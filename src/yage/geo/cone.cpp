/**
 *  @file        cone.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 11:51:36 2009
 *
 *  Implementación del cono.
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

#include "cone.hpp"

using namespace yage::base;

namespace yage
{
namespace geo
{

cone::cone (size_t division)
{
    /* La base*/
    begin (mesh::TRIANGLES);
    for (size_t i = 0; i <= division; ++i) {
	point (point3f (0, 0, 0));
	point (point3f (cos (2 * M_PI * (float) i / division),
			0.0f,
			sin (2 * M_PI * (float) i / division)));
	point (point3f (cos (2 * M_PI * (float) (i+1) / division),
			0.0f,
			sin (2 * M_PI * (float) (i+1) / division)));
    }
    end ();

    /* Los lados */
    begin (mesh::TRIANGLES);
    for (size_t i = 0; i <= division; ++i) {
     	point (point3f (cos (2 * M_PI * (float) (i+1) / division),
			0.0f,
			sin (2 * M_PI * (float) (i+1) / division)));
	point (point3f (cos (2 * M_PI * (float) i / division),
			0.0f,
			sin (2 * M_PI * (float) i / division)));

	point (point3f (0, 1, 0));
    }
    end ();
}

} /* namespace geo */
} /* namespace yage */
