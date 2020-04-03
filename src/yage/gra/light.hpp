/**
 *  @file        light.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 14 18:36:15 2009
 *
 *  Interfaz de la clase light.
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

#ifndef YAGE_LIGHT_H_
#define YAGE_LIGHT_H_

#include <SDL/SDL_opengl.h>

#include <yage/base/point3.hpp>
#include <yage/base/point4.hpp>
#include <yage/base/handle_allocator.hpp>
#include <yage/base/singleton.hpp>

#include <yage/gra/drawable.hpp>

namespace yage
{
namespace gra
{

typedef
base::singleton_holder<
    base::fixed_handle_allocator<GLenum, GL_LIGHT0, GL_LIGHT1>
    >
light_handle_allocator;

class light : public drawable
{
public:
    light ();
    ~light ();
    void enable ();
    void disable ();
    void draw ();

    void set_spot_exponent (int val)
    {
	m_spot_exponent = val;
	m_need_update = true;
    }

    void set_spot_cutoff (int val)
    {
	m_spot_cutoff = val;
	m_need_update = true;
    }

    void set_attenuation (float constant,
			  float quadratic,
			  float linear)
    {
	m_constant_attenuation = constant;
	m_linear_attenuation = linear;
	m_quadratic_attenuation = quadratic;
	m_need_update = true;
    }

    void set_directional (bool directional)
    {
	m_directional = directional;
	m_need_update = true;
    }

    void set_direction (const base::point3f& dir)
    {
	m_direction = dir;
	m_need_update = true;
    }

    void set_ambient (const base::point4f& ambient)
    {
	m_ambient = ambient;
	m_need_update = true;
    }

    void set_diffuse (const base::point4f& diffuse)
    {
	m_diffuse = diffuse;
	m_need_update = true;
    }

    void set_specular (const base::point4f& specular)
    {
	m_specular = specular;
	m_need_update = true;
    }

private:
    GLenum m_handle;

    GLint   m_spot_exponent;
    GLfloat m_spot_cutoff;

    GLfloat m_constant_attenuation;
    GLfloat m_linear_attenuation;
    GLfloat m_quadratic_attenuation;

    bool m_directional;

    base::point3f m_direction;
    base::point4f m_ambient;
    base::point4f m_diffuse;
    base::point4f m_specular;

    bool m_need_update;
};

typedef boost::shared_ptr<light> light_ptr;

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_LIGHT_H_ */
