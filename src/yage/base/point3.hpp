/**
 *  @file        point3.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 14:07:39 2009
 *
 *  Declaración del tipo point3.
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

#ifndef YAGE_POINT3_H
#define YAGE_POINT3_H

#include <iostream>
#include <cmath>

namespace yage
{
namespace base
{

template <class T>
class point3
{
public:
    inline point3 ();
    inline point3 (T x, T y, T z);
    inline point3 (const point3& org);
    inline point3 (const float* org);

    inline void set (T nx, T ny, T nz);
    inline void set_x (T x);
    inline void set_y (T y);
    inline void set_z (T z);

    inline T x () const;
    inline T y () const;
    inline T z () const;

    inline T* ptr ();
    inline const T* ptr () const;

    inline T length () const;
    inline T sq_length () const;
    inline point3 cross (const point3& p) const;
    inline T dot (const point3& p) const;
    inline point3 normalize () const;
    inline point3 normal (const point3& p) const;
    inline T cos (const point3& p) const;

    inline point3& operator+= (const point3& p);
    inline point3 operator+ (const point3& p) const;
    inline point3 operator- (const point3& p) const;
    inline point3 operator* (const T& t) const;
    inline point3 operator* (const point3& p) const;

    inline bool operator< (const point3& p) const;
    inline bool operator==(const point3& p) const;
    inline bool operator!=(const point3& p) const;

    inline point3& operator=(const point3& p);
    inline T& operator[] (int indice);
    inline const T& operator[] (const int indice) const;

    point3 rotate (float angle, const point3& axis);

private:
    T p[3];
};

typedef point3<float> point3f;

} /* namespaec base */
} /* namespace yage */

#include <yage/base/point3.tpp>

#endif /* YAGE_POINT3_H */
