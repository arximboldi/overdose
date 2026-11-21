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

#include <SDL_ttf.h>
#ifdef __EMSCRIPTEN__
#include <cmath>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <gl4esinit.h>
#endif

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
    , m_win_width (DEFAULT_SCREEN_WIDTH)
    , m_win_height (DEFAULT_SCREEN_HEIGHT)
    , m_desktop_width (0)
    , m_desktop_height (0)
    , m_fullsc (DEFAULT_FULLSCREEN)
    , m_grab (false)
    , m_isinit (false)
    , m_scene (new gra::scene)
{
}

void graphic_system::init (int sc_w, int sc_h, bool fs, bool grab)
{
    m_win_width = sc_w;
    m_win_height = sc_h;
    m_fullsc = fs;
    m_grab = grab;
    do_init ();
}

void graphic_system::init (const std::string& title,
			   int sc_w, int sc_h, bool fs, bool grab)
{
    m_title = title;
    m_win_width = sc_w;
    m_win_height = sc_h;
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

    /* Before a mode is set, this is the mode of the desktop. */
    const SDL_VideoInfo* info = SDL_GetVideoInfo ();
    m_desktop_width = info->current_w;
    m_desktop_height = info->current_h;

    set_video_mode ();

    /* TODO: Parametrizar key repeat? */
    SDL_EnableKeyRepeat (300, 50);
    SDL_WM_SetCaption (m_title.c_str (), 0);

    /* Asociamos las extensiones a los tipos */
    m_geometries.get_policy ().attach_default_factory<geo::md2_model_impl> ("md2");
    m_geometries.get_policy ().attach_default_factory<geo::ply_model> ("ply");

    /* Inicializamos algunos parametros de Opengl */
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

void graphic_system::set_video_mode ()
{
    bool fullscreen = m_fullsc;
#ifdef __EMSCRIPTEN__
    /* Browsers only go fullscreen when the user asks for it. */
    fullscreen = false;
#endif
    int width = m_win_width;
    int height = m_win_height;
    if (fullscreen && m_desktop_width > 0 && m_desktop_height > 0) {
	width = m_desktop_width;
	height = m_desktop_height;
    }

    /* TODO: Parametrizar SDL_RESIZABLE? */
    SDL_Surface* screen = SDL_SetVideoMode (
	width, height, 32, SDL_OPENGL | (fullscreen ? SDL_FULLSCREEN : 0));
    if (!screen)
	throw graphic_system_error (
	    std::string ("Could not create window: ") + SDL_GetError ());

#ifdef __EMSCRIPTEN__
    /* gl4es implements the fixed-function OpenGL we use on top of
       WebGL, and needs the context SDL just created. */
    static bool gl4es_ready = false;
    if (!gl4es_ready) {
	initialize_gl4es ();
	gl4es_ready = true;
    }
#endif

    m_sc_width = screen->w;
    m_sc_height = screen->h;
    glViewport (0, 0, m_sc_width, m_sc_height);

    SDL_ShowCursor (m_grab ? SDL_DISABLE : SDL_ENABLE);
    SDL_WM_GrabInput (m_grab ? SDL_GRAB_ON : SDL_GRAB_OFF);
}

void graphic_system::resize_window (int sc_w, int sc_h, bool fs, bool grab)
{
#ifndef WIN32
    m_win_width = sc_w;
    m_win_height = sc_h;
    m_fullsc = fs;
    m_grab = grab;
    set_video_mode ();
#else
    throw graphic_system_error ("Resize not supported on windows platform.");
#endif
}

void graphic_system::toggle_fullscreen ()
{
#ifdef __EMSCRIPTEN__
    EM_ASM ({
	if (Module['toggleFullscreen'])
	    Module['toggleFullscreen'] ();
    });
#else
    resize_window (m_win_width, m_win_height, !m_fullsc, m_grab);
#endif
}

#ifdef __EMSCRIPTEN__
/*
 * The page sizes the canvas with CSS, e.g. to fill the screen when
 * it is fullscreen. Render at the resolution it is displayed at.
 */
void graphic_system::fit_canvas ()
{
    double css_width, css_height;
    if (emscripten_get_element_css_size ("#canvas", &css_width, &css_height)
	!= EMSCRIPTEN_RESULT_SUCCESS)
	return;

    double ratio = emscripten_get_device_pixel_ratio ();
    int width = std::lround (css_width * ratio);
    int height = std::lround (css_height * ratio);
    if (width <= 0 || height <= 0 ||
	(width == m_sc_width && height == m_sc_height))
	return;

    emscripten_set_canvas_element_size ("#canvas", width, height);
    m_sc_width = width;
    m_sc_height = height;
    glViewport (0, 0, m_sc_width, m_sc_height);
}
#endif

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
#ifdef __EMSCRIPTEN__
    fit_canvas ();
#endif
    glEnable (GL_NORMALIZE);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if (m_scene)
	m_scene->render (m_sc_width, m_sc_height, HUD_WIDTH, HUD_HEIGHT);

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
