/**
 *  Time-stamp:  <2009-06-10 22:19:40 raskolnikov>
 *
 *  @file        fly_camera_controller.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 19:08:12 2009
 *
 *  Implementación de fly_camera_controller
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

#include <cmath>
#include <lib/matrix.h>
#include <lib/vertex.h>
#include "fly_camera_controller.hpp"

using namespace yage;

namespace dose
{
namespace tool
{

fly_camera_controller::fly_camera_controller (yage::gra::camera_ptr cam,
					      float move_speed,
					      float rotate_speed)
    : m_camera (cam)
    , m_move_speed (move_speed)
    , m_rotate_speed (rotate_speed)
    , m_move (0)
{
}

void fly_camera_controller::update (int delta)
{
    if (m_move & STRAFE_LEFT) {
	base::point3f dir =
	    m_camera->get_up_vector ()
	    .cross (m_camera->get_plane_normal ())
	    .normalize ();
	
	m_camera->set_position (
	    m_camera->get_position () - dir * m_move_speed * delta);
    }

    if (m_move & STRAFE_RIGHT) {
	base::point3f dir =
	    m_camera->get_up_vector ()
	    .cross (m_camera->get_plane_normal ())
	    .normalize ();
	
	m_camera->set_position (
	    m_camera->get_position () + dir * m_move_speed * delta);
    }

    if (m_move & MOVE_FORWARD) {
	m_camera->set_position (
	    m_camera->get_position () -
	    m_camera->get_plane_normal ().normalize () * m_move_speed * delta);
    }

    if (m_move & MOVE_BACKWARD) {
	m_camera->set_position (
	    m_camera->get_position () +
	    m_camera->get_plane_normal ().normalize () * m_move_speed * delta);
    }
}

bool fly_camera_controller::handle_key_press (SDL_Event& ev)
{
    switch (ev.key.keysym.sym)
    {
    case SDLK_a:
	m_move |= STRAFE_LEFT;
	break;
    case SDLK_d:
	m_move |= STRAFE_RIGHT;
	break;
    case SDLK_w:
	m_move |= MOVE_FORWARD;
	break;
    case SDLK_s:
	m_move |= MOVE_BACKWARD;
    default:
	break;
    }

    return true;
}

bool fly_camera_controller::handle_key_release (SDL_Event& ev)
{
    switch (ev.key.keysym.sym)
    {
    case SDLK_a:
	m_move ^= STRAFE_LEFT;
	break;
    case SDLK_d:
	m_move ^= STRAFE_RIGHT;
	break;
    case SDLK_w:
	m_move ^= MOVE_FORWARD;
	break;
    case SDLK_s:
	m_move ^= MOVE_BACKWARD;
    default:
	break;
    }

    return true;
}

bool fly_camera_controller::handle_mouse_move (SDL_Event& ev)
{
    float horiz = ev.motion.xrel * m_rotate_speed;
    float vert = ev.motion.yrel * m_rotate_speed;

    base::point3f n = m_camera->get_plane_normal ();
    base::point3f u = m_camera->get_up_vector ();
    base::point3f v = n.normal (u);
    
    n = n.rotate (- horiz, u);
    n = n.rotate (vert, v);
    
    m_camera->set_plane_normal (n);
    
    return true;
}

} /* namespace tool */
} /* namespace dose */
