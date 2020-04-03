/**
 *  Time-stamp:  <2009-06-14 11:52:53 raskolnikov>
 *
 *  @file        collidable.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 21 10:48:36 2009
 *
 *  Clases para la detección de colisiones.
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

#ifndef YAGE_COLLIDABLE_H_
#define YAGE_COLLIDABLE_H_

#include <yage/base/point3.hpp>
#include <yage/base/exception.hpp>
#include <boost/variant.hpp>

namespace yage
{
namespace game
{

YAGE_DECLARE_ERROR (base::yage_error, collision_error);

struct aabb
{
    base::point3f min;
    base::point3f max;

    aabb () {}
    
    aabb (const base::point3f& min_, const base::point3f& max_)
	: min (min_), max (max_)
    {}
};

struct capsule

{
    base::point3f p1;
    base::point3f p2;
    float         rad;
};

struct sphere
{
    base::point3f center;
    float         rad;

    sphere () {}
    
    sphere (const base::point3f& center_, float rad_)
	: center (center_), rad (rad_)
    {}
};

typedef boost::variant <
    capsule,
    sphere,
    aabb>
collidable;

void translate_collidable (collidable& col,
			   const base::point3f& pos);

} /* namespace game */
} /* namespace yage */

#endif /* YAGE_COLLIDABLE_H_ */
