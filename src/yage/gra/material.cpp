/*
 *  File:       material.cpp
 *  Author:     Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  Date:       Sun May 10 18:36:08 2009
 *
 *  Implementación de la clase material.
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

#include <SDL/SDL_opengl.h>
#include "material.hpp"

using namespace yage::base;

namespace yage
{
namespace gra
{

material::material (const point4f& ambient,
		    const point4f& diffuse,
		    const point4f& specular,
		    int shininess)
    : m_ambient (ambient)
    , m_diffuse (diffuse)
    , m_specular (specular)
    , m_shininess (shininess)
{
}

void material::apply ()
{
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT,   &m_ambient [0]);
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE,   &m_diffuse [0]);
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR,  &m_specular [0]);
    glMaterialf  (GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
}

} /* namespace gra */
} /* namespace yage */
