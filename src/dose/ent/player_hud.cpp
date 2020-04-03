/**
 *  Time-stamp:  <2020-04-03 16:05:55 raskolnikov>
 *
 *  @file        player_hud.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu Jun 11 23:44:53 2009
 *
 *  Implementación de la clase player_hud.
 *
 *  @todo Debemos minimizar las responsabilidades de esta clase.
 */

/*
 *  Copyright (C) 2009 Juan Pedro Bolívar Puente
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <cassert>
#include <boost/lexical_cast.hpp>
#include <yage/core/system.hpp>
#include <yage/geo/textured_plane_2d.hpp>

#include "dose/overdose.hpp"

#include "dose/drug/dope.hpp"
#include "player_hud.hpp"

using namespace yage;
using namespace yage::base;

namespace dose
{
namespace ent
{

gra::scene_node& player_hud::get_slot (int i)
{
    return m_node.get_path (std::string ("slot_") + boost::lexical_cast<std::string> (i));
}

player_hud::player_hud ()
    : m_psychodelia (overdose::s_dope_level)
    , m_ecstasy (overdose::s_dope_level)
    , m_euphoria (overdose::s_dope_level)
    , m_alert_count (0)
    , m_selected (-1)
{
    core::graphic_system& graphic = core::system::self ().graphic ();

    m_node.set_position (point3f (0, 0, 0));
    m_node.set_scale (point3f (1, 1, 0));
    m_node.set_rotate (point4f (0, 0, 0, 0));

    /* Establecemos el fondo de los indicadores */
    {
	gra::texture_ptr t (graphic.textures ().find ("level-bg.png"));
	gra::drawable_ptr d (new geo::textured_plane_2d (t));
	t->set_blending (true);

	{
	    gra::scene_node& n = m_node.get_child ("psychodelia");
	    n.get_child ("bg").add_drawable (d);
	    n.set_position (point3f (30, t->get_height () + 10, 0));
	    n.set_rotate (point4f (180, 0, 0, 1));
	}
	{
	    gra::scene_node& n = m_node.get_child ("ecstasy");
	    n.get_child ("bg").add_drawable (d);
	    n.set_position (point3f (55, t->get_height () + 10, 0));
	    n.set_rotate (point4f (180, 0, 0, 1));
	}
	{
	    gra::scene_node& n = m_node.get_child ("euphoria");
	    n.get_child ("bg").add_drawable (d);
	    n.set_position (point3f (80, t->get_height () + 10, 0));
	    n.set_rotate (point4f (180, 0, 0, 1));
	}
    }

    /* Establecemos los indicadores */
    {
	gra::texture_ptr t (graphic.textures ().find ("level-psychodelia.png"));
	gra::drawable_ptr d (new geo::textured_plane_2d (t));
	t->set_blending (true);
	gra::scene_node& n = m_node.get_path ("psychodelia.level");
	n.add_drawable (d);
	n.set_position (point3f (1, 1, 0.5));
	n.set_scale (point3f (1, 0, 0));
    }
    {
	gra::texture_ptr t (graphic.textures ().find ("level-ecstasy.png"));
	gra::drawable_ptr d (new geo::textured_plane_2d (t));
	t->set_blending (true);
	gra::scene_node& n = m_node.get_path ("ecstasy.level");
	n.add_drawable (d);
	n.set_position (point3f (1, 1, 0.5));
	n.set_scale (point3f (1, 0, 0));
    }
    {
	gra::texture_ptr t (graphic.textures ().find ("level-euphoria.png"));
	gra::drawable_ptr d (new geo::textured_plane_2d (t));
	t->set_blending (true);
	gra::scene_node& n = m_node.get_path ("euphoria.level");
	n.add_drawable (d);
	n.set_position (point3f (1, 1, 0.5));
	n.set_scale (point3f (1, 0, 0));
    }

    /* Las drogas*/
    {
	gra::texture_ptr t (graphic.textures ().find ("dope-bg.png"));
	m_selected_bg.reset (new geo::textured_plane_2d (t));
	t->set_blending (true);

	for (int i = 0; i < MAX_DRUG; ++i) {
	    get_slot (i).set_position (
		point3f (graphic.get_width () - t->get_width () - 10,
			 10 + t->get_height () * i, 0));
	    get_slot (i).get_child ("bg").set_position (point3f (0, 0, -0.5));
	    get_slot (i).get_child ("fg").set_position (point3f (0, 0, 0.5));
	}
    }

    /* Establecemos el cuadro de texto de los mensajes de usuario. */
    {
	gra::font_ptr f = graphic.fonts ().find ("DejaVuSans.ttf", 16);
	f->set_style (TTF_STYLE_BOLD);
	m_player_msg.reset (new gra::text (f));
	gra::scene_node& n = m_node.get_child ("player-message");
	n.add_drawable (m_player_msg);
	m_player_msg->set_color (point3f (1, 1, 0));
    }
    {
	m_player_alert.reset (new gra::text (graphic.fonts ().find ("DejaVuSans.ttf", 16)));
	gra::scene_node& n = m_node.get_child ("player-alert");
	n.add_drawable (m_player_alert);
	m_player_alert->set_color (point3f (1, 0, 0));
    }
}

void player_hud::set_player_message (const std::string& str)
{
    if (str != m_player_msg->get_text ()) {
	core::graphic_system& graphic = core::system::self ().graphic ();

	m_player_msg->set_text (str);
	float center = graphic.get_width () / 2 - m_player_msg->get_width () / 2;
	m_node.get_child ("player-message").set_position (point3f (center, 20, 0));
    }
}

void player_hud::set_player_alert (const std::string& str, int duration)
{
    if (str != m_player_alert->get_text ()) {
	core::graphic_system& graphic = core::system::self ().graphic ();

	m_player_alert->set_text (str);
	float center = graphic.get_width () / 2 - m_player_alert->get_width () / 2;
	m_node.get_child ("player-alert").set_position (point3f (center, 40, 0));
    }
    m_alert_count = duration;
}

void player_hud::update (int delta)
{
    if (m_alert_count > 0) {
	m_alert_count -= delta;
	if (m_alert_count <= 0) {
	    m_player_alert->set_text ("");
	    m_alert_count = 0;
	}
    }

    clean_effects ();
}

player_hud::~player_hud ()
{
    if (m_node.get_parent ())
	m_node.get_parent ()->detach (m_node.get_name ());
}

void player_hud::set_psychodelia (float psychodelia)
{
    gra::scene_node& n = m_node.get_path ("psychodelia.level");
    n.set_scale (point3f (1, std::min (1.0f, psychodelia / DRUG_SCALE), 0));
    m_psychodelia = psychodelia;
}

void player_hud::set_ecstasy (float ecstasy)
{
    gra::scene_node& n = m_node.get_path ("ecstasy.level");
    n.set_scale (point3f (1, std::min (1.0f, ecstasy / DRUG_SCALE), 0));
    m_ecstasy = ecstasy;
}

void player_hud::set_euphoria (float euphoria)
{
    gra::scene_node& n = m_node.get_path ("euphoria.level");
    n.set_scale (point3f (1, std::min (1.0f, euphoria / DRUG_SCALE), 0));
    m_euphoria = euphoria;
}

void player_hud::add_drug (dope_ptr p)
{
    assert (!full ());

    get_slot (m_drugs.size ()).get_child ("fg").add_drawable (
	gra::drawable_ptr (new geo::textured_plane_2d (p->get_texture ())));
    m_drugs.push_back (p);

    if (m_selected < 0)
	change_selected (0);
}

void player_hud::clear_drugs ()
{
    for (size_t i = 0; i < m_drugs.size (); ++i)
	get_slot (i).get_child ("fg").clear_drawables ();
    m_drugs.clear ();
    change_selected (-1);
}

void player_hud::apply_drug (dope_ptr ret)
{
    set_psychodelia (std::max (get_psychodelia () + ret->get_psychodelia (), 0.0f));
    set_ecstasy (std::max (get_ecstasy () + ret->get_ecstasy (), 0.0f));
    set_euphoria (std::max (get_euphoria () + ret->get_euphoria (), 0.0f));

    effect_list::iterator it;
    for (it = m_effects.begin (); it != m_effects.end (); ++it) {
	if (!it->expired () &&
	    ret->get_name () == drug::dope_effect_ptr (*it)->get_name ())
	{
	    drug::dope_effect_ptr (*it)->accumulate (ret);
	    break;
	}
    }

    if (it == m_effects.end ()) {
	drug::dope_effect_ptr fx (new drug::dope_effect (ret));
	fx->take ();
	m_node.attach ("effect_" + fx->get_name (), fx->get_node ());
	m_effects.push_back (fx);
    }

    clean_effects ();
}

drug::dope_ptr player_hud::take_drug ()
{
    assert (m_selected >= 0 && m_selected < (int) m_drugs.size ());

    /* Eliminamos la droga de la lista */
    drug::dope_ptr ret = m_drugs [m_selected];
    m_drugs.erase (m_drugs.begin () + m_selected);

    get_slot (m_selected).get_child ("fg").clear_drawables ();
    for (size_t i = m_selected; i < m_drugs.size (); ++i) {
	gra::scene_node& curr = get_slot (i).get_child ("fg");
	gra::scene_node& next = get_slot (i+1).get_child ("fg");
	curr.add_drawable (next.drawable_begin (), next.drawable_end ());
	next.clear_drawables ();
    }

    if (m_selected >= (int) m_drugs.size ())
	change_selected (m_selected - 1);

    return ret;
}

void player_hud::finish_drugs ()
{
    effect_list::iterator it;
    for (it = m_effects.begin (); it != m_effects.end (); ++it)
	if (!it->expired ())
	    drug::dope_effect_ptr (*it)->force_finish ();
    m_effects.clear ();
}

void player_hud::clean_effects ()
{
    point3f pos (0, core::system::self ().graphic ().get_height () - 30, 0);

    for (effect_list::iterator it = m_effects.begin ();
	 it != m_effects.end ();)
    {
	if (it->expired () || drug::dope_effect_ptr (*it)->is_finished ()) {
	    it = m_effects.erase (it);
	} else {
	    drug::dope_effect_ptr (*it)->get_node ().set_position (pos);
	    pos [1] -= 25;
	    ++it;
	}
    }
}

void player_hud::select_next ()
{
    if (!m_drugs.empty ())
	change_selected ((m_selected + 1) % m_drugs.size ());
}

void player_hud::select_prev ()
{
    if (!m_drugs.empty ())
	change_selected ((m_selected - 1) < 0 ? m_drugs.size () - 1 : m_selected - 1);
}

void player_hud::change_selected (int new_sel)
{
    if (m_selected >= 0)
	get_slot (m_selected).get_child ("bg").clear_drawables ();

    if (new_sel >= 0)
	get_slot (new_sel).get_child ("bg").add_drawable (m_selected_bg);

    m_selected = new_sel;
}

} /* namespace ent */
} /* namespace dose */
