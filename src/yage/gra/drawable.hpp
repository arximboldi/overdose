/**
 *  Time-stamp:  <2009-06-10 21:10:30 raskolnikov>
 *
 *  @file        drawable.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 15:12:23 2009
 *
 *  Interfaz drawable
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

#ifndef YAGE_DRAWABLE_H
#define YAGE_DRAWABLE_H

#include <boost/shared_ptr.hpp>

namespace yage
{
namespace gra
{

class drawable
{
    
public:
    virtual ~drawable () {}
    virtual void draw () = 0;
};

typedef boost::shared_ptr<drawable> drawable_ptr;

} /* namespace gra */
} /* namespace yage */

#endif /* MGE_DRAWABLE_H */
