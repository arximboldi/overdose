/**
 *  @file        state_manager.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 12:39:35 2009
 *
 *  Interfaz de la clase state_manager.
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

#ifndef YAGE_STATE_MANAGER_H_
#define YAGE_STATE_MANAGER_H_

#include <stack>
#include <queue>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <yage/base/factory_manager.hpp>
#include <yage/core/task.hpp>

namespace yage
{

namespace gra
{
class scene;
};

namespace game
{

class state;

typedef base::factory_manager<std::string, state> state_factory;

class state_manager : public state_factory
		    , public core:: task
		    , public boost::enable_shared_from_this<state_manager>
{
public:
    typedef sigc::signal1<void, state_manager&> signal;
    signal on_finish;

    state_manager ();
    ~state_manager ();

    void update (int delta);

    void change_state (const std::string& name);
    void enter_state (const std::string& name);
    void leave_state ();

    bool empty ()
    {
	return m_states.empty ();
    }

private:
    enum action
    {
	ENTER_STATE,
	CHANGE_STATE,
	LEAVE_STATE
    };
    typedef std::pair<action, std::string> action_slot;

    void do_change_state (const std::string& name);
    void do_enter_state (const std::string& name);
    void do_leave_state ();

    void new_state (const std::string& name);
    void register_state (boost::shared_ptr<state> st);
    void unregister_state (boost::shared_ptr<state> st);

    void clean_resources ();

    std::string m_next_state;
    std::stack<boost::shared_ptr<state> > m_states;
    std::queue<action_slot> m_actions;

    boost::shared_ptr<gra::scene> m_loading_scene;
    int m_next_delta;
};

} /* namespace game */
} /* namespace yage */

#endif /* YAGE_STATE_MANAGER_H_ */
