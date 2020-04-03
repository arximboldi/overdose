/**
 *  @file        textured_plane_2d.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 00:18:09 2009
 *
 *  Implementación de la clase textured_plane_2d.
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

#include "yage/gra/texture.hpp"
#include "textured_plane_2d.hpp"

namespace yage
{
namespace geo
{

textured_plane_2d::textured_plane_2d (texture_ptr ptr)
    : m_tex (ptr)
{
}

void textured_plane_2d::draw ()
{
    if (m_tex)
    {
	float width = m_tex->get_real_width ();
	float height = m_tex->get_real_height ();

	m_tex->enable ();

	glBegin (GL_QUADS);
	{
	    glTexCoord2f (0, 0);
	    glVertex2f (0, 0);
	    glTexCoord2f (1, 0);
	    glVertex2f (width, 0);
	    glTexCoord2f (1, 1);
	    glVertex2f (width, height);
	    glTexCoord2f (0, 1);
	    glVertex2f (0, height);
	}
	glEnd ();

	m_tex->disable ();
    }

}

} /* namespace geo */
} /* namespace yage */
