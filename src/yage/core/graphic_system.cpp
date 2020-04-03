/**
 *  @file        graphic_system.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 15 13:23:41 2009
 *
 *  Implementación de graphic_system.
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

#include <SDL/SDL_ttf.h>

#include "yage/geo/md2_model_impl.hpp"
#include "yage/geo/ply_model.hpp"

#include "yage/gra/scene.hpp"
#include "graphic_system.hpp"

namespace yage
{
namespace core
{

YAGE_DEFINE_ERROR_WHERE (graphic_system_error, "graphic_system");

graphic_system::graphic_system ()
    : m_sc_width (DEFAULT_SCREEN_WIDTH)
    , m_sc_height (DEFAULT_SCREEN_HEIGHT)
    , m_fullsc (DEFAULT_FULLSCREEN)
    , m_grab (false)
    , m_isinit (false)
    , m_scene (new gra::scene)
{
}

void graphic_system::init (int sc_w, int sc_h, bool fs, bool grab)
{
    m_sc_width = sc_w;
    m_sc_height = sc_h;
    m_fullsc = fs;
    m_grab = grab;
    do_init ();
}

void graphic_system::init (const std::string& title,
			   int sc_w, int sc_h, bool fs, bool grab)
{
    m_title = title;
    m_sc_width = sc_w;
    m_sc_height = sc_h;
    m_fullsc = fs;
    m_grab = grab;
    do_init ();
}

void graphic_system::do_init ()
{
    /* Inicializar sdl */
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	throw graphic_system_error (
	    std::string ("Could not init SDL: ") +
	    SDL_GetError ());
    std::atexit (SDL_Quit);

    /* Inicializar ttf */
    if (TTF_Init () < 0)
	throw graphic_system_error (
	    std::string ("Could not init SDL_ttf: ") + TTF_GetError ());
    std::atexit (TTF_Quit);

    /* Parametros del contexto de Opengl */
    SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

    /* TODO: Parametrizar SDL_RESIZABLE? */
    if (SDL_SetVideoMode (m_sc_width, m_sc_height, 32,
			  SDL_OPENGL |
			  (m_fullsc ? SDL_FULLSCREEN : 0)) == 0)
	throw graphic_system_error (
	    std::string ("Could not create window: ") + SDL_GetError ());

    /* TODO: Parametrizar key repeat? */
    SDL_EnableKeyRepeat (300, 50);
    SDL_WM_SetCaption (m_title.c_str (), 0);

    if (m_grab) {
	SDL_ShowCursor (0);
	SDL_WM_GrabInput (SDL_GRAB_ON);
    }

    /* Asociamos las extensiones a los tipos */
    m_geometries.get_policy ().attach_default_factory<geo::md2_model_impl> ("md2");
    m_geometries.get_policy ().attach_default_factory<geo::ply_model> ("ply");

    /* Inicializamos algunos parametros de Opengl */
    glViewport (0, 0, m_sc_width, m_sc_height);
    glClearColor (0, 0, 0, 1);
    glEnable (GL_NORMALIZE);
    glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, 1);

    set_polygon_mode ();
    set_shading_mode ();

    m_isinit = true;
}

void graphic_system::close ()
{
    if (m_isinit) {
	TTF_Quit ();
	SDL_Quit ();
    }
    m_isinit = false;
}

graphic_system::~graphic_system ()
{
}

void graphic_system::resize_window (int sc_w, int sc_h, bool fs, bool grab)
{
#ifndef WIN32
    m_sc_width = sc_w;
    m_sc_height = sc_h;
    m_fullsc = fs;
    m_grab = grab;

    SDL_SetVideoMode (m_sc_width, m_sc_height, 32,
		      SDL_OPENGL |
		      (m_fullsc ? SDL_FULLSCREEN : 0));

    if (m_grab) {
	SDL_ShowCursor (false);
	SDL_WM_GrabInput (SDL_GRAB_OFF);
    } else {
	SDL_ShowCursor (true);
	SDL_WM_GrabInput (SDL_GRAB_ON);
    }

#else
    throw graphic_system_error ("Resize not supported on windows platform.");
#endif
}

bool graphic_system::handle_video_resize (SDL_Event& ev)
{
    m_sc_width = ev.resize.w;
    m_sc_height = ev.resize.h;

    glViewport (0, 0, m_sc_width, m_sc_height);
    return false;
}

bool graphic_system::handle_video_update (SDL_Event& ev)
{
    update ();
    return false;
}

void graphic_system::update ()
{
    glEnable (GL_NORMALIZE);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if (m_scene)
	m_scene->render (m_sc_width, m_sc_height);

    SDL_GL_SwapBuffers ();
}

void graphic_system::set_polygon_mode (polygon_mode mode)
{
    glPolygonMode (GL_BACK, mode);
    glPolygonMode (GL_FRONT, mode);
}

void graphic_system::set_shading_mode (shading_mode mode)
{
    glShadeModel (mode);
}

void graphic_system::set_clear_color (const base::point4f& col)
{
    glClearColor (col[0], col[1], col[2], col[3]);
}

} /* namespace core */
} /* namespace yage */
