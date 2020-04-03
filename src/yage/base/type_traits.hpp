/**
 *  @file        type_traits.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Tue Apr  7 14:34:06 2009
 *
 *  Usefull traits to use when programming templates.
 *  Inspired by Loki's type traits but not as complete. Feel free
 *  to extend as needed.
 */

/*
 *  Copyright (C) 2009 Juan Pedro Bolívar Puente
 *
 *  This file is part of Psychosynth.
 *
 *  Psychosynth is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Psychosynth is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef YAGE_TYPE_TRAITS_H_
#define YAGE_TYPE_TRAITS_H_

namespace yage
{
namespace base
{

template<typename T>
struct take_pointer
{
    enum { result = false };
    typedef T type;
};

template<typename T>
struct take_pointer<T*>
{
    enum { result = true };
    typedef T type;
};

template<typename T>
struct type_traits
{
    enum { is_pointer = take_pointer<T>::result };
    typedef typename take_pointer<T>::type pointee_type;
    typedef volatile T volatile_type;
};

} /* namespace base */
} /* namespace yage */

#endif /* YAGE_TYPE_TRAITS_H_ */
