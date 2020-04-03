/**
 *  @file        static_collision.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 21 10:52:42 2009
 *
 *  Implementación de la clase collision.
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

#include "collision_util.hpp"
#include "static_collision.hpp"

using namespace yage::base;

namespace yage
{
namespace game
{

bool static_collision::test (const collidable& a, const collidable& b)
{
    return boost::apply_visitor (*this, a, b);
}

bool static_collision::operator () (const sphere& a, const sphere& b)
{
    float rad = a.rad + b.rad;
    return (a.center - b.center).sq_length () < rad * rad;
}

bool static_collision::operator () (const capsule& a, const capsule& b)
{
    float s, t;
    point3f c1, c2;
    float dist2 = closest_pt_segment_segment (
	a.p1, a.p2, b.p1, b.p2, s, t, c1, c2);
    float radius = a.rad + b.rad;
    return dist2 <= radius * radius;
}

bool static_collision::operator () (const aabb& a, const aabb& b)
{
    if (a.max[0] < b.min[0] || a.min[0] > b.max[0]) return false;
    if (a.max[1] < b.min[1] || a.min[1] > b.max[1]) return false;
    if (a.max[2] < b.min[2] || a.min[2] > b.max[2]) return false;

    return true;
}

bool static_collision::operator () (const sphere& a, const capsule& b)
{
    float dist2 = sq_dist_point_segment (b.p1, b.p2, a.center);
    float radius = a.rad + b.rad;
    return dist2 <= radius * radius;

    return false;
}

bool static_collision::operator () (const sphere& a, const aabb& b)
{
    bool res = sq_dist_point_aabb (a.center, b) <= a.rad * a.rad;
    return res;
}

bool static_collision::operator () (const capsule& a, const aabb& b)
{
    /* TODO: Esto no funciona si la capsula no es paralela a los ejes,
       pero lo dejamos así porque por ahora estamos siempre
       paralelos a los ejes. */

    return
	std::min (sq_dist_point_aabb (a.p1, b),
		  sq_dist_point_aabb (a.p1, b))
	<= a.rad * a.rad;
}

} /* namespace game */
} /* namespace yage */
