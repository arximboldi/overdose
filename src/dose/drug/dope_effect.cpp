/**
 *  @file        dope_effect.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 21:18:21 2009
 *
 *  Implementación de la clase dope_effect.
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

#include <yage/core/system.hpp>
#include <yage/gra/text.hpp>
#include <yage/geo/textured_plane_2d.hpp>

#include "dose/st/level.hpp"
#include "dope.hpp"
#include "dope_effect.hpp"

using namespace yage;
using namespace yage::base;

namespace dose
{
namespace drug
{

dope_effect::dope_effect (dope_ptr p)
    : m_dope (p)
{
    core::graphic_system& graphic = core::system::self ().graphic ();

    /* Nombre de la droga */
    {
	gra::scene_node& n = m_node.get_path ("bar.text");

	gra::text_ptr t (new gra::text (graphic.fonts ().find ("DejaVuSans.ttf", 14),
					p->get_name (),
					point3f (1, 1, 1)));
	n.add_drawable (t);
	n.set_position (point3f (5, 2, 0));
    }

    /* Barra de progreso */
    {
	gra::scene_node& n = m_node.get_path ("bar.progress");
	{
	    gra::texture_ptr t = graphic.textures ().find ("effect-bg.png");
	    t->set_blending (true);
	    n.add_drawable (gra::drawable_ptr (new geo::textured_plane_2d (t)));


	    m_node.get_child ("bar").set_position (
		point3f (graphic.get_width () / 2 - t->get_width () / 2, 0, 0));
	}
	gra::scene_node& ni = n.get_child ("level");
	{
	    gra::texture_ptr t = graphic.textures ().find ("effect.png");
	    t->set_blending (true);
	    ni.add_drawable (gra::drawable_ptr (new geo::textured_plane_2d (t)));
	    ni.set_position (point3f (1, 1, 0.5));
	}
    }

}

dope_effect::~dope_effect ()
{
    if (m_node.get_parent ())
	m_node.get_parent ()->detach (m_node.get_name ());
}

void dope_effect::take ()
{
    m_dope->take ();
    m_dope->get_level ()->get_tasks ().add (shared_from_this ());
}

void dope_effect::accumulate (dope_ptr d)
{
    m_dope->accumulate (d);
}

void dope_effect::update (int delta)
{
    m_node.get_path ("bar.progress.level").set_scale (
	base::point3f (std::min (1.0f, m_dope->get_progress ()), 1, 1));

    m_dope->update (delta);
    if (m_dope->get_progress () <= 0) {
	m_dope->handle_finish ();
	finish ();
    }
}

void dope_effect::force_finish ()
{
    m_dope->set_progress (0);
    m_dope->handle_finish ();
    finish ();
}

const std::string& dope_effect::get_name () const
{
    return m_dope->get_name ();
}

} /* namespace drug */
} /* namespace dose */
