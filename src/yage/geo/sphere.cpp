/**
 *  Time-stamp:  <2009-05-22 22:30:51 raskolnikov>
 *
 *  @file        sphere.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 15:14:34 2009
 *
 *  Implementación del tipo sphere.
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

#include "sphere.hpp"

using namespace yage::base;

namespace yage
{
namespace geo
{

sphere::sphere (size_t division)
{
    size_t i, j;
    
    begin (mesh::QUADS);
    for (i = 0; i < division; ++i) {
	for (j = 0; j < division/2; j++) {
	    point (point3f (sin (2 * M_PI * (float) j / division) *
			    cos (2 * M_PI * (float) i / division),
			    cos (2 * M_PI * (float) j / division),
			    sin (2 * M_PI * (float) j / division) *
			    sin (2 * M_PI * (float) i / division)));
	    point (point3f (sin (2 * M_PI * (float) j / division) *
			    cos (2 * M_PI * (float) (i+1) / division),
			    cos (2 * M_PI * (float) j / division),
			    sin (2 * M_PI * (float) j / division) *
			    sin (2 * M_PI * (float) (i+1) / division)));
	    point (point3f (sin (2 * M_PI * (float) (j+1) / division) *
			    cos (2 * M_PI * (float) (i+1) / division),
			    cos (2 * M_PI * (float) (j+1) / division),
			    sin (2 * M_PI * (float) (j+1) / division) *
			    sin (2 * M_PI * (float) (i+1) / division)));
	    point (point3f (sin (2 * M_PI * (float) (j+1) / division) *
			    cos (2 * M_PI * (float) i / division),
			    cos (2 * M_PI * (float) (j+1) / division),
			    sin (2 * M_PI * (float) (j+1) / division) *
			    sin (2 * M_PI * (float) i / division)));
	}
    }
    end ();
}

} /* namespace geo */
} /* namespace yage */
