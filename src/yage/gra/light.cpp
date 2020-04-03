/**
 *  @file        light.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 14 19:09:40 2009
 *
 *  Implementación de la clase light.
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

#include "light.hpp"

namespace yage
{
namespace gra
{

light::light ()
    : m_handle (GL_NONE)
    , m_spot_exponent (0)
    , m_spot_cutoff (180)
    , m_constant_attenuation (1)
    , m_linear_attenuation (0)
    , m_quadratic_attenuation (0)
    , m_directional (false)
    , m_direction (0, 0, 1)
    , m_ambient (1, 1, 1, 1)
    , m_diffuse (1, 1, 1, 1)
    , m_specular (1, 1, 1, 1)
    , m_need_update (true)
{
}

void light::draw ()
{
    if (m_handle != GL_NONE)
    {
	if (m_need_update) {
	    glLighti (m_handle, GL_SPOT_EXPONENT, m_spot_exponent);
	    glLightf (m_handle, GL_SPOT_CUTOFF, m_spot_cutoff);

	    glLightf (m_handle, GL_CONSTANT_ATTENUATION, m_constant_attenuation);
	    glLightf (m_handle, GL_LINEAR_ATTENUATION, m_linear_attenuation);
	    glLightf (m_handle, GL_QUADRATIC_ATTENUATION, m_quadratic_attenuation);

	    glLightfv (m_handle, GL_AMBIENT, m_ambient.ptr ());
	    glLightfv (m_handle, GL_DIFFUSE, m_diffuse.ptr ());
	    glLightfv (m_handle, GL_SPECULAR, m_specular.ptr ());

	    m_need_update = false;
	}

	/* Siempre hay que actualizar la posición ya que depende
	   del estado actual de la matriz que puede haber cambiado */
	if (m_directional) {
	    base::point4f pos (m_direction.x (),
			       m_direction.y (),
			       m_direction.z (),
			       0);
	    glLightfv (m_handle, GL_POSITION,  pos.ptr ());
	} else {
	    base::point4f pos (0, 0, 0, 1);
	    glLightfv (m_handle, GL_POSITION,  pos.ptr ());
	}
    }
}

light::~light ()
{
    disable ();
}

void light::enable ()
{
    if (m_handle == GL_NONE)
    {
	m_handle = light_handle_allocator::self ().allocate ();
	glEnable (m_handle);
	m_need_update = true;
    }
}

void light::disable ()
{
    if (m_handle != GL_NONE)
    {
	glDisable (m_handle);
	light_handle_allocator::self ().release (m_handle);
	m_handle = GL_NONE;
    }
}

} /* namespace gra */
} /* namespace yage */
