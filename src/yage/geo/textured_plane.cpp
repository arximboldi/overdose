/**
 *  @file        textured_plane.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 17 18:23:25 2009
 *
 *  Implementación de textured_plane.
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

#include "textured_plane.hpp"

using namespace yage::base;

namespace yage
{
namespace geo
{

textured_plane::textured_plane (float htiles,
				float vtiles)
{
    const float l = 0.5;
    begin (QUADS);

    tex_coord (point2f (0, 0));
    point (point3f (0, l, -l));
    tex_coord (point2f (htiles, 0));
    point (point3f (0, l, l));
    tex_coord (point2f (htiles, vtiles));
    point (point3f (0, -l, l));
    tex_coord (point2f (0, vtiles));
    point (point3f (0, -l, -l));

    end ();
}


} /* namespace geo */
} /* namespace yage */
