/**
 *  Time-stamp:  <2009-06-16 10:59:12 raskolnikov>
 *
 *  @file        function_animation.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sat Jun 13 12:50:32 2009
 *
 *  Interfaz de la clase function_animation y algunas funciones
 *  y functores útiles.
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

#ifndef YAGE_FUNCTION_ANIMATION_H_
#define YAGE_FUNCTION_ANIMATION_H_

#include <boost/function.hpp>
#include <yage/gra/animation.hpp>

namespace yage
{
namespace gra
{

template <typename T, typename U>
T linear_function (T min, T max, U x)
{
    return min + (max - min) * x; 
}

template <typename U>
U sinusoid (U x)
{
    return std::sin (x * M_PI / 2); 
}

template <typename T>
class function_animation : public animation
{
public:
    typedef boost::function1<void, T> function_type;

    function_animation (function_type func,
			float duration = 1.0f)
	: m_func (func)
	, m_duration (duration)
    {
    }
    
    void animate (float percent)
    {
	m_func (percent);
    }
    
    float get_duration ()
    {
	return m_duration;
    }

private:
    function_type m_func;
    float m_duration;
};

template <typename T>
boost::shared_ptr<function_animation<T> >
create_function_animation (typename function_animation<T>::function_type func,
			   float duration = 1.0f)
{
    return boost::shared_ptr<function_animation<T> > (
	new function_animation<T> (func, duration));
}

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_FUNCTION_ANIMATION_H_ */
