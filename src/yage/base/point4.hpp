/**
 *  @file        point4.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 14:08:06 2009
 *
 *  Declaración del tipo point4<>
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

#ifndef YAGE_POINT4_H
#define YAGE_POINT4_H

#include <iostream>

namespace yage
{
namespace base
{

template <class T>
class point4
{
public:
    inline point4 ();
    inline point4 (T x, T y, T z, T t);
    inline point4 (const point4& org);

    inline void set (T nx, T ny, T nz, T nt);
    inline void set_x (T x);
    inline void set_y (T y);
    inline void set_z (T z);
    inline void set_t (T t);


    inline T x () const;
    inline T y () const;
    inline T z () const;
    inline T t () const;

    inline T* ptr ();
    inline const T* ptr () const;

    inline T& operator[] (const int indice);
    inline const T& operator[] (const int indice) const;
    inline point4& operator= (const point4 &p);

    inline bool operator== (const point4<T> &p);
    inline bool operator!= (const point4<T> &p);

    inline point4 operator- (const point4& p) const;
    inline point4 operator+ (const point4& p) const;
    inline point4 operator* (T p) const;

private:
    T p[4];
};

typedef point4<float> point4f;

} /* namespace base */
} /* namespace yage */

#include <yage/base/point4.tpp>

#endif /* YAGE_POINT4_H */
