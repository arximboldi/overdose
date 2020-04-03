/**
 *  Time-stamp:  <2009-06-10 22:03:56 raskolnikov>
 *
 *  @file        point3.tpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 14:00:48 2009
 *
 *  Implementación de la clase point3
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

#ifndef YAGE_POINT3_T_
#define YAGE_POINT3_T_

namespace yage
{
namespace base
{

template <typename T>
point3<T> point3<T>::rotate (float theta, const point3& r)
{
    /* La implementación se basa en matrices, pero como no quiero
       implementar mi propia clase matriz y ademas asi es mas eficiente.

       El artículo que explica esto es:
       http://local.wasp.uwa.edu.au/~pbourke/geometry/rotate/

       En esa web hay articulos muy interesantes de geometría. */

    point3 q (0.0, 0.0, 0.0);
    double costheta, sintheta;

    costheta = std::cos (theta);
    sintheta = std::sin (theta);

    q[0] += (costheta + (1 - costheta) * r[0] * r[0]) * p[0];
    q[0] += ((1 - costheta) * r[0] * r[1] - r[2] * sintheta) * p[1];
    q[0] += ((1 - costheta) * r[0] * r[2] + r[1] * sintheta) * p[2];

    q[1] += ((1 - costheta) * r[0] * r[1] + r[2] * sintheta) * p[0];
    q[1] += (costheta + (1 - costheta) * r[1] * r[1]) * p[1];
    q[1] += ((1 - costheta) * r[1] * r[2] - r[0] * sintheta) * p[2];

    q[2] += ((1 - costheta) * r[0] * r[2] - r[1] * sintheta) * p[0];
    q[2] += ((1 - costheta) * r[1] * r[2] + r[0] * sintheta) * p[1];
    q[2] += (costheta + (1 - costheta) * r[2] * r[2]) * p[2];

    return q;
}

template <class T>
inline std::ostream& operator<< (std::ostream& os, const point3<T>& p)
{
    return os << '(' << p.x() << ',' << p.y() << ',' << p.z() <<  ')';
}

template <class T>
inline std::istream& operator>> (std::istream& is, point3<T>& p)
{
    char caracter;
    T x,y,z;
    is >> caracter >> x >> caracter >> y >> caracter >> z >> caracter;
    p = point3<T> (x,y,z);
    return is;
}

template <class T>
point3<T>::point3 ()
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
}

template <class T>
point3<T>::point3 (T x, T y, T z)
{
    p[0] = x;
    p[1] = y;
    p[2] = z;

}

template <class T>
point3<T>::point3 (const point3<T> &orig)
{
    p[0] = orig.x();
    p[1] = orig.y();
    p[2] = orig.z();
}

template <class T>
point3<T>::point3 (const float* orig)
{
    p[0] = orig [0];
    p[1] = orig [1];
    p[2] = orig [3];
}

template <class T>
void point3<T>::set (T x, T y, T z)
{
    p[0] = x;
    p[1] = y;
    p[2] = z;
}

template <class T>
void point3<T>::set_x (T x)
{
    p[0] = x;
}

template <class T>
void point3<T>::set_y (T y)
{
    p[1] = y;
}

template <class T>
void point3<T>::set_z (T z)
{
    p[2] = z;
}

template <class T>
T point3<T>::x () const
{
    return p[0];
}

template <class T>
T point3<T>::y () const
{
    return p[1];
}

template <class T>
T point3<T>::z () const
{
    return p[2];
}

template <class T>
T* point3<T>::ptr ()
{
    return p;
}

template <class T>
const T* point3<T>::ptr () const
{
    return p;
}

template <class T>
point3<T>& point3<T>::operator= (const point3<T>& po)
{
    p[0] = po.x ();
    p[1] = po.y ();
    p[2] = po.z ();
    return *this;
}

template <class T>
bool point3<T>::operator== (const point3<T>& po) const
{
    return
	p[0] == po.x () &&
	p[1] == po.y () &&
	p[2] == po.z (); 
}

template <class T>
bool point3<T>::operator!= (const point3<T>& po) const
{
    return
	p[0] != po.x () ||
	p[1] != po.y () ||
	p[2] != po.z (); 
}

template <class T>
T& point3<T>::operator[] (const int indice)
{
    return p[indice];
}

template <class T>
const T& point3<T>::operator[] (const int indice) const
{
    return p[indice];
}

template<class T>
point3<T>& point3<T>::operator += (const point3<T>& v)
{
    p[0] += v.p[0];
    p[1] += v.p[1];
    p[2] += v.p[2];
    return *this;
}
  
template<class T>
point3<T> point3<T>::operator+ (const point3<T>& v) const
{
    return point3<T>(v.p[0] + p[0], v.p[1] + p[1], v.p[2] + p[2]);
}

template<class T>
point3<T> point3<T>::operator- (const point3 &v) const
{
    return point3<T>(p[0] - v. p[0], p[1] - v.p[1], p[2] - v.p[2]);
}

template<class T>
T point3<T>::length () const
{
    return std::sqrt (p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
}

template<class T>
T point3<T>::sq_length () const
{
    return p[0]*p[0] + p[1]*p[1] + p[2]*p[2];
}

template<class T>
point3<T> point3<T>::operator* (const T& t) const
{
    return point3<T>(t * p[0], t * p[1], t * p[2]);
}

template<class T>
point3<T> point3<T>::operator* (const point3& v) const
{
    return point3<T>(v.p[0] * p[0], v.p[1] * p[1], v.p[2] * p[2]);
}

template<class T>
T point3<T>::dot (const point3& v) const
{
    return v.p[0] * p[0] + v.p[1] * p[1] + v.p[2] * p[2];
}

template<class T>
point3<T> point3<T>::cross (const point3& v) const
{
    return point3<T>(p[1]*v.p[2] - p[2]*v.p[1],
		     p[2]*v.p[0] - p[0]*v.p[2],
		     p[0]*v.p[1] - p[1]*v.p[0]);
}
 
template<class T>
point3<T> point3<T>::normalize () const
{
    float l = length();
    if (l == 0.0f) return point3<T>(0,0,0);
    return *this * (1.0f / l);
}

template<class T>
point3<T> point3<T>::normal (const point3& v) const
{
    point3<T> n = cross(v);
    T l = n.length();
    if (l == 0)
	return point3<T>(0, 0, 0);

    return n * (1.0f / l);
}

template<class T>
T point3<T>::cos (const point3& p) const
{
    return dot (p) / length () / p.length ();
}

template<class T>
bool point3<T>::operator< (const point3<T>& v) const
{
    return
	p[0] == v.p[0] ?
	p[1] == v.p[1] ?
	p[2] <  v.p[2] :
	p[1] <  v.p[1] :
	p[0] <  v.p[0];
}

} /* namespace base */
} /* namespace yage */

#endif /* YAGE_POINT3_T_ */
