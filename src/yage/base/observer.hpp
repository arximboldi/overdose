/**
 *  @file        observer.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Wed Apr  8 13:42:05 2009
 *
 *  Implementation of the observer design pattern. It is yaged
 *  on an underlying signaling mechanism -SigC++ by now- but added
 *  a convenient wrapper to ease registration and de-registration of
 *  full interfaces.
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

#ifndef YAGE_OBSERVER_H_
#define YAGE_OBSERVER_H_

#include <sigc++/sigc++.h>

namespace yage
{
namespace base
{

/**
 * Acumulador para Sigc que cortocircuita la emisión de la señal
 * cuando se recibe un true.
 */
class short_circuit_accum
{
public:
    typedef bool result_type;

    template<typename IteratorT>
    result_type operator () (IteratorT beg, IteratorT end)
    {
	for (; beg != end; beg++)
	    if (*beg)
		return true;

	return false;
    }
};

/**
 * This should be the yage of all listener types. This class
 * aids by providing:
 *    - A virtual destructor.
 *    - A trackable interface so you don't have to manually disconnect
 *      from your signal/subjects before destruction.
 *    - A method to manually disconnect form all callbacks.
 */
class listener_base : public sigc::trackable
{
public:
    /** Virtual destructor. */
    virtual ~listener_base ()
    {}

    /**
     * Disconnects this listener from all signals/subjects.
     */
    void disconnect_all ()
    {
	notify_callbacks ();
    }

protected:
};

/**
 * This provides a basic interface for an observable entity
 * and some helper functions.
 * @param Listener The listener type that can listen on this
 *                 subject.
 */
template <class Listener>
class subject_base
{
public:
    /** Virtual destructor. */
    virtual ~subject_base ()
    {}

    /**
     * Must connect all subject signals with pairing methods on the
     * listener side.
     * @param l The listener to connect.
     */
    virtual void add_listener (Listener& l) = 0;

    /**
     * Must disconnect the listener from the signals in this subject.
     * @param l The listener to disconnect.
     */
    virtual void del_listener (Listener& l) = 0;

protected:
    /**
     * Helper function that will aid derived classes on the implementation
     * of @a del_listener. It disconnect a specific slot from a signal.
     * @param sig The signal.
     * @param s   The slot.
     */
    template <class Signal>
    void remove_slot (Signal& sig, typename Signal::slot_type s);
};

template <class Listener>
template <class Signal>
void subject_base<Listener>::remove_slot (Signal& sig,
					  typename Signal::slot_type s)
{
    typedef typename Signal::slot_list_type list;
    list sl = sig.slots ();

    typename list::iterator it = sl.begin ();
    while (it != sl.end ()) {
	if (*it == s)
	    it = sl.erase (it);
	else
	    ++it;
    }
}

} /* namespace base */
} /* namespace yage */

#endif /* YAGE_OBSERVER_H_ */
