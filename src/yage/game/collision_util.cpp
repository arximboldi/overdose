/**
 *  Time-stamp:  <2009-06-15 21:48:57 raskolnikov>
 *
 *  @file        collision_util.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 21 12:21:56 2009
 *
 *  Implementación de las funciones de utilidad sobre geometría
 *  e intersección de volúmenes.
 *
 *  Cuidado con las erratas del Real-Time Collsision Detection:
 *   http://realtimecollisiondetection.net/books/rtcd/errata/
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

#include "yage/base/misc.hpp"
#include "collision_util.hpp"

using namespace yage::base;

namespace yage
{
namespace game
{

/* TODO !!! */
bool intersect_segment_capsule (const base::point3f& sa,
				const base::point3f& sb,
				const base::point3f& p,
				const base::point3f& q,
				float r, float& t)
{
    bool res = false;
    t = FLT_MAX;
    
    {
	float tt;
	if (intersect_segment_cylinder (sa, sb, p, q, r, tt) && tt < t) {
	    res = true;
	    t = tt;
	}
    }{
	float tt;
	if (intersect_segment_sphere (sa, sb, p, r, tt) && tt < t) {
	    res = true;
	    t = tt;
	}
    }{
	float tt;
	if (intersect_segment_sphere (sa, sb, q, r, tt) && tt < t) {
	    res = true;
	    t = tt;
	}
    }

    return res;
}

bool intersect_segment_sphere (const base::point3f& p,
			       const base::point3f& q,
			       const base::point3f& sc,
			       float sr, float& t)
{
    point3f d = (q - p).normalize ();
    point3f m = p - sc;
    float b = m.dot (d);
    float c = m.sq_length () - sr * sr;
    
    if (c > 0.0f && b > 0.0f)
	return false;

    float discr = b*b - c;
    if (discr < 0.0f)
	return false;
    
    t = -b - sqrt (discr);
    if (t < 0.0f)
	t = 0.0f;
    t /= (p - q).length ();
    
    return t <= 1.0f;
}

bool intersect_segment_cylinder (const base::point3f& sa,
				 const base::point3f& sb,
				 const base::point3f& p,
				 const base::point3f& q,
				 float r, float& t)
{
    point3f
	d = q - p,
	m = sa - p,
	n = sb - sa;
    
    float md = m.dot (d);
    float nd = n.dot (d);
    float dd = d.sq_length ();
    
    /* Comprobamos si el segmento esta fuera de las esquinas del cilindro */
    if (md < 0.0f && md + nd < 0.0f)
	return false; /* Fuera del lado p */
    if (md > dd && md + nd > dd)
	return false; /* Fuera del lado q */
    
    float nn = n.sq_length ();
    float mn = m.dot (n);
	
    float a = dd * nn - nd * nd;
    float k = m.sq_length () - r * r;
    float c = dd * k - md * md;
    
    if (std::abs (a) < EPSILON) {
        /* El segmento es paralelo */
        if (c > 0.0f)
	    return false;
	
	/* Sabemos que intersecan, asi que busacamos como interseca */
        if (md < 0.0f)
	    t = -mn / nn; /* Interseca con en lado p */
        else if (md > dd)
	    t = (nd - mn) / nn; /* Interseca con el lado q */
        else
	    t = 0.0f; /* Dentro del cilindro*/
        return true;
    }
    
    float b = dd * mn - nd * md;
    float discr = b * b - a * c;
    if (discr < 0.0f)
	return false; /* No hay soluciones reales */

    float t0 = t = (-b - std::sqrt (discr)) / a;
    if (md + t * nd < 0.0f) {
	/* Interseccion fuera del cilindro por el lado 'p'*/
        if (nd <= 0.0f)
	    return false; /* El segmento apunta hacia afuera */
        t = -md / nd;
	
        /* Hay intersección si Dot(S(t) - p, S(t) - p) <= r^2 */
        if (k + t * (2.0f * mn + t * nn) <= 0.0f)
	    return false;
    } else if (md + t * nd > dd) {
        /* Interseccion por el lado q */
        if (nd >= 0.0f)
	    return false; /* El segmento va hacia afuera */
        t = (dd - md) / nd;
	
        /* Intersección si Dot(S(t) - q, S(t) - q) <= r^2 */
        if (k + dd - 2.0f * md + t * (2.0f * (mn - nd) + t * nn) <= 0.0f)
	    return true;
    }
    t = t0;

    /* Entre los end-caps */
    return t >= 0.0f && t <= 1.0f;

    /* Este codigo esta documentado en las erratas del libro */
#if 0
    t = (-b - std::sqrt (discr)) / a;
    if (t < 0.0f || t > 1.0f)
	return false; /* Interseccion fuera del segmento */
    if (md + t * nd < 0.0f) {
	/* Interseccion fuera del cilindro por el lado 'p'*/
	if (nd <= 0.0f)
	    return false;

	t = -md / nd;
	/* Hay intersección si Dot(S(t) - p, S(t) - p) <= r^2 */
	return k + t * (2.0f * mn + t * nn) <= 0.0f;
    } else if (md + t * nd > dd) {
	/* Intersección fuera del lado 'q' */
	if (nd >= 0.0f)
	    return false;
	
	t = (dd - md) / nd;
	/* Hay intersección si Dot(S(t) - q, S(t) - q) <= r^2 */
	return k + dd - 2 * md + t * (2 * (mn - nd) + t * nn) <= 0.0f;
    }
    /* El segmento interseca por en medio */
    return true;
#endif
}

bool intersect_ray_aabb (const base::point3f& p,
			 const base::point3f& d,
			 aabb a, float& tmin,
			 base::point3f& q)
{
    tmin = 0.0f;
    float tmax = FLT_MAX;

    for (int i = 0; i < 3; i++) {
	if (std::abs (d[i]) < EPSILON) {
	    /* El rayo es paralelo al slab. No colisiona si el rayo no está en el slab. */
	    if (p[i] < a.min[i] || p[i] > a.max[i]) return 0;
	} else {
	    /* Calculamos el valor de intersección t del rayo con
	       el plano cercano y lejano del slab */
	    float ood = 1.0f / d[i];
	    float t1 = (a.min[i] - p[i]) * ood;
	    float t2 = (a.max[i] - p[i]) * ood;

            /* t1 con el plano cercano y t2 con el lejano*/
	    if (t1 > t2)
		std::swap (t1, t2);

	    /* Ajustamos los intervalos a la colisión */
	    if (t1 > tmin)
		tmin = t1;
	    if (t2 < tmax) /* Putas erratas!! */
		tmax = t2;

	    /* No hay colisión */
	    if (tmin > tmax)
		return false;
	}
    }
    
    q = p + d * tmin;
    return true;
}

float sq_dist_point_segment (const base::point3f& a,
			     const base::point3f& b,
			     const base::point3f& c)
{
    point3f
	ab = b - a,
	ac = c - a,
	bc = c - b;

    float e = ac.dot (ab);
    
    /* Si c se proyecta fuera de a-b */
    if (e <= 0.0f)
	return ac.sq_length ();
    
    float f = ab.sq_length ();
    if (e >= f)
	return bc.sq_length ();

    /* Si c se proyecta dentro de a-b */
    return ac.sq_length () - e * e / f;
}

float sq_dist_point_line (const base::point3f& a,
			  const base::point3f& b,
			  const base::point3f& c)
{
    point3f
	ab = b - a,
	ac = c - a,
	bc = c - b;

    float e = ac.dot (ab);
    float f = ab.sq_length ();
    
    /* Si c se proyecta dentro de a-b */
    return ac.sq_length () - e * e / f;
}

float closest_pt_segment_segment (const base::point3f& p1,
				  const base::point3f& q1,
				  const base::point3f& p2,
				  const base::point3f& q2,
				  float &s, float &t,
				  base::point3f& c1,
				  base::point3f& c2)
{
    point3f d1 = q1 - p1;   /* Vector dirección del segmento S1 */
    point3f d2 = q2 - p2;   /* Vector dirección del segmento S2 */
    point3f r  = p1 - p2;
    float a   = d1.sq_length ();
    float e   = d2.sq_length ();
    float f   = d2.dot (r);

    /* Comprobar si alguno o ambos segmentos se degeneran en */
    if (a <= EPSILON && e <= EPSILON) {
	/* Los dos segmentos son puntos. */
	s = t = 0.0f;
	c1 = p1;
	c2 = p2;
	return (c1 - c2).sq_length ();
    }
    if (a <= EPSILON) {
	/* El primer segmento es un punto */
	s = 0.0f;
	t = f / e; /* s = 0 => t = (b*s + f) / e = f / e */
	t = clamp (t, 0.0f, 1.0f);
    } else {
	float c = d1.dot (r);
	if (e <= EPSILON) {
	    /* El segundo segmento degenera en punto. */
	    t = 0.0f;
	    s = clamp (-c / a, 0.0f, 1.0f); /* t = 0 => s = (b*t - c) / a = -c / a */
	} else {
	    /* Caso general no degenerado */
	    float b = d1.dot (d2);
	    float denom = a*e - b*b; /* Siempre no negativo */
	    
	    /* Si los segmentos no son paralelos, calcular el punto más cercano
	       de L1 a L2 y encerrar en el segmento S1. Si no tomar un s
	       arbitrario (aquí 0). */
	    if (denom != 0.0f)
		s = clamp ((b*f - c*e) / denom, 0.0f, 1.0f);
	    else
		s = 0.0f;
	    
	    /* Calcular el punto de L2 más cercano a S1(s) usando
	       t = Dot((P1 + D1*s) - P2,D2) / Dot(D2,D2) = (b*s + f) / e */
	    t = (b*s + f) / e;

            /* Si t en [0,1] hecho. Si no encerrar t, recalcular s para el nuevo valor
	       de t usando s = Dot((P2 + D2*t) - P1,D1) / Dot(D1,D1)= (t*b - c) / a
	       y encerrar s en [0, 1] */
	    if (t < 0.0f) {
		t = 0.0f;
		s = clamp (-c / a, 0.0f, 1.0f);
	    } else if (t > 1.0f) {
		t = 1.0f;
		s = clamp ((b - c) / a, 0.0f, 1.0f);
	    }
	}
    }
    
    c1 = p1 + d1 * s;
    c2 = p2 + d2 * t;

    return (c1 - c2).sq_length ();
}

float sq_dist_point_aabb (const base::point3f& p,
			  const aabb& b)
{
    float sqdist = 0.0f;

    for (int i = 0; i < 3; i++) {
	float v = p[i];
	if (v < b.min[i])
	    sqdist += (b.min[i] - v) * (b.min[i] - v);
	if (v > b.max[i])
	    sqdist += (v - b.max[i]) * (v - b.max[i]);
    }
    
    return sqdist;
}

} /* namespace game */
} /* namespace yage */
