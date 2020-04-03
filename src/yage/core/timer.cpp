/**
 *  @file        timer.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        2007
 *
 *  A time counter and delay generator.
 */

/*
 *  Copyright (C) 2007 Juan Pedro Bolívar Puente
 *
 *  This file is part of Psychosynth.
 *
 *  Psychosynth is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Psychosynth is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <unistd.h>
#include <iostream>
#include <sys/time.h>

#include "timer.hpp"

using namespace std;

namespace yage
{
namespace core
{

timer::timer ()
{
    rate = -1;
    rateticks = 1;
    reset ();
}

timer::~timer ()
{
}

void timer::force_fps (int fpsrate)
{
    framecount = 0;
    if (fpsrate > 0) {
	rate = fpsrate;
	rateticks = (1000.0 / (float) rate);
    } else {
	rate = -1;
	rateticks = 1;
    }
}

void timer::reset ()
{
    framecount = 0;
    ms = 0;
    totalms = 0;
    mscount = lastticks = SDL_GetTicks ();
}

void timer::update ()
{
    Uint32 current_ticks;
    Uint32 target_ticks;
    Uint32 the_delay;
    Uint32 currms;

    if (rate > 0) {
        framecount++;

        currms = current_ticks = SDL_GetTicks ();
        ms = currms - mscount;
        mscount = currms;

        target_ticks = lastticks + Uint32 (framecount * rateticks);

        if (current_ticks <= target_ticks) {
            the_delay = target_ticks - current_ticks;
            SDL_Delay (the_delay);
        } else {
            framecount = 0;
            lastticks = SDL_GetTicks ();
        }
    } else {
        currms = SDL_GetTicks();
        ms = currms - mscount;
        mscount = currms;
    }
}

} /* namespace core */
} /* namespace yage */
