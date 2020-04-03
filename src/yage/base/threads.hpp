/**
 *  @file        threads.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Tue Apr  7 11:29:08 2009
 *
 *  This module provides simplified and abstracted threading models
 *  that can be used for policy-yaged designs. It is inspired
 *  by Andrei Alexandrescu's implementation at his book Modern C++ Design.
 *
 *  To make the code directly compatible with Boost.Threads we use
 *  the Boost mutex interface as threading policy. As such, a MutexPolicy
 *  must have the following two methods:
 *
 *       - Mutex::lock ()    -> Locks the mutex
 *       - Mutex::unlock ()  -> Unlocks the mutex
 *
 *  A mutex must also the find, as boost::mutex does, a exception safe
 *  RAII wrapper to lock the mutex under the name of:
 *
 *       - Mutex::scoped_lock with at least one constructor accepting
 *         a reference to a Mutex instance.
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

#ifndef YAGE_THREADS_H_
#define YAGE_THREADS_H_

#include <yage/base/util.hpp>

#define YAGE_DEFAULT_THREADING         yage::base::no_threading
#define YAGE_DEFAULT_NONOBJ_THREADING  yage::base::no_threading

#ifndef YAGE_DEFAULT_MUTEX
#include <boost/thread/recursive_mutex.hpp>
#define YAGE_DEFAULT_MUTEX             boost::recursive_mutex
#endif

namespace yage
{
namespace base
{

template <class T>
class no_threading
{
public:
    typedef T volatile_type;

    struct lock
    {
	lock () {}
	explicit lock (const no_threading& host) {}
	explicit lock (const no_threading* host) {}
    };

private:
};

template <class T>
class lockable_yage
{
public:
    typedef volatile T volatile_type;
};

template <class T, class Mutex = YAGE_DEFAULT_MUTEX>
class object_lockable : public lockable_yage<T>
{
public:
    class lock : public non_copyable
    {
    public:
	lock (const object_lockable& host)
	    : m_host (host)
	{
	    m_host.m_mutex.lock ();
	}

	lock (const object_lockable* host)
	    : m_host (*host)
	{
	    m_host.m_mutex.lock ();
	}

	~lock ()
	{
	    m_host.m_mutex.unlock ();
	}

    private:
	const object_lockable& m_host;
    };

private:
    mutable Mutex m_mutex;
};

template <class T, class Mutex = YAGE_DEFAULT_MUTEX>
class class_lockable : public lockable_yage<T>
{
public:
    class lock : public non_copyable
    {
    public:
	lock ()
	{
	    s_init.m_mutex.lock ();
	}

	lock (const class_lockable& host)
	{
	    s_init.m_mutex.lock ();
	}

	lock (const class_lockable* host)
	{
	    s_init.m_mutex.lock ();
	}

	~lock ()
	{
	    s_init.m_mutex.unlock ();
	}
    };

private:
    struct initializer
    {
	bool  m_is_init;
	Mutex m_mutex;

	initializer ()
	    : m_is_init (false)
	{
	    m_is_init = true;
	}

	~initializer ()
	{
	    assert (m_is_init);
	}
    };

    static initializer s_init;
};

template<class T, class M>
typename class_lockable<T, M>::initializer class_lockable<T, M>::s_init;

typedef
tpl_bind_snd<object_lockable, YAGE_DEFAULT_MUTEX>
default_object_lockable;

typedef
tpl_bind_snd<class_lockable, YAGE_DEFAULT_MUTEX>
default_class_lockable;

} /* namespace base */
} /* namespace yage */

#endif /* YAGE_THREADS_H_ */
