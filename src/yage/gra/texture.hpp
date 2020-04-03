/*
 *  File:       texture.hpp
 *  Author:     Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  Date:       Sun May 10 17:44:21 2009
 *  Time-stamp: <2009-06-12 18:54:04 raskolnikov>
 *
 *  Interfaz de la clase texture.
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

#ifndef YAGE_TEXTURE_H_
#define YAGE_TEXTURE_H_

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include <boost/shared_ptr.hpp>

#include <yage/base/exception.hpp>

namespace yage
{
namespace gra
{

YAGE_DECLARE_ERROR (base::yage_error, texture_error);

class texture
{
public:
    texture (const std::string& fname);
    texture (SDL_Surface* surf);
    ~texture ();

    void reload (const std::string& fname);
    void reload (SDL_Surface* surf);

    void enable ();
    void disable ();

    size_t get_real_width () const
    {
	return m_real_width;
    }

    size_t get_real_height () const
    {
	return m_real_height;
    }
    
    size_t get_width () const
    {
	return m_width;
    }

    size_t get_height () const
    {
	return m_height;
    }

    void set_blending (bool blend)
    {
	m_blending = blend;
    }
    
private:
    void make_texture (SDL_Surface* surf, GLint filter);
	
    GLuint m_glid;
    size_t m_width;
    size_t m_height;
    size_t m_real_width;
    size_t m_real_height;

    bool m_blending;
};

typedef boost::shared_ptr<texture> texture_ptr;

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_TEXTURE_H_ */
