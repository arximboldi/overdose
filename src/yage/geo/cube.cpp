/**
 *  Time-stamp:  <2009-05-24 19:19:02 raskolnikov>
 *
 *  @file        cube.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 11:57:50 2009
 *
 *  Implementación de la clase cube
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

#include "cube.hpp"

using namespace yage::base;

namespace yage
{
namespace geo
{

cube::cube ()
{
    float l = 1.0f;
     
    begin (mesh::TRIANGLES);

    point (point3f (l/2,l/2,l/2)); 
    point (point3f (-l/2,l/2,l/2)); 
    point (point3f (-l/2,-l/2,l/2));

    point (point3f (l/2,l/2,l/2)); 
    point (point3f (-l/2,-l/2,l/2));
    point (point3f (l/2,-l/2,l/2));

    point (point3f (l/2,l/2,l/2)); 
    point (point3f (l/2,-l/2,l/2)); 
    point (point3f (l/2,l/2,-l/2)); 

    point (point3f (l/2,-l/2,-l/2));
    point (point3f (l/2,l/2,-l/2)); 
    point (point3f (l/2,-l/2,l/2)); 

    point (point3f (-l/2,l/2,-l/2)); 
    point (point3f (l/2,l/2,-l/2)); 
    point (point3f (l/2,-l/2,-l/2)); 

    point (point3f (-l/2,l/2,-l/2)); 
    point (point3f (l/2,-l/2,-l/2)); 
    point (point3f (-l/2,-l/2,-l/2));

    point (point3f (-l/2,l/2,l/2)); 
    point (point3f (-l/2,l/2,-l/2)); 
    point (point3f (-l/2,-l/2,l/2)); 

    point (point3f (-l/2,l/2,-l/2)); 
    point (point3f (-l/2,-l/2,-l/2));
    point (point3f (-l/2,-l/2,l/2));

    point (point3f (l/2,l/2,l/2)); 
    point (point3f (l/2,l/2,-l/2)); 
    point (point3f (-l/2,l/2,-l/2));

    point (point3f (l/2,l/2,l/2)); 
    point (point3f (-l/2,l/2,-l/2));
    point (point3f (-l/2,l/2,l/2)); 

    point (point3f (l/2,-l/2,-l/2));
    point (point3f (l/2,-l/2,l/2));
    point (point3f (-l/2,-l/2,-l/2));
    
    point (point3f (l/2,-l/2,l/2)); 
    point (point3f (-l/2,-l/2,l/2)); 
    point (point3f (-l/2,-l/2,-l/2)); 
    end ();
}

} /* namespace geo */
} /* namespace yage */
