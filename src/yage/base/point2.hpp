/**
 *  Time-stamp:  <2009-05-21 12:33:41 raskolnikov>
 *
 *  @file        point2.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 13:52:20 2009
 *
 *  Declaración de la clase point2<>
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

#ifndef YAGE_POINT2_H
#define YAGE_POINT2_H

namespace yage
{
namespace base
{

template <class T>
class point2
{
public:
    inline point2 ();
    inline point2 (T x, T y);
    inline point2 (const point2& org);

    inline void set (T nx, T ny);
    inline void set_x (T x);
    inline void set_y (T y);
    inline T x () const;
    inline T y () const;

    inline T length () const;
    inline T sq_length () const;
    inline point2 dot (const point2 & p) const;

    inline point2 & operator= (const point2 &p);
    inline T& operator[] (const int indice);
    inline T* ptr ();
    inline const T* ptr () const;
    
    inline point2& operator+= (const point2 &p);
    inline point2 operator+ (const point2 &p) const;
    inline point2 operator- (const point2 &p) const;
    inline point2 operator* (const T & t) const;
    inline point2 operator* (const point2 & p) const;
    
    inline bool operator< (const point2& p) const;
    inline bool operator== (const point2<T> &p);
    inline bool operator!= (const point2<T> &p);
    
private:
    T p[2];
};

typedef point2<float> point2f;

} /* namespace base */
} /* namespace yage */

#include <yage/base/point2.tpp>

#endif /* YAGE_POINT2_H */
