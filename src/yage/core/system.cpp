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

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

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
    timer timer;
    bool val;

    m_input.add_video_listener (m_graphic);
    while (!m_must_quit && (val = m_input.update ()))
    {
	if (m_update_fps) {
	    timer.force_fps (m_fps);
	    m_update_fps = false;
	}

	timer.update ();
	m_tasks->update (timer.delta_ticks ());
	m_graphic.update ();
    }

    m_input.del_video_listener (m_graphic);
    m_must_quit = false;
}

} /* namespace core */
} /* namespace yage */
