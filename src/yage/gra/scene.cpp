/**
 *  Time-stamp:  <2009-06-15 12:48:00 raskolnikov>
 *
 *  @file        scene.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 21 20:47:58 2009
 *
 *  Implementación de la clase scene.
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
#include "camera.hpp"
#include "scene.hpp"
#include "fog.hpp"

namespace yage
{
namespace gra
{

void scene::render (int vp_width, int vp_height)
{
    /* Dibujamos la escena */
    setup_perspective (vp_width, vp_height);
    {
	if (m_camera)
	    m_camera->apply_model_rotation ();
	if (m_sky) {
	    glPushMatrix ();
	    glScalef(m_sky_scale[0], m_sky_scale[1], m_sky_scale[2]);
	    m_sky->draw ();
	    glPopMatrix ();
	}

	if (m_camera)
	    m_camera->apply_model_translation ();
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHTING);

	if (m_fog)
	    m_fog->enable ();
	
	m_root.draw ();

	if (m_fog)
	    m_fog->disable ();
	
	glDisable (GL_LIGHTING);
	glDisable (GL_DEPTH_TEST);
    }
    
    /* Dibujamos el HUD bidimensional */
    setup_ortho (vp_width, vp_height);
    {
	glPushMatrix ();
	m_hud_root.draw ();
	glPopMatrix ();	    
    }
}

void scene::setup_perspective (int vp_width, int vp_height)
{
    glMatrixMode (GL_PROJECTION);  
    glLoadIdentity ();

    if (m_camera)
	m_camera->apply_projection (vp_width, vp_height);
    else
	gluPerspective (45.0, (GLdouble) vp_width / vp_height, 0.5, 1000.0);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

void scene::setup_ortho (int vp_width, int vp_height)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glOrtho (0.0f, vp_width, vp_height, 0.0f, -1.0f, 1.0f);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

} /* namespace gra */
} /* namespace yage */
