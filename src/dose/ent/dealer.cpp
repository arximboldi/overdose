/**
 *  @file        dealer.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu Jun 11 19:45:48 2009
 *
 *  Implementación de la clase dealer.
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
#include "dose/st/level.hpp"
#include "dealer.hpp"
#include "player.hpp"

using namespace yage;

namespace dose
{
namespace ent
{

dealer::dealer (const std::string& model,
		const std::string& texture,
		bool inverse_normals,
		float walk_speed,
		float rotate_speed)
    : pedestrian (model, texture, inverse_normals, walk_speed, rotate_speed)
{
    states ().add_state ("salute", bind (&dealer::salute_state, this, _1));
}

void dealer::add_drug (dope_ptr d)
{
    m_drugs.push_back (d);
}

dealer::dope_ptr dealer::current_offer ()
{
    return m_drugs.front ();
}

dealer::dope_ptr dealer::take_shit ()
{
    dope_ptr ret = m_drugs.front ();
    m_drugs.pop_front ();
    return ret;
}

bool dealer::has_shit () const
{
    return !m_drugs.empty ();
}

void dealer::update (int delta)
{
    pedestrian::update (delta);

    if (states ().current () != "salute" && player_near ())
	states ().push_state ("salute");
}

bool dealer::player_near ()
{
    base::point3f d = get_level ()->get_player ()->get_node ().get_world_position ();
    base::point3f t = get_node ().get_world_position ();

    return (d - t).sq_length () < PLAYER_DISTANCE * PLAYER_DISTANCE;
}

void dealer::salute_state (int delta)
{
    try {
	set_animation ("salute");
    } catch (geo::md2_model_error& err) {
	set_animation ("stand", 1.5);
    }

    if (!player_near ()) {
	states ().pop_state ();
	finish_animation ();
    }
    else
	set_look_angle (angle_to_player ());
}

} /* namespace ent */
} /* namespace dose */
