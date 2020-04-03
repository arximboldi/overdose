/**
 *  Time-stamp:  <2009-06-15 21:04:09 raskolnikov>
 *
 *  @file        policeman.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sat Jun 13 22:00:17 2009
 *
 *  Implementación de la clase policeman.
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

#include <yage/game/entity_manager.hpp>

#include "dose/st/level.hpp"
#include "policeman.hpp"
#include "player.hpp"

using namespace yage;
using namespace yage::base;
using namespace boost;

namespace dose
{
namespace ent
{

policeman::policeman (float walk_speed,
		      float rotate_speed)
    : pedestrian ("swat.md2", "swat.png", true, walk_speed, rotate_speed)
    , m_old_action (0)
{
    states ().add_state ("follow", bind (&policeman::follow_state, this, _1));
}

void policeman::handle_collision (yage::game::entity& other,
				  yage::game::collidable& box,
				  yage::game::dynamic_collision& col)
{
    try {
	player& p = dynamic_cast<player&> (other);
	if (!p.get_hud ().empty ())
	    person::handle_collision (other, box, col);
	else
	    pedestrian::handle_collision (other, box, col);
	p.handle_police ();
    } catch (std::bad_cast&) {
	pedestrian::handle_collision (other, box, col);
    }
}
    
void policeman::update (int delta)
{
    pedestrian::update (delta);

    if (states ().current () != "follow")
    {
	if (!get_level ()->get_player ()->is_dead () &&
	    player_has_drugs () &&
	    player_in_distance () &&
	    player_in_fov () &&
	    player_in_line ())
	{
	    m_old_action = get_action ();
	    set_action (RUN_FW);
	    states ().push_state ("follow");
	}
    }
}

void policeman::follow_state (int delta)
{
    if (get_level ()->get_player ()->is_dead () ||
	!player_has_drugs () ||
	!player_in_distance () ||
	!player_in_fov () ||
	!player_in_line ())
    {
	states ().pop_state ();
	set_action (m_old_action);
    }
    else
	set_look_angle (angle_to_player ());
}

bool policeman::player_in_fov ()
{
    const float fov = M_PI / 2.0f;
    
    float a = base::normalize_angle (get_look_angle ());
    float pa = angle_to_player ();

    return
	std::abs (a - pa) < fov ||
	std::abs (a - pa) > 2*M_PI - fov;
}

bool policeman::player_in_line ()
{
    game::sphere colbox (get_node ().get_world_position (), 10);
    game::collidable camcol = colbox;
    point3f line =
	get_level ()->get_player ()->get_node ().get_world_position () - colbox.center;
    return
	! get_level ()->entities ()->find_dynamic_static_collisions (colbox, line);
}

bool policeman::player_has_drugs ()
{
    return ! get_level ()->get_player ()->get_hud ().empty ();
}

bool policeman::player_in_distance ()
{
    const float SQ_DISTANCE = 1000 * 1000;
    return sq_distance_to_player () < SQ_DISTANCE;
}

} /* namespace ent */
} /* namespace dose */
