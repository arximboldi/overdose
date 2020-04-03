/**
 *  @file        fog.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 21 21:27:35 2009
 *
 *  Interfaz de la clase fog.
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

#ifndef YAGE_FOG_H_
#define YAGE_FOG_H_

#include <SDL/SDL_opengl.h>
#include <boost/shared_ptr.hpp>
#include <yage/base/point4.hpp>

namespace yage
{
namespace gra
{

class fog
{
public:
    enum fog_mode
    {
	EXP    = GL_EXP,
	EXP2   = GL_EXP2,
	LINEAR = GL_LINEAR
    };

    fog ();
    void enable ();
    void update ();
    void disable ();

    void set_color (const base::point4f& c)
    {
	m_color = c;
    }

    const base::point4f& get_color () const
    {
	return m_color;
    }

    void set_mode (fog_mode mode)
    {
	m_mode = mode;
    }

    void set_density (float density)
    {
	m_density = density;
    }

    void set_start (float start)
    {
	m_start = start;
    }

    void set_end (float end)
    {
	m_end = end;
    }

    float get_density () const
    {
	return m_density;
    }

private:
    fog_mode m_mode;
    float    m_density;
    float    m_start;
    float    m_end;

    base::point4f m_color;
};

typedef boost::shared_ptr<fog> fog_ptr;

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_FOG_H_ */
