/***************************************************************************
 *                                                                         *
 *   PSYCHOSYNTH                                                           *
 *   ===========                                                           *
 *                                                                         *
 *   Copyright (C) 2007 Juan Pedro Bolivar Puente                          *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 ***************************************************************************/

#include "yage/base/iterator.hpp"
#include "task_manager.hpp"

namespace yage
{

namespace core
{

void task_manager::add (boost::shared_ptr<task> t)
{
    m_tasks.push_back (t);
    t->set_task_parent (shared_from_this ());
}

void task_manager::del (boost::shared_ptr<task> t)
{
    m_tasks.remove (t);
    t->set_task_parent (boost::shared_ptr<task_manager> ());
}

void task_manager::update (int ms)
{
    base::ptr_iterator<task_list::iterator> i = m_tasks.begin();

    while (i != m_tasks.end ())
    {
	if (i->is_finished ()) {
	    i = m_tasks.erase (i);
	} else {
	    if (!i->is_paused ())
		i->update (ms);
	    i++;
	}
    }
}

} /* namespace core */
} /* namespace yage */
