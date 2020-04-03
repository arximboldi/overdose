/**
 *  @file        point2.tpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 13:52:03 2009
 *
 *  Implementacion de la clase point2<>
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

#ifndef YAGE_POINT2_T_
#define YAGE_POINT2_T_

#include <iostream>
#include <cmath>

namespace yage
{
namespace base
{

template <class T>
inline std::ostream& operator<< (std::ostream& os, const point2<T>& p)
{
    return os << '(' << p.x() << ',' << p.y() <<  ')';
}

template <class T>
inline std::istream& operator>> (std::istream& is, point2<T>& p)
{
    char caracter;
    T x,y,z;
    is >> caracter >> x >> caracter >> y >> caracter;
    p = point2<T> (x,y);
    return is;
}

template <class T>
point2<T>::point2 ()
{
    p[0] = 0;
    p[1] = 0;
}

template <class T>
point2<T>::point2 (T x, T y )
{
    p[0] = x;
    p[1] = y;
}

template <class T>
point2<T>::point2 (const point2<T> &orig)
{
    p[0] = orig.x ();
    p[1] = orig.y ();
}

template <class T>
void point2<T>::set (T x, T y)
{
    p[0] = x;
    p[1] = y;

}

template <class T>
void point2<T>::set_x (T x)
{
    p[0] = x;
}

template <class T>
void point2<T>::set_y (T y)
{
    p[1] = y;
}

template <class T>
T point2<T>::x () const
{
    return p[0];
}

template <class T>
T point2<T>::y () const
{
    return p[1];
}

template <class T>
T* point2<T>::ptr ()
{
    return p;
}

template <class T>
const T* point2<T>::ptr () const
{
    return p;
}

template <class T>
point2<T> & point2<T>::operator= (const point2<T> &po)
{
    p[0] = po.x();
    p[1] = po.y();
    return *this;
}

template <class T>
bool point2<T>::operator== (const point2<T> &po)
{
    return
	p[0] == po.x () &&
	p[1] == po.y ();
}

template <class T>
bool point2<T>::operator!= (const point2<T> &po)
{
    return
	p[0] != po.x () ||
	p[1] != po.y ();
}

template <class T>
T &point2<T>::operator[] (const int indice)
{
    return p[indice];
}

template<class T>
point2<T>& point2<T>::operator+= (const point2<T> &v)
{
    p[0] += v.p[0];
    p[1] += v.p[1];
    return *this;
}

template<class T>
point2<T> point2<T>::operator +(const point2<T> &v) const
{
    return point2<T>(v.p[0] + p[0], v.p[1] + p[1]);
}

template<class T>
point2<T> point2<T>::operator -(const point2 &v) const
{
    return point2<T>(p[0] - v. p[0], p[1] - v.p[1]);
}

template<class T>
T point2<T>::length() const
{
    return std::sqrt (p[0]*p[0] + p[1]*p[1]);
}

template<class T>
T point2<T>::sq_length () const
{
    return p[0]*p[0] + p[1]*p[1];
}

template<class T>
point2<T> point2<T>::operator* (const T & t) const
{
    return point2<T> (t * p[0], t * p[1]);
}

template<class T>
point2<T> point2<T>::operator* (const point2 & v) const
{
    return point2<T> (v.p[0] * p[0], v.p[1] * p[1]);
}

template<class T>
point2<T> point2<T>::dot (const point2 & v) const
{
    return point2<T> (v.p[0] * p[0], v.p[1] * p[1]);
}

template<class T>
bool point2<T>::operator< (const point2<T>& v) const
{
    return
	p[0] == v.p[0] ?
	p[1] <  v.p[1] :
	p[0] <  v.p[0] ;
}

} /* namespace base */
} /* namespace yage */

#endif /* YAGE_POINT2_T_ */
