/**
 *  @file        system.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 15:20:26 2009
 *
 *  Implementación de la clase system
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

#include <SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <SDL_opengl.h>

#include "yage/gra/camera.hpp"
#include "system.hpp"
#include "task_manager.hpp"
#include <iostream>

namespace yage
{
namespace core
{

YAGE_DEFINE_ERROR_WHERE (system_error, "system");

system_impl::system_impl ()
    : m_tasks (new task_manager)
    , m_fps (-1)
    , m_update_fps (false)
    , m_must_quit (false)
{
}

void system_impl::clear_resources ()
{
    m_graphic.fonts ().clear ();
    m_graphic.geometries ().clear ();
    m_graphic.textures ().clear ();
    m_graphic.materials ().clear ();
}

void system_impl::main_loop ()
{
    m_timer = timer ();
    m_input.add_video_listener (m_graphic);

#ifdef __EMSCRIPTEN__
    /* A browser only draws and delivers input once control returns to
       it, so let it call us once per frame instead of looping here.
       simulate_infinite_loop makes this call never return: the stack
       frames of our callers, and the objects living in them, stay
       around while the browser drives the loop. */
    emscripten_set_main_loop_arg (&system_impl::browser_frame, this, 0, true);
#else
    while (iterate ())
	;
    finish_loop ();
#endif
}

bool system_impl::iterate ()
{
    if (m_must_quit || !m_input.update ())
	return false;

    if (m_update_fps) {
	m_timer.force_fps (m_fps);
	m_update_fps = false;
    }

    m_timer.update ();
    m_tasks->update (m_timer.delta_ticks ());
    m_graphic.update ();
    return true;
}

void system_impl::finish_loop ()
{
    m_input.del_video_listener (m_graphic);
    m_must_quit = false;
}

#ifdef __EMSCRIPTEN__
void system_impl::browser_frame (void* self)
{
    system_impl& sys = *static_cast<system_impl*> (self);
    if (!sys.iterate ()) {
	sys.finish_loop ();
	emscripten_cancel_main_loop ();
    }
}
#endif

} /* namespace core */
} /* namespace yage */
