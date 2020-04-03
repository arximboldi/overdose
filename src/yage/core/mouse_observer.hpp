/**
 *  Time-stamp:  <2009-05-22 15:31:45 raskolnikov>
 *
 *  @file        mouse_listener.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 14:55:27 2009
 *
 *  Interfaz mouse_listener.
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

#ifndef YAGE_MOUSE_LISTENER_H_
#define YAGE_MOUSE_LISTENER_H_

#include <yage/base/observer.hpp>
#include <yage/core/sdl_wrapper.hpp>

namespace yage
{
namespace core
{

class mouse_listener : public base::listener_base
{
public:
    virtual bool handle_mouse_button_press (SDL_Event& event) = 0;
    virtual bool handle_mouse_button_release (SDL_Event& event) = 0;
    virtual bool handle_mouse_move (SDL_Event& event) = 0;
};

class mouse_subject : public base::subject_base <mouse_listener>
{
public:
    sdl_signal_type on_mouse_move;
    sdl_signal_type on_mouse_button_press;
    sdl_signal_type on_mouse_button_release;
    
    void add_listener (mouse_listener& l);
    void del_listener (mouse_listener& l);
};

class mouse_forwarder : public mouse_listener
		      , public mouse_subject
{
public:
    bool handle_mouse_button_press (SDL_Event& event)
    {
	return on_mouse_button_press (event);
    }
    
    bool handle_mouse_button_release (SDL_Event& event)
    {
	return on_mouse_button_release (event);
    }
    
    bool handle_mouse_move (SDL_Event& event)
    {
	return on_mouse_move (event);
    }
};

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_MOUSE_LISTENER_H_ */
