/**
 *  @file        sdl_wrapper.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Mon May 18 11:25:40 2009
 *
 *  Utilidades varias para facilitar trabajar con la SDL desde C++.
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

#ifndef YAGE_SDL_WRAPPER_H_
#define YAGE_SDL_WRAPPER_H_

#include <SDL/SDL.h>
#include <yage/base/observer.hpp>
#include <yage/base/pointer.hpp>

namespace yage
{
namespace core
{

typedef
sigc::signal1<bool, SDL_Event&, base::short_circuit_accum>
sdl_signal_type;

typedef
base::scoped_ptr<SDL_Surface, void (*) (SDL_Surface*), &SDL_FreeSurface>
sdl_surface_ptr;

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_SDL_WRAPPER_H_ */
