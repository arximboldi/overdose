/**
 *  Time-stamp:  <2009-05-23 22:40:59 raskolnikov>
 *
 *  @file        task_manager.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Wed May 13 19:23:25 2009
 *
 *  Interfaz de la clase task_manager.
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

#ifndef YAGE_TASK_MANAGER_H_
#define YAGE_TASK_MANAGER_H_

#include <list>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <yage/core/task.hpp>

namespace yage
{
namespace core
{

class task_manager : public boost::enable_shared_from_this <task_manager>
{	    
public:
    void update (int ms);
    
    void add (boost::shared_ptr<task> t);
    void del (boost::shared_ptr<task> t);
	
    bool has_tasks ()
    {
	return !m_tasks.empty ();
    }

    void clear ()
    {
	m_tasks.clear ();
    }
    
private:
    typedef std::list<boost::shared_ptr<task> > task_list;
    task_list m_tasks;
};

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_TASK_MANAGER_H */
