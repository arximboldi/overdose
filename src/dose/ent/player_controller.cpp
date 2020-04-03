/**
 *  Time-stamp:  <2009-06-13 16:43:22 raskolnikov>
 *
 *  @file        player_controller.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 24 13:29:04 2009
 *
 *  Implementación de player_controller.
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

#include "player.hpp"
#include "player_controller.hpp"

using namespace yage;

namespace dose
{
namespace ent
{

const SDLKey DEFAULT_MOVE_KEYS [] =
{
    SDLK_UP,
    SDLK_DOWN,
    SDLK_LEFT,
    SDLK_RIGHT
};

player_controller::player_controller (player_ptr person)
    : m_person (person)
{
    for (int i = 0; i < 4; ++i)
	m_move_keys [i] = DEFAULT_MOVE_KEYS [i];
}

void player_controller::randomize_keys ()
{
    for (int i = 0; i < 8; ++i) {
	int a = base::ranged_random (0, 4);
	int b = base::ranged_random (0, 4);
	std::swap (m_move_keys [a], m_move_keys [b]);
    }
    m_person->set_action (0);
}

void player_controller::restore_keys ()
{
    for (int i = 0; i < 4; ++i)
	m_move_keys [i] = DEFAULT_MOVE_KEYS [i];
    m_person->set_action (0);
}

bool player_controller::handle_key_press (SDL_Event& ev)
{
    SDLKey k = ev.key.keysym.sym;
    
    switch (k)
    {
    case SDLK_b:
	m_person->buy_some_shit ();
	break;

    case SDLK_n:
	m_person->get_hud ().select_prev ();
	break;

    case SDLK_m:
	m_person->get_hud ().select_next ();
	break;	

    case SDLK_SPACE:
	m_person->take_some_shit ();
	break;	

    default:
	if (k == m_move_keys [0])
	    m_person->activate_action (person::RUN_FW);
	else if (k == m_move_keys [1])
	    m_person->activate_action (person::RUN_BW);
	else if (k == m_move_keys [2])
	    m_person->activate_action (person::ROTATE_L);
	else if (k == m_move_keys [3])
	    m_person->activate_action (person::ROTATE_R);
	break;
    };

    return false;
}

bool player_controller::handle_key_release (SDL_Event& ev)
{
    SDLKey k = ev.key.keysym.sym;
    
    switch (k)
    {
    default:
	if (k == m_move_keys [0])
	    m_person->deactivate_action (person::RUN_FW);
	else if (k == m_move_keys [1])
	    m_person->deactivate_action (person::RUN_BW);
	else if (k == m_move_keys [2])
	    m_person->deactivate_action (person::ROTATE_L);
	else if (k == m_move_keys [3])
	    m_person->deactivate_action (person::ROTATE_R);
	break;
    };

    return false;
}   

} /* namespace ent */
} /* namespace dose */
