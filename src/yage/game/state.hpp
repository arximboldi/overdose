/**
 *  @file        state.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 12:42:42 2009
 *
 *  Interfaz de la clase state.
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

#ifndef YAGE_STATE_H_
#define YAGE_STATE_H_

#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <yage/core/mouse_observer.hpp>
#include <yage/core/key_observer.hpp>
#include <yage/core/task.hpp>
#include <yage/core/task_manager.hpp>

namespace yage
{

namespace gra
{
class scene;
}

namespace game
{

class state_manager;

class state : public boost::enable_shared_from_this<state>
{
public:
    state ();
    virtual ~state () {}

    virtual void init () {}
    virtual void pause () {}
    virtual void resume () {}

    /* TODO: hacer mas generico esto: */
    virtual std::string loading () { return ""; }

    void change_state (const std::string& name);
    void enter_state (const std::string& name);
    void leave_state ();
    void update (int delta);

    boost::shared_ptr<gra::scene> get_scene ()
    {
	return m_scene;
    }

    core::task_manager& get_tasks ()
    {
	return *m_tasks;
    }

    core::key_forwarder& get_keys ()
    {
	return m_keys;
    }

    core::mouse_forwarder& get_mouse ()
    {
	return m_mouse;
    }

    void set_state_parent (boost::weak_ptr<state_manager> parent)
    {
	m_parent = parent;
    }

    boost::shared_ptr<state_manager> get_state_parent ()
    {
	return boost::shared_ptr<state_manager> (m_parent);
    }

private:
    core::key_forwarder m_keys;
    core::mouse_forwarder m_mouse;
    boost::shared_ptr<core::task_manager> m_tasks;
    boost::shared_ptr<gra::scene> m_scene;

    boost::weak_ptr<state_manager> m_parent;
};

} /* namespace game */
} /* namespace yage */

#endif /* YAGE_STATE_H_ */
