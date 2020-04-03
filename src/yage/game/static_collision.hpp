/**
 *  Time-stamp:  <2009-05-21 19:25:52 raskolnikov>
 *
 *  @file        static_collision.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 21 10:38:16 2009
 *
 *  Interfaz de la clase collision.
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

#ifndef YAGE_STATIC_COLLISION_H_
#define YAGE_STATIC_COLLISION_H_

#include <yage/game/collidable.hpp>

namespace yage
{
namespace game
{

class static_collision : public boost::static_visitor<bool>
{
public:
    bool test (const collidable& a, const collidable& b);

    bool operator () (const sphere& a, const sphere& b);
    bool operator () (const capsule& a, const capsule& b);
    bool operator () (const aabb& a, const aabb& b);
    bool operator () (const sphere& a, const capsule& b);
    bool operator () (const sphere& a, const aabb& b);
    bool operator () (const capsule& a, const aabb& b);

    bool operator () (const capsule& a, const sphere& b) { return (*this) (b, a); }
    bool operator () (const aabb& a, const sphere& b) { return (*this) (b, a); }
    bool operator () (const aabb& a, const capsule& b) { return (*this) (b, a); }
};

} /* namespace game */
} /* namespace yage */

#endif /* YAGE_STATIC_COLLISION_H_ */
