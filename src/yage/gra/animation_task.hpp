/**
 *  Time-stamp:  <2009-06-15 19:53:51 raskolnikov>
 *
 *  @file        animation_task.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 17 20:24:31 2009
 *
 *  Interfaz de la clase animation_task.
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

#ifndef YAGE_ANIMATION_TASK_H_
#define YAGE_ANIMATION_TASK_H_

#include <boost/shared_ptr.hpp>

#include <yage/base/misc.hpp>
#include <yage/core/task.hpp>
#include <yage/gra/animation.hpp>
#include <yage/gra/function_animation.hpp>

namespace yage
{
namespace gra
{

class animation_task : public core::task
		     , public animation
{
public:
    static const float DEFAULT_SPEED = 1;
    
    animation_task (boost::shared_ptr<animation> anim,
		    float speed = DEFAULT_SPEED,
		    bool loop = false);

    void update (int delta);

    void seek (float pos)
    {
	m_pos = base::clamp (pos, 0.0f, 1.0f);
    }
    
    void set_speed (float speed)
    {
	m_speed = speed;
    }

    float get_speed () const
    {
	return m_speed;
    }
    
    void set_animation (animation_ptr anim)
    {
	m_anim = anim;
    }

    animation_ptr get_animation ()
    {
	return m_anim;
    }
    
    void animate (float position)
    {
	m_pos = position;
    }

    void set_loop (bool loop)
    {
	m_loop = loop;
    }

    bool get_loop () const
    {
	return m_loop;
    }

    float get_duration ()
    {
	return m_anim->get_duration () * m_speed;
    }

    void set_length (float len)
    {
	m_len = len;
    }
    
private:
    animation_ptr m_anim;
    float m_len;
    float m_pos;
    float m_speed;
    bool  m_loop;
};

typedef boost::shared_ptr<animation_task> animation_task_ptr;

template<typename T>
animation_task_ptr
create_function_task (typename function_animation<T>::function_type func,
		      float duration = 1.0f,
		      bool loop = false)
{
    animation_task_ptr ret (
	new animation_task (create_function_animation<T> (func, duration),
			    animation_task::DEFAULT_SPEED,
			    loop));
    return ret;
}

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_ANIMATION_TASK_H_ */
