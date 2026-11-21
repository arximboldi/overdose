/**
 *  @file        text.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 17 23:53:11 2009
 *
 *  Implementación de la clase text.
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
#include <cmath>

#include "yage/core/sdl_wrapper.hpp"
#include "text.hpp"
#include "texture.hpp"

namespace yage
{
namespace gra
{

YAGE_DEFINE_ERROR_WHERE (text_error, "text");

/* How many pixels one unit along x covers with the current transform. */
static float pixel_scale ()
{
    GLfloat projection [16], modelview [16];
    GLint viewport [4];
    glGetFloatv (GL_PROJECTION_MATRIX, projection);
    glGetFloatv (GL_MODELVIEW_MATRIX, modelview);
    glGetIntegerv (GL_VIEWPORT, viewport);

    /* The x axis, first column of the modelview, in clip space. */
    float x = 0, y = 0;
    for (int i = 0; i < 4; ++i) {
	x += projection [i * 4] * modelview [i];
	y += projection [i * 4 + 1] * modelview [i];
    }
    return std::hypot (x * viewport [2] / 2, y * viewport [3] / 2);
}

text::text (boost::shared_ptr<font> font,
	    const std::string& str,
	    const base::point3f& color,
	    font::render_mode mode)
    : m_need_update (true)
    , m_raster_size (font ? font->get_point_size () : 0)
    , m_font (font)
    , m_str (str)
    , m_color (color)
    , m_mode (mode)
    , m_real_width (0)
    , m_real_height (0)
    , m_width (0)
    , m_height (0)
{
}

boost::shared_ptr<texture> text::get_texture ()
{
    update_texture ();
    return m_tex;
}

void text::draw ()
{
    if (!m_str.empty ())
    {
	/* Rasterise the text at the size it ends up on the screen, so
	   that it stays sharp when the window or its scale changes. */
	if (m_font) {
	    int size = std::lround (m_font->get_point_size () * pixel_scale ());
	    size = std::clamp (size, 1, 4 * m_font->get_point_size ());
	    if (size != m_raster_size) {
		m_raster_size = size;
		m_need_update = true;
	    }
	}
	update_texture ();

	m_tex->enable ();

	glBegin (GL_QUADS);
	{
	    glTexCoord2f (0, 0);
	    glVertex2f (0, 0);
	    glTexCoord2f (1, 0);
	    glVertex2f (m_real_width, 0);
	    glTexCoord2f (1, 1);
	    glVertex2f (m_real_width, m_real_height);
	    glTexCoord2f (0, 1);
	    glVertex2f (0, m_real_height);
	}
	glEnd ();

	m_tex->disable ();
    }
}

void text::update_texture ()
{
    if (m_need_update)
    {
	if (m_str.empty ()) {
	    m_width = 0;
	    m_height = 0;
	} else {
	    if (!m_font)
		throw text_error ("Can not render text without a font.");

	    core::sdl_surface_ptr surf (
		m_font->render_surface (m_str, m_color, m_mode, m_raster_size));

	    if (!m_tex)
		m_tex.reset (new texture (surf.get ()));
	    else
		m_tex->reload (surf.get ());

	    /* Sizes are in units of the font's own size, whatever size
	       the text was rasterised at. */
	    float units = float (m_font->get_point_size ()) / m_raster_size;
	    m_width  = std::lround (m_tex->get_width () * units);
	    m_height = std::lround (m_tex->get_height () * units);
	    m_real_width  = m_tex->get_real_width () * units;
	    m_real_height = m_tex->get_real_height () * units;

	    if (m_mode == font::BLENDED)
		m_tex->set_blending (true);
	}

	m_need_update = false;
    }
}

size_t text::get_width ()
{
    update_texture ();
    return m_width;
}

size_t text::get_height ()
{
    update_texture ();
    return m_height;
}

} /* namespace gra */
} /* namespace yage */
