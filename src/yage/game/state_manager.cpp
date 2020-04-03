/**
 *  @file        state_manager.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 12:42:05 2009
 *
 *  Implementación de la clase state_manager.
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

#include "yage/gra/scene.hpp"
#include "yage/gra/texture.hpp"
#include "yage/geo/textured_plane_2d.hpp"

#include "yage/core/system.hpp"
#include "state_manager.hpp"
#include "state.hpp"

namespace yage
{
namespace game
{

state_manager::state_manager ()
    : m_loading_scene (new gra::scene)
    , m_next_delta (1)
{
}

state_manager::~state_manager ()
{
    while (!m_states.empty ())
	do_leave_state ();
}

void state_manager::change_state (const std::string& name)
{
    m_actions.push (action_slot (CHANGE_STATE, name));
}

void state_manager::enter_state (const std::string& name)
{
    m_actions.push (action_slot (ENTER_STATE, name));
}

void state_manager::leave_state ()
{
    m_actions.push (action_slot (LEAVE_STATE, std::string ()));
}

void state_manager::update (int delta)
{
    if (!m_states.empty ())
	m_states.top ()->update (delta);

    while (!m_actions.empty ())
    {
	action_slot& a = m_actions.front ();

	switch (a.first)
	{
	case CHANGE_STATE:
	    do_change_state (a.second);
	    break;
	case ENTER_STATE:
	    do_enter_state (a.second);
	    break;
	case LEAVE_STATE:
	    do_leave_state ();
	    break;
	default:
	    break;
	}

	m_actions.pop ();
    }
}

void state_manager::do_change_state (const std::string& name)
{
    if (!m_states.empty ()) {
	unregister_state (m_states.top ());
	m_states.pop ();
    }
    clean_resources ();
    new_state (name);
}

void state_manager::do_enter_state (const std::string& name)
{
    if (!m_states.empty ()) {
	m_states.top ()->pause ();
	unregister_state (m_states.top ());
    }

    new_state (name);
}

void state_manager::new_state (const std::string& name)
{
    boost::shared_ptr<state> current (create (name));
    current->set_state_parent (shared_from_this ());

    std::string texname = current->loading ();
    if (!texname.empty ()) {
	core::graphic_system& graphic = core::system::self ().graphic ();
	gra::texture_ptr tex (graphic.textures ().find (texname));

	gra::scene_node& node = m_loading_scene->get_hud_root ();
	node.clear_drawables ();
	node.add_drawable (gra::drawable_ptr (new geo::textured_plane_2d (tex)));
	node.set_scale (base::point3f (
			    (float) graphic.get_width () / tex->get_width (),
			    (float) graphic.get_height () / tex->get_height (), 1));
	graphic.set_scene (m_loading_scene);
	graphic.update ();
    }

    current->init ();
    register_state (current);
    m_states.push (current);
}

void state_manager::do_leave_state ()
{
    if (!m_states.empty ()) {
	unregister_state (m_states.top ());
	m_states.pop ();
    }

    if (!m_states.empty ()) {
	register_state (m_states.top ());
	m_states.top ()->resume ();
    } else
	on_finish (*this);
}

void state_manager::register_state (boost::shared_ptr<state> st)
{
    core::system::type& sys = core::system::self ();

    sys.graphic ().set_scene (st->get_scene ());
    sys.input ().add_mouse_listener (st->get_mouse ());
    sys.input ().add_key_listener (st->get_keys ());
}

void state_manager::unregister_state (boost::shared_ptr<state> st)
{
    core::system::type& sys = core::system::self ();

    sys.graphic ().set_scene (boost::shared_ptr<gra::scene> ());
    sys.input ().del_mouse_listener (st->get_mouse ());
    sys.input ().del_key_listener (st->get_keys ());
}

void state_manager::clean_resources ()
{
    core::graphic_system& graphic = core::system::self ().graphic ();

    graphic.textures ().clear ();
    graphic.fonts ().clear ();
    graphic.geometries ().clear ();
    graphic.materials ().clear ();
}

} /* namespace game */
} /* namespace yage */
