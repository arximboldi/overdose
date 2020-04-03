/**
 *  Time-stamp:  <2009-06-15 11:30:58 raskolnikov>
 *
 *  @file        static_drawable.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Mon May 11 15:47:26 2009
 *
 *  Interfaz de la clase static_drawable.
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

#ifndef YAGE_STATIC_DRAWABLE_H_
#define YAGE_STATIC_DRAWABLE_H_

#include <SDL/SDL_opengl.h>

#include <yage/base/singleton.hpp>
#include <yage/base/handle_allocator.hpp>

#include <yage/gra/drawable.hpp>

namespace yage
{
namespace gra
{

typedef
base::singleton_holder<base::handle_allocator<GLuint, base::count_creator_policy> >
display_list_handle_allocator;

class static_drawable : public drawable
{
public:
    static_drawable (drawable& d);
    ~static_drawable ();
    void draw ();

private:
    GLuint m_handle;
};

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_STATIC_DRAWABLE_H_ */
