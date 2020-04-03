/**
 *  @file        state_task.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 17 20:39:27 2009
 *
 *  Interfaz de state_task.
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

#ifndef YAGE_STATE_TASK_H_
#define YAGE_STATE_TASK_H_

#include <map>
#include <stack>

#include <boost/function.hpp>
#include <yage/base/exception.hpp>
#include <yage/core/task.hpp>

namespace yage
{
namespace core
{

YAGE_DECLARE_ERROR (base::yage_error, state_task_error);

class state_task : public task
{
public:
    typedef boost::function<void (int delta)> state_function;

    void add_state (const std::string& name,
		    const state_function& fun);

    void push_state (const std::string& name);
    void pop_state ();
    void change_state (const std::string& name);

    void update (int delta);

    const std::string& current ();

private:
    typedef std::map<std::string, state_function> state_map;

    std::stack<state_map::value_type> m_states;
    state_map m_state_map;
};

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_STATE_TASK_H_ */
