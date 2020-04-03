/**
 *  @file        video_listener.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 14:56:31 2009
 *
 *  Interfaz de las clases de implementación del observer para el video.
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

#ifndef YAGE_VIDEOLISTENER_H
#define YAGE_VIDEOLISTENER_H

#include <yage/base/observer.hpp>
#include <yage/core/sdl_wrapper.hpp>

namespace yage
{
namespace core
{

class video_listener : public base::listener_base
{
public:
    virtual bool handle_video_update (SDL_Event& ev) = 0;
    virtual bool handle_video_resize (SDL_Event& ev) = 0;
};

class video_subject : public base::subject_base <video_listener>
{
public:
    sdl_signal_type on_video_update;
    sdl_signal_type on_video_resize;

    void add_listener (video_listener& l);
    void del_listener (video_listener& l);
};

class video_forwarder : public video_listener
		      , public video_subject
{
public:
    bool handle_video_update (SDL_Event& ev)
    {
	return on_video_update (ev);
    }

    bool handle_video_resize (SDL_Event& ev)
    {
	return on_video_resize (ev);
    }
};

} /* namespace core */
} /* namespace yage */

#endif /* VIDEOLISTENER_H */
