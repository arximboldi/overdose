/**
 *  @file        pedestrian.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Wed Jun 10 19:50:14 2009
 *
 *  Implementacion de la clase pedestrian.
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

#include <boost/bind.hpp>
#include <yage/base/misc.hpp>
#include <yage/game/dynamic_collision.hpp>

#include "dose/st/level.hpp"
#include "pedestrian.hpp"
#include "player.hpp"

using namespace boost;
using namespace yage;

const int MIN_IDLE = 1000;
const int MAX_IDLE = 10000;

const int MIN_WALK = 1000;
const int MAX_WALK = 10000;

namespace dose
{
namespace ent
{

pedestrian::pedestrian (const std::string& model,
			const std::string& texture,
			bool inverse_normals,
			float walk_speed,
			float rotate_speed)
    : person (model, texture, inverse_normals, walk_speed, rotate_speed)
{
    m_states.add_state ("walk", bind (&pedestrian::walk_state, this, _1));
    m_states.add_state ("idle", bind (&pedestrian::idle_state, this, _1));
    m_states.add_state ("rotate", bind (&pedestrian::rotate_state, this, _1));

    m_states.push_state ("idle");
    m_ticks = base::ranged_random (MIN_IDLE, MAX_IDLE);
}

void pedestrian::update (int delta)
{
    person::update (delta);
    m_states.update (delta);
}

void pedestrian::handle_collision (yage::game::entity& other,
				   yage::game::collidable& box,
				   yage::game::dynamic_collision& col)
{
    person::handle_collision (other, box, col);

    if (states ().current () != "rotate")
    {
	base::point3f normal = col.get_normal ();

	m_dest_angle = std::atan2 (normal[2], normal[0]);
	m_dest_angle = base::ranged_random<float> (m_dest_angle - M_PI/2, m_dest_angle + M_PI/2);
	m_dest_angle = base::normalize_angle (m_dest_angle);

	m_old_action = get_action ();

	float curr_angle = base::normalize_angle (get_look_angle ());
	if (base::normalize_angle (m_dest_angle - curr_angle) < 0)
	    set_action (ROTATE_L);
	else
	    set_action (ROTATE_R);

	m_states.push_state ("rotate");
    }
}

void pedestrian::rotate_state (int delta)
{
    float curr_angle = base::normalize_angle (get_look_angle ());
    if (base::normalize_angle (m_dest_angle - curr_angle) < 0)
	set_action (ROTATE_L);
    else
	set_action (ROTATE_R);

    if (std::abs (m_dest_angle - curr_angle) <= get_rotate_speed () * delta)
    {
	set_action (m_old_action);
	m_states.pop_state ();
    }
}

void pedestrian::walk_state (int delta)
{
    m_ticks -= delta;
    if (m_ticks <= 0) {
	m_ticks = base::ranged_random (MIN_IDLE, MAX_IDLE);
	m_states.change_state ("idle");
	set_action (0);
    }
}

void pedestrian::idle_state (int delta)
{
    m_ticks -= delta;
    if (m_ticks <= 0) {
	m_ticks = base::ranged_random (MIN_WALK, MAX_WALK);
	set_action (RUN_FW);
	m_states.change_state ("walk");
    }
}

float pedestrian::angle_to_player ()
{
    base::point3f d = get_level ()->get_player ()->get_node ().get_world_position ();
    base::point3f t = get_node ().get_world_position ();
    base::point3f v = d - t;
    return std::atan2 (v[2], v[0]);
}

float pedestrian::sq_distance_to_player ()
{
    base::point3f d = get_level ()->get_player ()->get_node ().get_world_position ();
    base::point3f t = get_node ().get_world_position ();

    return (d - t).sq_length ();
}

} /* namespace ent */
} /* namespace dose */
