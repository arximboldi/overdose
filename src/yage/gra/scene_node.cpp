/**
 *  @file        scene_node.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 15:07:04 2009
 *
 *  Implementacion de scene_node
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

#include "scene_node.hpp"

namespace yage
{
namespace gra
{

scene_node::scene_node ()
    : m_position (0.0f, 0.0f, 0.0f)
    , m_scale (1.0f, 1.0f, 1.0f)
    , m_rotate (0, 0, 0, 0)
{
}

void scene_node::draw()
{
    glPushMatrix ();

    glTranslatef (m_position[0], m_position[1], m_position[2]);
    glRotatef (m_rotate[0], m_rotate[1], m_rotate[2], m_rotate[3]);
    glScalef (m_scale[0], m_scale[1], m_scale[2]);

    for (scene_node::iterator iter = begin (); iter != end (); ++iter)
	iter->draw ();

    for (draw_list::iterator it = m_drawables.begin(); it != m_drawables.end(); ++it)
	(*it)->draw ();

    glPopMatrix();
}

} /* namespace gra */
} /* namespace yage */
