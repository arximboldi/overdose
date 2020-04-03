/**
 *  Time-stamp:  <2009-05-22 12:29:48 raskolnikov>
 *
 *  @file        video_observer.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 12:24:51 2009
 *
 *  Implementación de las clases del patrón observer para el video.
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

#include "video_observer.hpp"

namespace yage
{
namespace core
{

void video_subject::add_listener (video_listener& l)
{
    on_video_update.connect (sigc::mem_fun (l, &video_listener::handle_video_update));
    on_video_resize.connect (sigc::mem_fun (l, &video_listener::handle_video_resize));
}

void video_subject::del_listener (video_listener& l)
{
    remove_slot (on_video_resize, sigc::mem_fun (l, &video_listener::handle_video_resize));
    remove_slot (on_video_update, sigc::mem_fun (l, &video_listener::handle_video_update));
}

} /* namespace core */
} /* namespace yage */
