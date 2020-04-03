/**
 *  Time-stamp:  <2009-06-15 11:32:09 raskolnikov>
 *
 *  @file        static_drawable.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Mon May 11 15:47:01 2009
 *
 *  Implementación de la clase static_drawable.
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

#include "static_drawable.hpp"

namespace yage
{
namespace gra
{

static_drawable::static_drawable (drawable& d)
{
    m_handle = display_list_handle_allocator::self ().allocate ();
    
    glNewList (m_handle, GL_COMPILE);
    d.draw ();
    glEndList ();
}

static_drawable::~static_drawable ()
{
    glDeleteLists (m_handle, 1);
    display_list_handle_allocator::self ().release (m_handle);
}

void static_drawable::draw ()
{
    glCallList (m_handle);
}

} /* namespace gra */
} /* namespace yage */
