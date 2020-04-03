/**
 *  Time-stamp:  <2009-06-12 00:23:30 raskolnikov>
 *
 *  @file        2d_textured_plane.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 00:14:59 2009
 *
 *  Interfaz de la clase 2d_textured_plane.
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

#ifndef YAGE_2D_TEXTURED_PLANE_H_
#define YAGE_2D_TEXTURED_PLANE_H_

#include <yage/gra/drawable.hpp>

namespace yage
{

namespace gra
{
class texture;
}

namespace geo
{

class textured_plane_2d : public gra::drawable
{
public:
    typedef boost::shared_ptr<gra::texture> texture_ptr;

    textured_plane_2d (texture_ptr ptr = texture_ptr ());

    void draw ();
    
    void set_texture (texture_ptr ptr)
    {
	m_tex = ptr;
    }
    
private:
    texture_ptr m_tex;
};

} /* namespace geo */
} /* namespace yage */

#endif /* YAGE_2D_TEXTURED_PLANE_H_ */
