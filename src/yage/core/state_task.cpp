/**
 *  @file        state_task.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 17 20:46:33 2009
 *
 *  Implementación de state_task.
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

#include "state_task.hpp"

namespace yage
{
namespace core
{

YAGE_DEFINE_ERROR_WHERE (state_task_error, "state_task");

void state_task::add_state (const std::string& name,
			    const state_function& fun)
{
    m_state_map.insert (state_map::value_type (name, fun));
}

void state_task::change_state (const std::string& name)
{
    pop_state ();
    push_state (name);
}

void state_task::push_state (const std::string& name)
{
    state_map::iterator it = m_state_map.find (name);

    if (it == m_state_map.end ())
	throw state_task_error (std::string ("Unknown state: ") + name);

    m_states.push (*it);
}

void state_task::pop_state ()
{
    if (m_states.empty ())
	throw state_task_error ("Can not pop empty state task.");
    m_states.pop ();
}

void state_task::update (int delta)
{
    if (!m_states.empty ())
	m_states.top ().second (delta);
}

const std::string& state_task::current ()
{
    if (m_states.empty ())
	throw state_task_error ("Can not pop empty state task.");
    return m_states.top ().first;
}

} /* namespace core */
} /* namespace yage */
