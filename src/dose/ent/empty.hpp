/**
 *  Time-stamp:  <2009-06-14 11:41:37 raskolnikov>
 *
 *  @file        empty.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun Jun 14 11:39:49 2009
 *
 *  Interfaz de la clase empty.
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

#ifndef DOSE_EMPTY_H_
#define DOSE_EMPTY_H_

#include <yage/game/entity.hpp>

namespace dose
{
namespace ent
{

class empty : public yage::game::entity
{
public:
    void update (int) {}
    void handle_collision (yage::game::entity&,
			   yage::game::collidable&,
			   yage::game::dynamic_collision&) {}
};

} /* namespace dose */
} /* namespace ent */

#endif /* DOSE_EMPTY_H_ */

