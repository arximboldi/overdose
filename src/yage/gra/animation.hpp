/**
 *  @file        animation.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Wed May 13 13:35:51 2009
 *
 *  Interfaz animation.
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

#ifndef YAGE_ANIMATION_H_
#define YAGE_ANIMATION_H_

#include <boost/shared_ptr.hpp>

namespace yage
{
namespace gra
{

class animation
{
public:
    virtual ~animation () {}

    virtual void animate (float percent) = 0;
    virtual float get_duration () = 0;
    virtual float get_loop_offset () { return 1.0f; }
};

typedef boost::shared_ptr<animation> animation_ptr;

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_ANIMATION_H_ */
