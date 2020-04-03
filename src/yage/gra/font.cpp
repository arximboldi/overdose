/**
 *  Time-stamp:  <2009-05-18 12:17:47 raskolnikov>
 *
 *  @file        font.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 17 21:00:21 2009
 *
 *  Implementación de la clase font.
 *  @todo Añadir soporte para cadenas no UTF8.
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
#include "texture.hpp"
#include "font.hpp"

namespace yage
{
namespace gra
{

YAGE_DEFINE_ERROR_WHERE (font_error, "font");

font::font (const std::string& fname, int ptsize)
{
    m_font = TTF_OpenFont (fname.c_str (), ptsize);
    if (!m_font)
	throw font_error (std::string ("Could not load font: ") + fname);
}

font::~font ()
{
    TTF_CloseFont (m_font);
}

int font::get_height () const
{
    return TTF_FontHeight (m_font);
}

void font::get_size (const std::string& text,
		     int& w, int& h) const
{
    TTF_SizeUTF8 (m_font, text.c_str (), &w, &h);
}

int font::get_style () const
{
    return TTF_GetFontStyle (m_font);
}

void font::set_style (int st)
{
    TTF_SetFontStyle (m_font, st);
}

bool font::is_fixed_width () const
{
    return TTF_FontFaceIsFixedWidth (m_font);
}

boost::shared_ptr<texture>
font::render (const std::string& str,
	      const base::point3f& color,
	      render_mode mode)
{
    core::sdl_surface_ptr surf (render_surface (str, color, mode));
    
    boost::shared_ptr<texture> result (new texture (surf.get ()));
    return result;
}

SDL_Surface*
font::render_surface (const std::string& str,
		      const base::point3f& color,
		      render_mode mode)
{
    SDL_Color sdl_color = { color[0] * 255, color[1] * 255, color[2] * 255 };
    SDL_Surface* surf   = 0;
    
    switch (mode)
    {
    case SOLID:
	surf = TTF_RenderUTF8_Solid (m_font, str.c_str (), sdl_color);
	break;
    case SHADED:
    {
	SDL_Color bgcolor = {0, 0, 0};
	surf = TTF_RenderUTF8_Shaded (m_font, str.c_str (), sdl_color, bgcolor);
	break;
    }
    case BLENDED:
	surf = TTF_RenderUTF8_Blended (m_font, str.c_str (), sdl_color);
	break;
    default:
	break;
    }

    if (surf == 0)
	throw font_error (std::string ("Could not render text: ") + TTF_GetError ());

    return surf;
}

} /* namespace gra */
} /* namespace yage */
