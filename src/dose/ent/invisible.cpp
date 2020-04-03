/**
 *  @file        invisible.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu Jun 11 20:18:43 2009
 *
 *  Implementación de la clase invisible.
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

#include <yage/game/collidable.hpp>
#include "invisible.hpp"

using namespace yage;

namespace dose
{
namespace ent
{

invisible::invisible (const yage::base::point3f& min,
		      const yage::base::point3f& max)
{
    game::aabb b ( min, max );
    set_bounds (b);
}

} /* namespace  ent en e   */
} /* namespace dose */
