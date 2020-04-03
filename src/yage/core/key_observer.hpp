/**
 *  @file        key_listener.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 14:54:35 2009
 *
 *  Interfaces de clases del patrón observer para el teclado.
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

#ifndef YAGE_KEY_LISTENER_H
#define YAGE_KEY_LISTENER_H

#include <yage/base/observer.hpp>
#include <yage/core/sdl_wrapper.hpp>

namespace yage
{
namespace core
{

class key_listener : public base::listener_base
{
public:
    virtual bool handle_key_press (SDL_Event& event) = 0;
    virtual bool handle_key_release (SDL_Event& event) = 0;
};

class key_subject : public base::subject_base <key_listener>
{
public:
    sdl_signal_type on_key_press;
    sdl_signal_type on_key_release;

    void add_listener (key_listener& l);
    void del_listener (key_listener& l);
};

class key_forwarder : public key_listener
		    , public key_subject
{
public:
    bool handle_key_press (SDL_Event& event)
    {
	return on_key_press (event);
    }

    bool handle_key_release (SDL_Event& event)
    {
	return on_key_release (event);
    }
};

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_KEYLISTENER_H */
