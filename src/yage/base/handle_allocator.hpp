/**
 *  Time-stamp:  <2009-06-15 11:31:41 raskolnikov>
 *
 *  @file        handle_allocator.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Mon May 11 15:47:40 2009
 *
 *  Interfaz e implementación de la plantilla handle_allocator.
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

#ifndef YAGE_HANDLE_ALLOCATOR_H_
#define YAGE_HANDLE_ALLOCATOR_H_

#include <deque>
#include <list>

#include <yage/base/exception.hpp>

namespace yage
{
namespace base
{

YAGE_DECLARE_ERROR (yage_error, handle_allocator_error);

template <typename T>
class throw_creator_policy
{
public:
    T create ()
    {
	throw handle_allocator_error ();
    }
};

template <typename T>
class count_creator_policy
{
public:
    count_creator_policy ()
	: m_count (0)
    {}
    
    T create ()
    {
	return ++ m_count;
    }

private:
    T m_count;
};

template <typename T, template<typename> class CreatorPolicy = count_creator_policy>
class handle_allocator
{
public:
    handle_allocator ()
    {}
    
    T allocate ();
    void release (T id);
    
private:
    CreatorPolicy<T> m_creator;
    std::list<T> m_free;
};

/**
 * @todo Reimplementar como una poliza del anterior.
 */
template <typename T, T Min, T Max>
class fixed_handle_allocator
{
public:
    fixed_handle_allocator ();
    T allocate ();
    void release (T id);
    
private:
    std::deque<T> m_free;
};


template <typename T, template<typename> class C>
T handle_allocator<T, C>::allocate ()
{
    T ret;
	
    if (m_free.empty ())
	ret = m_creator.create ();
    else {
	ret = m_free.front ();
	m_free.pop_front ();
    }

    return ret;
}

template <typename T, template<typename> class C>
void handle_allocator<T, C>::release (T id)
{
    m_free.push_back (id);
}

template <typename T, T Min, T Max>
fixed_handle_allocator<T, Min, Max>::fixed_handle_allocator ()
{
    for (T curr = Min; curr <= Max; ++curr)
	m_free.push_back (curr);
}

template <typename T, T Min, T Max>
T fixed_handle_allocator<T, Min, Max>::allocate ()
{
    if (m_free.empty ())
	throw handle_allocator_error ();

    T ret = m_free.front ();
    m_free.pop_front ();
    return ret;
}

template <typename T, T Min, T Max>
void fixed_handle_allocator<T, Min, Max>::release (T id)
{
    m_free.push_back (id);
}

} /* namespace base */
} /* namespace yage */

#endif /* YAGE_HANDLE_ALLOCATOR_H_ */
