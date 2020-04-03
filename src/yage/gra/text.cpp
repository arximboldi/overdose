/**
 *  Time-stamp:  <2009-06-12 18:51:06 raskolnikov>
 *
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

#include "yage/core/sdl_wrapper.hpp"
#include "text.hpp"
#include "texture.hpp"

namespace yage
{
namespace gra
{

YAGE_DEFINE_ERROR_WHERE (text_error, "text");

text::text (boost::shared_ptr<font> font,
	    const std::string& str,
	    const base::point3f& color,
	    font::render_mode mode)
    : m_need_update (true)
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
		m_font->render_surface (m_str, m_color, m_mode));

	    if (!m_tex)
		m_tex.reset (new texture (surf.get ()));
	    else
		m_tex->reload (surf.get ());

	    m_width  = m_tex->get_width ();
	    m_height = m_tex->get_height ();
	    m_real_width  = m_tex->get_real_width ();
	    m_real_height = m_tex->get_real_height ();
	    
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
