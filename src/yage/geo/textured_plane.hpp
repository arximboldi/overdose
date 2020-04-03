/**
 *  @file        textured_plane.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 17 18:21:56 2009
 *
 *  Interfaz de textured_plane.
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

#ifndef YAGE_TEXTURED_PLANE_H_
#define YAGE_TEXTURED_PLANE_H_

#include <yage/geo/mesh.hpp>

namespace yage
{
namespace geo
{

class textured_plane : public mesh
{
public:
    textured_plane (float htiles = 1,
                    float vtiles = 1,
                    int hdiv = 1,
                    int vdiv = 1);
};

} /* namespace geo */
} /* namespace yage */

#endif /* YAGE_TEXTURED_PLANE_H_ */
