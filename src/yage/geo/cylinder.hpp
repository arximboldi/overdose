/**
 *  Time-stamp:  <2009-05-11 13:35:14 raskolnikov>
 *
 *  @file        cylinder.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 12:08:36 2009
 *
 *  Declaracion de la clase geometrica cilindro.
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

#ifndef YAGE_CYLINDER_H
#define YAGE_CYLINDER_H

#include <yage/geo/multi_mesh.hpp>

namespace yage
{
namespace geo
{

class cylinder : public multi_mesh
{  
public:
    cylinder (size_t division = 20);
};

} /* namespace geo */
} /* namespace yage */

#endif /* YAGE_CYLINDER_H */
