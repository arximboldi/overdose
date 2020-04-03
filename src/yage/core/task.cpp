/**
 *  @file        task.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Wed May 13 19:36:20 2009
 *
 *  Implementación de la clase task.
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

#include "task.hpp"
#include "task_manager.hpp"

namespace yage
{
namespace core
{

task::task ()
    : m_is_finished (false)
    , m_is_paused (false)
{}

void task::finish ()
{
    m_is_finished = true;
    if (!m_next.empty () && !m_parent.expired ()) {
	task_list::iterator it;
	for (it = m_next.begin (); it != m_next.end (); ++it)
	    get_task_parent ()->add (*it);
    }
}

} /* namespace core */
} /* namespace yage */
