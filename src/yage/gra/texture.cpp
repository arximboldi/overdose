/*
 *  File:       texture.cpp
 *  Author:     Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  Date:       Sun May 10 17:49:25 2009
 *  Time-stamp: <2009-06-13 17:58:18 raskolnikov>
 *
 *  Implementación de la clase texture.
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

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "yage/core/sdl_wrapper.hpp"
#include "texture.hpp"

namespace yage
{
namespace gra
{

YAGE_DEFINE_ERROR_WHERE (texture_error, "texture");

static int power_of_two(int input)
{
    int value = 1;

    while (value < input)
	value <<= 1;
    return value;
}

/* TODO: Mejorar el control de errores aquí. */
void texture::make_texture (SDL_Surface* surf, GLint filter)
{
    m_width = surf->w;
    m_height = surf->h;
    
    m_real_width  = power_of_two (surf->w);
    m_real_height = power_of_two (surf->h);
    
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    core::sdl_surface_ptr conv (
	SDL_CreateRGBSurface (SDL_SWSURFACE, m_real_width, m_real_height, 32,
			      0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff));
#else
    core::sdl_surface_ptr conv (
	SDL_CreateRGBSurface (SDL_SWSURFACE, m_real_width, m_real_height, 32,
			      0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000));
#endif

    Uint32 saved_flags;
    Uint8 saved_alpha;
    saved_flags = surf->flags;
    saved_alpha = surf->format->alpha;

    if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
 	SDL_SetAlpha (surf, 0, 0);
 
    SDL_BlitSurface (surf, 0, conv.get (), 0);

    if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
 	SDL_SetAlpha (surf, saved_flags, saved_alpha);
     
    glGenTextures (1, &m_glid);
    glBindTexture (GL_TEXTURE_2D, m_glid);
    
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glPixelStorei (GL_UNPACK_ROW_LENGTH, conv->pitch / conv->format->BytesPerPixel);
    glTexImage2D (GL_TEXTURE_2D, 0, 4, m_real_width, m_real_height, 0,
		  GL_RGBA, GL_UNSIGNED_BYTE, conv->pixels);
    glPixelStorei (GL_UNPACK_ROW_LENGTH, 0);
}

texture::texture (const std::string& fname)
    : m_blending (false)
{    
    SDL_Surface* tex_image = IMG_Load (const_cast<char*> (fname.c_str ()));

    if (tex_image) {
	make_texture (tex_image, GL_LINEAR);
	SDL_FreeSurface (tex_image);
    } else {
	throw texture_error (std::string ("Error while loading texture: ") + fname +
			     " | " + IMG_GetError ());
    }
}

texture::texture (SDL_Surface* surf)
{
    make_texture (surf, GL_LINEAR);
}

void texture::reload (const std::string& fname)
{
    glDeleteTextures (1, &m_glid);
    
    SDL_Surface* tex_image = IMG_Load (const_cast<char*> (fname.c_str ()));

    if (tex_image) {
	make_texture (tex_image, GL_LINEAR);
	SDL_FreeSurface (tex_image);
    } else {
	throw texture_error (std::string ("Error while loading texture: ") + fname +
			     " | " + IMG_GetError ());
    }
}

void texture::reload (SDL_Surface* surf)
{
    glDeleteTextures (1, &m_glid);
    make_texture (surf, GL_LINEAR);
}

texture::~texture ()
{
    glDeleteTextures (1, &m_glid);
}

void texture::enable ()
{
    glEnable (GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, m_glid);

    if (!m_blending) {
	glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    } else {
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable (GL_DEPTH_TEST);
    }
}

void texture::disable ()
{
    if (m_blending) {
	glEnable (GL_DEPTH_TEST);
	glDisable (GL_BLEND);
    }
    
    glDisable (GL_TEXTURE_2D);
}

} /* namespace gra */
} /* namespace yage */
