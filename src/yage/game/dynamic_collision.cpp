/**
 *  Time-stamp:  <2009-06-14 17:22:56 raskolnikov>
 *
 *  @file        dynamic_collision.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 21 17:45:58 2009
 *
 *  Implementación de dynamic_collision.
 *
 *  @todo Muchos de los tests han sido implementados cutremente,
 *        hay que limpiar el código y hacer que los test prueben
 *        realmente los volúmenes que se piden.
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

#include <cfloat>

#include "collision_util.hpp"
#include "dynamic_collision.hpp"

using namespace yage::base;

namespace yage
{
namespace game
{

bool dynamic_collision::test (const collidable& a, const collidable& b,
			      const base::point3f& delta)
{
    m_delta = delta;
    return boost::apply_visitor (*this, a, b);
}

bool dynamic_collision::operator () (const sphere& sa, const sphere& sb)
{
    point3f s = sa.center - sb.center;
    float r = sa.rad + sb.rad;
    float c = s.sq_length () - r * r;

    /* Collisionan al principio */
    if (c < 0.0f) {
	m_time = 0.0f;
	return true;
    }

    float a = m_delta.sq_length ();
    if (a < EPSILON)    /* No se mueven. */
	return false;
    float b = m_delta.dot (s);
    if (b >= 0.0f)      /* No se acercan mutuamente. */
	return false;
    float d = b * b - a * c;
    if (d < 0.0f)       /* No hay solición real a la ecuación. */
	return false;

    m_time = (-b - std::sqrt (d)) / a;
    if (m_time <= 1.0)
	return true;

    return false;
}

bool dynamic_collision::operator () (const capsule& a, const capsule& b)
{
    /* Hack */
    sphere as (a.p1, a.rad);
    sphere bs (b.p1, b.rad);

    if ((*this) (as, bs)) {
	point3f dest = as.center + m_delta * m_time * (1 - EPSILON);
	m_normal =
	    (base::point3f (dest[0], 0, dest[2]) -
	     base::point3f (bs.center[0], 0, bs.center[2])).normalize ();
	return true;
    }
    
    return false;
}

bool dynamic_collision::operator () (const aabb& a, const aabb& b)
{
    /* HACK para que no falle el test camara-personaje */
    return false;
}

bool dynamic_collision::operator () (const sphere& a, const capsule& b)
{
    if ((*this) (a, sphere (b.p1, b.rad))) {
    	point3f dest = b.p1 + m_delta * m_time * (1 - EPSILON);
	m_normal =
	    (base::point3f (dest[0], 0, dest[2]) -
	     base::point3f (a.center[0], 0, a.center[2])).normalize ();
	return true;
    }
    return false;
}

bool dynamic_collision::operator () (const sphere& s, const aabb& b)
{   
    /* Obtenemos una AABB expandiendo b por el radio de la esfera */
    aabb e = b;
    e.min[0] -= s.rad; e.min[1] -= s.rad; e.min[2] -= s.rad;
    e.max[0] += s.rad; e.max[1] += s.rad; e.max[2] += s.rad;

    /* Intersecamos un rayo contra la AABB expandida.*/
    point3f p;
    if (!intersect_ray_aabb (s.center, m_delta, e, m_time, p) ||
	m_time > 1.0f)
        return false;
    
    /* Buscamos las caras en de b en las que p cae */
    int u = 0, v = 0;
    if (p[0] < b.min[0]) u |= 1;
    if (p[0] > b.max[0]) v |= 1;
    if (p[1] < b.min[1]) u |= 2;
    if (p[1] > b.max[1]) v |= 2;
    if (p[2] < e.min[2]) u |= 4;
    if (p[2] > e.max[2]) v |= 4;

    /* Componemos las pruebas en un bitmask (nota: aquí u + v == u | v) */
    int m = u + v;

    /* Segmento del movimiento de la esfera. */
    point3f p1 = s.center, p2 = s.center + m_delta;

#define corner(b, n)  (((n) & 1) ? (b).max : (b).min)
    
    /* Si los 3 bits están activados estamos en una región de vertice */
    if (m == 7) {
	float tmin = FLT_MAX;

	if (intersect_segment_capsule (p1, p2, corner (b, v), corner (b, v ^ 1), s.rad, m_time))
	    tmin = std::min (m_time, tmin);    
	if (intersect_segment_capsule (p1, p2, corner (b, v), corner (b, v ^ 2), s.rad, m_time))
	    tmin = std::min (m_time, tmin);
	if (intersect_segment_capsule (p1, p2, corner (b, v), corner (b, v ^ 4), s.rad, m_time))
	    tmin = std::min (m_time, tmin);

	if (tmin == FLT_MAX)
	    return false;
	
	m_time = tmin;
	return true;
    }
    
    /* Si solo hay 1 bit entonces estamos en una cara */
    if ((m & (m - 1)) == 0)
	return true;
	    
    /* Si no es un lado */
    return intersect_segment_capsule (p1, p2, corner (b, u ^ 7), corner (b, v), s.rad, m_time);

#undef corner
}

bool dynamic_collision::operator () (const capsule& a, const aabb& b)
{    
    /* Cambiamos el test por probar las dos esferas */
    float t1, t2;
    bool r1, r2, ret = false;
    sphere s;
    s.rad = a.rad;

    s.center = a.p1;
    r1 = (*this) (s, b);
    t1 = m_time;

    s.center = a.p2;
    r2 = (*this) (s, b);
    t2 = m_time;

    base::point3f dest;
    if (r1 && r2) {
	if (t1 < t2) {
	    m_time = t1;
	    dest = a.p1;
	} else {
	    m_time = t2;
	    dest = a.p2;
	}
	ret = true;
    } else if (r1) {
	m_time = t1;
	ret = true;
	dest = a.p1;
    } else if (r2) {
	dest = a.p2;
	m_time = t2;
	ret = true;
    }
    
    if (ret) {
	dest = dest + m_delta * m_time * (1 - EPSILON);
	
	float diff_max_x = dest[0] - b.max[0];
	float diff_min_x = b.min[0] - dest[0];
	float diff_max_z = dest[2] - b.max[2];
	float diff_min_z = b.min[2] - dest[2];
    
	if (diff_max_x >= 0 &&
	    diff_max_x >= diff_max_z &&
	    diff_max_x >= diff_min_z)
	    m_normal = base::point3f (1, 0, 0);
	else if (diff_max_z >= 0 &&
		 diff_max_z >= diff_max_x &&
		 diff_max_z >= diff_min_x)
	    m_normal = base::point3f (0, 0, 1);
	else if (diff_min_x >= 0 &&
		 diff_min_x >= diff_max_z &&
		 diff_min_x >= diff_min_z)
	    m_normal = base::point3f (-1, 0, 0);
	else if (diff_min_z >= 0 &&
		 diff_min_z >= diff_max_x &&
		 diff_min_z >= diff_min_x)
	    m_normal = base::point3f (0, 0, -1);
    }
    
    return ret;
}

} /* namespace game */
} /* namespace yage */
