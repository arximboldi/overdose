/**
 *  @file        building.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 12:03:52 2009
 *
 *  Interfaz de la clase building.
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

#ifndef DOSE_BUILDING_H_
#define DOSE_BUILDING_H_

#include <yage/game/entity.hpp>

namespace dose
{
namespace ent
{

class building : public yage::game::entity
{
public:
    building (float wide,
	      float deep,
	      float high,
	      const std::string& f_tex,
	      const std::string& s_tex,
	      const std::string& t_tex,
	      float tile_f = 1,
	      float tile_s = 1,
	      float tile_t = 1);

    void handle_collision (yage::game::entity&,
			   yage::game::collidable&,
			   yage::game::dynamic_collision&);
    void update (int delta);
};

} /* namespace ent */
} /* namespace dose */

#endif /* DOSE_BUILDING_H_ */
