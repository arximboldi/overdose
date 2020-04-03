/**
 *  Time-stamp:  <2009-05-22 12:28:19 raskolnikov>
 *
 *  @file        event_manager.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 14:48:49 2009
 *
 *  Declaracion de la clase input_system
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

#ifndef _YAGE_INPUT_SYSTEM_H
#define _YAGE_INPUT_SYSTEM_H

#include <list>

#include <yage/core/key_observer.hpp>
#include <yage/core/mouse_observer.hpp>
#include <yage/core/video_observer.hpp>

namespace yage
{
namespace core
{

class input_system : public key_subject,
		     public mouse_subject,
		     public video_subject
{  
public:
    bool update ();

    void add_video_listener (video_listener& l)
    {
	video_subject::add_listener (l);
    }

    void del_video_listener (video_listener& l)
    {
	video_subject::del_listener (l);
    }

    void add_mouse_listener (mouse_listener& l)
    {
	mouse_subject::add_listener (l);
    }

    void del_mouse_listener (mouse_listener& l)
    {
	mouse_subject::del_listener (l);
    }

    void add_key_listener (key_listener& l)
    {
	key_subject::add_listener (l);
    }

    void del_key_listener (key_listener& l)
    {
	key_subject::del_listener (l);
    }
};

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_EVENTMANAGER_H */
