/**
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

#include <algorithm>
#include <SDL_opengl.h>
#include "camera.hpp"
#include "scene.hpp"
#include "fog.hpp"
#include "projection.hpp"

namespace yage
{
namespace gra
{

void scene::render (int vp_width, int vp_height, int hud_width, int hud_height)
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
    setup_ortho (vp_width, vp_height, hud_width, hud_height);
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
	perspective (45.0, (GLdouble) vp_width / vp_height, 0.5, 1000.0);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

void scene::setup_ortho (int vp_width, int vp_height, int hud_width, int hud_height)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    /* Fit the HUD in the viewport, centred, keeping its aspect ratio. */
    double scale = std::min (double (vp_width) / hud_width,
			     double (vp_height) / hud_height);
    double width = vp_width / scale;
    double height = vp_height / scale;
    double left = (hud_width - width) / 2;
    double top = (hud_height - height) / 2;
    glOrtho (left, left + width, top + height, top, -1.0, 1.0);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

} /* namespace gra */
} /* namespace yage */
