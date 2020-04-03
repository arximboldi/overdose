/**
 *  Time-stamp:  <2009-05-19 11:48:29 raskolnikov>
 *
 *  @file        textured_hemisphere.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Tue May 19 11:04:57 2009
 *
 *  Interfaz de la clase textured_hemisphere.
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

#ifndef YAGE_TEXTURED_HEMISPHERE_H_
#define YAGE_TEXTURED_HEMISPHERE_H_

#include <yage/geo/mesh.hpp>

namespace yage
{
namespace geo
{

class textured_hemisphere : public mesh
{
public:
    textured_hemisphere (size_t divisions = 20);
};

} /* namespace geo */
} /* namespace yage */

#endif /* YAGE_TEXTURED_HEMISPHERE_H_ */
