/**
 *  Time-stamp:  <2009-06-15 16:36:29 raskolnikov>
 *
 *  @file        trigger_task.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Mon Jun 15 16:18:00 2009
 *
 *  Interfaz de la clase trigger_task.
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

#ifndef YAGE_TRIGGER_TASK_H_
#define YAGE_TRIGGER_TASK_H_

#include <boost/function.hpp>
#include <yage/core/task.hpp>

namespace yage
{
namespace core
{

template <typename FuncType = boost::function0<void> >
class trigger_task : public task
{
public:
    typedef FuncType function_type;

    trigger_task (FuncType func)
	: m_func (func)
    {}

    void update (int)
    {
	m_func ();
	this->finish ();
    }
    
private:
    FuncType m_func;
};

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_TRIGGER_TASK_H_ */
