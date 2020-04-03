/**
 *  Time-stamp:  <2009-06-15 21:43:30 raskolnikov>
 *
 *  @file        collision_util.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 21 12:19:56 2009
 *
 *  Funciones de utilidad para la detección de colisiones, geometría,
 *  etc. Un libro interesante de dónde se han sacado algunas de
 *  estas funciones es:
 *    - Real-time collision detection, Christer Rricson, 2005.
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

#ifndef YAGE_COLLISION_UTIL_H_
#define YAGE_COLLISION_UTIL_H_

#include <yage/base/point3.hpp>
#include <yage/game/collidable.hpp>

namespace yage
{
namespace game
{

/* Valor de error usado para definir la igualdad de flotantes. */
static const float EPSILON = 0.000001;


bool intersect_segment_sphere (const base::point3f& p,
			       const base::point3f& q,
			       const base::point3f& sc,
			       float sr, float& t);

bool intersect_segment_capsule (const base::point3f& sa,
				const base::point3f& sb,
				const base::point3f& p,
				const base::point3f& q,
				float r, float& t);

bool intersect_segment_cylinder (const base::point3f& sa,
				 const base::point3f& sb,
				 const base::point3f& p,
				 const base::point3f& q,
				 float r, float& t);

bool intersect_ray_aabb (const base::point3f& p,
			 const base::point3f& d,
			 aabb a, float &tmin,
			 base::point3f& q);

float sq_dist_point_segment (const base::point3f& a,
			     const base::point3f& b,
			     const base::point3f& c);

float sq_dist_point_line (const base::point3f& a,
			  const base::point3f& b,
			  const base::point3f& c);

float closest_pt_segment_segment (const base::point3f& p1,
				  const base::point3f& q1,
				  const base::point3f& p2,
				  const base::point3f& q2,
				  float &s, float &t,
				  base::point3f& c1,
				  base::point3f& c2);

float sq_dist_point_aabb (const base::point3f& p,
			  const aabb& b);

} /* namespace game */
} /* namespace yage */

#endif /* YAGE_COLLISION_UTIL_H_ */
