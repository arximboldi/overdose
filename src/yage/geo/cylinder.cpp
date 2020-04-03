/**
 *  @file        cylinder.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 12:10:55 2009
 *
 *  Implementación de los cilindros.
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
#include <cassert>
#include <SDL/SDL_opengl.h>

#include "cylinder.hpp"

using namespace yage::base;

namespace yage
{
namespace geo
{

cylinder::cylinder (size_t division)
{
    /* Tapa inferior */
    begin (mesh::TRIANGLES);
    for (size_t i = 0; i <=  division; ++i) {
	point (point3f (0, 0, 0));
	point (point3f (cos (2 * M_PI * (float)i / division),
			0.0f,
			sin (2 * M_PI * (float)i / division)));
	point (point3f (cos (2 * M_PI * (float)(i+1) / division),
			0.0f,
			sin (2 * M_PI * (float)(i+1) / division)));
    }
    end ();

    /* Ladas */
    begin (mesh::QUADS);
    for (size_t i = 0; i <= division; ++i) {
	point (point3f (cos(2 * M_PI * (float)i / division),
			0,
			sin (2 * M_PI * (float)i / division)));
	point (point3f (cos (2 * M_PI * (float)i / division),
			2,
			sin (2 * M_PI * (float)i / division)));
	point (point3f (cos (2 * M_PI * (float)(i+1) / division),
			2,
			sin (2 * M_PI * (float)(i+1) / division)));
	point (point3f (cos (2 * M_PI * (float)(i+1) / division),
			0,
			sin (2 * M_PI * (float)(i+1) / division)));
    }
    end ();

    /* Tapa superior */
    begin(mesh::TRIANGLES);
    for (size_t i = 0; i <=  division; ++i) {
	point (point3f (cos (2 * M_PI * (float)(i+1) / division),
			2,
			sin (2 * M_PI * (float)(i+1) / division)));
	point (point3f (cos (2 * M_PI * (float)i / division),
			2,
			sin (2 * M_PI * (float)i / division)));
	point (point3f (0, 2, 0));
    }
    end ();
}

} /* namespace geo */
} /* namespace yage */
