/**
 *  @file        state.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 15:32:48 2009
 *
 *  Implementación de la clase state.
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
#include "state.hpp"
#include "state_manager.hpp"

namespace yage
{
namespace game
{

state::state ()
    : m_tasks (new core::task_manager)
    , m_scene (new gra::scene)
{
}

void state::update (int delta)
{
    m_tasks->update (delta);
}

void state::change_state (const std::string& name)
{
    get_state_parent ()->change_state (name);
}

void state::enter_state (const std::string& name)
{
    get_state_parent ()->enter_state (name);
}

void state::leave_state ()
{
    get_state_parent ()->leave_state ();
}

} /* namespace game */
} /* namespace yage */
