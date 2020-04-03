/**
 *  @file        hemisphere.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 14:18:54 2009
 *
 *  Implementación del tipo hemisphere.
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
#include "hemisphere.hpp"

using namespace yage::base;

namespace yage
{
namespace geo
{

hemisphere::hemisphere (size_t division)
{
    begin (mesh::QUADS);
    for (size_t i = 0; i < division; ++i)
    {
	colour (point3f (1.0, (float) i / division, 0.0));

	for (size_t j = 0; j < division; j++) {
	    point (point3f (sin (M_PI * (float) j / division) *
			    cos (M_PI * (float) i /division),
			    cos (M_PI * (float) j / division),
			    sin (M_PI * (float) j / division) *
			    sin (M_PI * (float) i /division)));
	    point (point3f (sin (M_PI * (float) j / division) *
			    cos (M_PI * (float) (i+1) /division),
			    cos (M_PI * (float) j / division),
			    sin (M_PI * (float) j / division) *
			    sin (M_PI * (float) (i+1) /division)));
	    point (point3f (sin (M_PI * (float) (j+1) / division) *
			    cos (M_PI * (float) (i+1) /division),
			    cos (M_PI * (float) (j+1) / division),
			    sin (M_PI * (float) (j+1) / division) *
			    sin (M_PI * (float) (i+1) / division)));
	    point (point3f (sin (M_PI * (float) (j+1) / division) *
			    cos (M_PI * (float) i / division),
			    cos (M_PI * (float) (j+1) / division),
			    sin (M_PI * (float) (j+1) / division) *
			    sin (M_PI * (float) i / division)));
	}
    }
    end ();
}

} /* namespace geo */
} /* namespace yage */
