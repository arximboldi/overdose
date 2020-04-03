/**
 *  @file        point4.tpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 14:11:52 2009
 *
 *  Implementación del tipo point4<>
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

#ifndef YAGE_POINT4_T_
#define YAGE_POINT4_T_

namespace yage
{
namespace base
{

template <class T>
inline std::ostream& operator<< (std::ostream& os, const point4<T>& p)
{
    return os << '(' << p.x() << ',' << p.y() << ',' << p.z() <<',' << p.t() <<  ')';
}

template <class T>
inline std::istream& operator>> (std::istream& is, point4<T>& p)
{
    char caracter;
    T x, y, z, t;
    is >> caracter >> x >> caracter >> y >> caracter >> z >> caracter >> t >> caracter;
    p = point4<T> (x, y, z, t);
    return is;
}

template <class T>
point4<T>::point4()
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
}

template <class T>
point4<T>::point4 (T x, T y, T z, T t)
{
    p[0] = x;
    p[1] = y;
    p[2] = z;
    p[3] = t;

}

template <class T>
point4<T>::point4 (const point4<T>& orig)
{
    p[0] = orig.x ();
    p[1] = orig.y ();
    p[2] = orig.z ();
    p[3] = orig.t ();
}

template <class T>
void point4<T>::set (T x, T y, T z, T t)
{
    p[0] = x;
    p[1] = y;
    p[2] = z;
    p[3] = t;
}

template <class T>
void point4<T>::set_x (T x)
{
    p[0] = x;
}

template <class T>
void point4<T>::set_y (T y)
{
    p[1] = y;
}

template <class T>
void point4<T>::set_z (T z)
{
    p[2] = z;
}

template <class T>
void point4<T>::set_t (T t)
{
    p[3] = t;
}

template <class T>
T point4<T>::x() const
{
    return p[0];
}

template <class T>
T point4<T>::y () const
{
    return p[1];
}

template <class T>
T point4<T>::z () const
{
    return p[2];
}

template <class T>
T point4<T>::t () const
{
    return p[3];
}

template <class T>
T* point4<T>::ptr ()
{
    return p;
}

template <class T>
const T* point4<T>::ptr () const
{
    return p;
}

template <class T>
point4<T>& point4<T>::operator=(const point4<T>& po)
{
    p[0] = po.x();
    p[1] = po.y();
    p[2] = po.z();
    p[3] = po.t();

    return *this;
}

template <class T>
bool point4<T>::operator==(const point4<T>& po)
{
    return
	p[0] == po.x() &&
	p[1] == po.y() &&
	p[2] == po.z() &&
	p[3] == po.t();
}


template <class T>
bool point4<T>::operator!=(const point4<T>& po)
{
    return
	p[0] != po.x() ||
	p[1] != po.y() ||
	p[2] != po.z() ||
	p[3] != po.t();
}

template <class T>
T &point4<T>::operator[] (const int indice)
{
    return p[indice];
}

template <class T>
const T &point4<T>::operator[] (const int indice) const
{
    return p[indice];
}

template <class T>
point4<T> point4<T>::operator+ (const point4& rhs) const
{
    return point4 (p[0] + rhs[0], p[1] + rhs[1], p[2] + rhs[2], p[3] + rhs[3]);
}

template <class T>
point4<T> point4<T>::operator* (T rhs) const
{
    return point4 (p[0] * rhs, p[1] * rhs, p[2] * rhs, p[3] * rhs);
}

template <class T>
point4<T> point4<T>::operator- (const point4& rhs) const
{
    return point4 (p[0] - rhs[0], p[1] - rhs[1], p[2] - rhs[2], p[3] - rhs[3]);
}

} /* namespace base */
} /* namespace yage */

#endif /* YAGE_POINT4_T_ */
