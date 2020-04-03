/**
 *  @file        cube.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 11:56:58 2009
 *
 *  Clase cubo, declaración.
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

#ifndef YAGE_CUBE_H
#define YAGE_CUBE_H

#include <yage/base/point3.hpp>
#include <yage/geo/mesh.hpp>

namespace yage
{
namespace geo
{

class cube : public mesh
{
public:
    cube ();
};

} /* namespace geo */
} /* namespace yage */

#endif /* YAGE_CUBE_H */
