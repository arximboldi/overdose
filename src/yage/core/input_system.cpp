/**
 *  @file        input_system.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 14:51:37 2009
 *
 *  Implementación del input_system
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

#include <iostream>
#include "input_system.hpp"

namespace yage
{
namespace core
{

bool input_system::update ()
{
    bool cont = true;
    SDL_Event ev;

    while (SDL_PollEvent (&ev)) {
	switch (ev.type) {
	case SDL_VIDEOEXPOSE:
	    on_video_update (ev);
	    break;

	case SDL_VIDEORESIZE:
	    on_video_resize (ev);
	    break;

	case SDL_KEYDOWN:
	    on_key_press (ev);
	    break;

	case SDL_KEYUP:
	    on_key_release (ev);
	    break;

	case SDL_MOUSEBUTTONDOWN:
	    on_mouse_button_press (ev);
	    break;

	case SDL_MOUSEBUTTONUP:
	    on_mouse_button_release (ev);
	    break;

	case SDL_MOUSEMOTION:
	    on_mouse_move (ev);
	    break;

	case SDL_QUIT:
	    cont = false;
	    break;

	default:
	    break;
	}
    }

    return cont;
}

} /* namespace core */
} /* namespace yage */
