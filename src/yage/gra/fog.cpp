/**
 *  @file        fog.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 21 21:31:38 2009
 *
 *  Implementación de la clase fog.
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

#include "fog.hpp"

namespace yage
{
namespace gra
{

fog::fog ()
    : m_mode (EXP)
    , m_density (1)
    , m_start (0)
    , m_end (1)
    , m_color (0, 0, 0, 0)
{
}

void fog::enable ()
{
    update ();
    glEnable (GL_FOG);
}

void fog::update ()
{
    glFogi (GL_FOG_MODE, m_mode);
    glFogf (GL_FOG_DENSITY, m_density);
    glFogf (GL_FOG_START, m_start);
    glFogf (GL_FOG_END, m_end);
    glFogfv (GL_FOG_COLOR, m_color.ptr ());
    glHint(GL_FOG_HINT, GL_DONT_CARE);
}

void fog::disable ()
{
    glDisable (GL_FOG);
}

} /* namespace gra */
} /* namespace yage */
