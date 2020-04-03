/**
 *  @file        game_app.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 16:28:19 2009
 *
 *  Implementación de la clase game_app.
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

#include "yage/core/task_manager.hpp"
#include "yage/core/system.hpp"
#include "game_app.hpp"

namespace yage
{
namespace app
{

game_app::game_app (const std::string& name,
		    const std::string& version,
		    const std::string& description,
		    const std::string& copyright_date,
		    const std::string& author)
    : yage_app (name,
		version,
		description,
		copyright_date,
		author)
    , m_game_states (new game::state_manager)
{
    m_game_states->on_finish.connect (
	sigc::mem_fun (*this, &game_app::handle_state_manager_finish));
}

int game_app::execute ()
{
    register_states (m_game_states);
    m_game_states->enter_state (initial_state ());

    core::system::self ().tasks ().add (m_game_states);
    core::system::self ().main_loop ();

    return 0;
}

void game_app::handle_state_manager_finish (game::state_manager&)
{
    core::system::self ().quit_loop ();
}

} /* namespace app */
} /* namespace yage */
