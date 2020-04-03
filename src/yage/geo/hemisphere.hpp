/**
 *  Time-stamp:  <2009-05-11 13:30:20 raskolnikov>
 *
 *  @file        hemisphere.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 14:18:27 2009
 *
 *  Declaracion del tipo hemisphere
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

#ifndef YAGE_HEMISPHERE_H
#define YAGE_HEMISPHERE_H

#include <yage/geo/mesh.hpp>

namespace yage
{
namespace geo
{

class hemisphere : public mesh
{
public:
    hemisphere (size_t division = 20);
};

} /* namespace geo */
} /* namespace yage */

#endif /* YAGE_HEMISPHERE_H */
