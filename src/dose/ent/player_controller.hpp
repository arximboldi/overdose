/**
 *  @file        player_controller.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 24 12:43:40 2009
 *
 *  Interfaz de player_controller.
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

#ifndef DOSE_PLAYER_CONTROLLER_H_
#define DOSE_PLAYER_CONTROLLER_H_

#include <yage/core/key_observer.hpp>

namespace dose
{
namespace ent
{

class player;

class player_controller : public yage::core::key_listener
{
public:
    typedef boost::shared_ptr<player> player_ptr;

    player_controller (player_ptr person);

    bool handle_key_press (SDL_Event& ev);
    bool handle_key_release (SDL_Event& ev);
    void randomize_keys ();
    void restore_keys ();

private:
    player_ptr m_person;
    SDLKey m_move_keys [4];
};

} /* namespace ent */
} /* namespace dose */

#endif /* DOSE_PLAYER_CONTROLLER_H_ */
