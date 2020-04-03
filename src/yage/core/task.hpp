/**
 *  Time-stamp:  <2009-06-15 16:26:38 raskolnikov>
 *
 *  @file        task.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Wed May 13 19:29:32 2009
 *
 *  Interfaz de la clase task.
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

#ifndef YAGE_TASK_H_
#define YAGE_TASK_H_

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <list>

namespace yage
{
namespace core
{

class task_manager;

class task
{
public:
    typedef std::list<boost::shared_ptr<task> > task_list;
    
    task ();
    
    virtual ~task () {}

    virtual void update (int ms) = 0;
    
    void finish ();
    
    bool is_finished ()
    {
	return m_is_finished;
    }
	
    bool toggle_pause ()
    {
	return (m_is_paused = !m_is_paused);
    }
	
    bool is_paused ()
    {
	return m_is_paused;
    }
	
    boost::shared_ptr<task>
    add_next (boost::shared_ptr<task> next)
    {
	m_next.push_back (next);
	return next;
    }
	
    const task_list& get_next ()
    {
	return m_next;
    }

    void set_task_parent (boost::weak_ptr<task_manager> parent)
    {
	m_parent = parent;
    }
    
    boost::shared_ptr<task_manager> get_task_parent ()
    {
	return boost::shared_ptr<task_manager> (m_parent);
    }

private:
    bool m_is_finished;
    bool m_is_paused;
	
    std::list<boost::shared_ptr<task> > m_next;
    boost::weak_ptr<task_manager> m_parent;
};

typedef boost::shared_ptr<task> task_ptr;

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_TASK_H_ */
