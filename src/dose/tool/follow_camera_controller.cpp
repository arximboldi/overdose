/**
 *  Time-stamp:  <2009-06-16 11:26:00 raskolnikov>
 *
 *  @file        follow_camera_controller.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 24 11:52:43 2009
 *
 *  Implementación de follow_camera_controller.
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

#include <yage/base/misc.hpp>
#include <yage/game/entity.hpp>
#include <yage/game/dynamic_collision.hpp>
#include <yage/game/entity_manager.hpp>
#include "follow_camera_controller.hpp"

using namespace boost;
using namespace yage;

namespace dose
{
namespace tool
{

follow_camera_controller::follow_camera_controller (yage::gra::camera_ptr cam,
						    yage::game::entity_ptr ent,
						    float distance,
						    float angle,
						    float speed)
    : m_camera (cam)
    , m_entity (ent)
    , m_distance (distance)
    , m_angle (angle)
    , m_hangle (0)
    , m_speed (speed)
{
    base::point3f orient;

    ent->add_listener (*this);
    m_old_pos    = ent->get_node ().get_position ();
    m_old_orient = ent->get_orientation ();
}

void follow_camera_controller::handle_entity_move (game::entity& p)
{
    base::point3f new_pos = p.get_node().get_position ();

    m_old_pos = new_pos;
    recalculate ();
}

void follow_camera_controller::handle_entity_rotate (game::entity& p)
{
    m_old_orient = p.get_orientation ();
    recalculate ();
}

void follow_camera_controller::recalculate ()
{    
    /* HACK, parametrizar el 50 ese ;) */
    base::point3f center = m_old_pos + base::point3f (0, 50, 0);
    float hangle = std::atan2 (m_old_orient [0], m_old_orient [2]) + m_hangle;
    base::point3f newpos = center - base::point3f (
	std::cos (m_angle) * std::sin (hangle) * m_distance,
	- std::sin (m_angle) * m_distance,
	std::cos (m_angle) * std::cos (hangle) * m_distance);
    
    /* Evitamos colisiones con el suelos */
    if (newpos [1] < 0)
	newpos [1] = 5;
    
    /* Si los volumenes se solapan esto no funciona bien:
         - Comprobamos si la camara esta dentro de algun volumen.
	 - Nos imaginamos que viajamos desde el centro del rayo de vision
	   hasta la camara para buscar "cuanto" podríamos movernos y acortar
	   así la distancia en la práctica */
    game::entity_manager_ptr entities (m_entity->get_entity_parent ());
    game::sphere cambox ( newpos, 5 /* near de la cam / 2 ??*/ );
    game::collidable camcol = cambox;
    
    game::entity_manager::entity_list elist;
    entities->find_collisions (elist, camcol);

    if (!elist.empty ()) {
	cambox.center = center;
	camcol = cambox;
	
	game::collidable other = elist.front ()->get_bounds ();
	translate_collidable (other, elist.front ()->get_node ().get_position ());
	game::dynamic_collision col;
	if (col.test (other, camcol, newpos - center)) {
	    newpos = center + col.get_delta () * col.get_time ();
	}
    }

    m_camera->set_position (newpos);
    m_camera->look_at (center);
}

bool follow_camera_controller::handle_mouse_move (SDL_Event& ev)
{
    const float EPSILON = 0.001;
    m_angle = base::clamp<float> (m_angle + ev.motion.yrel * m_speed, -M_PI/2+EPSILON, M_PI/2-EPSILON);
    m_hangle += ev.motion.xrel * m_speed;

    recalculate ();
    
    return false;
}

bool follow_camera_controller::handle_mouse_button_press (SDL_Event& ev)
{
    switch (ev.button.button)
    {
    case SDL_BUTTON_WHEELUP:
	m_distance = base::clamp<float> (m_distance - m_speed * 1000, 50, 1000);
	break;
    case SDL_BUTTON_WHEELDOWN:
	m_distance = base::clamp<float> (m_distance + m_speed * 1000, 50, 1000);
	break;
    case SDL_BUTTON_MIDDLE:
	m_hangle = 0;
	break;
    default:
	break;
    }

    recalculate ();
    
    return false;
}

bool follow_camera_controller::handle_mouse_button_release (SDL_Event& ev)
{
    return false;
}


} /* namespace tool */
} /* namespace dose */
