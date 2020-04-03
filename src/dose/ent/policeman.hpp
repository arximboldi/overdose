/**
 *  Time-stamp:  <2009-06-13 23:29:13 raskolnikov>
 *
 *  @file        policeman.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sat Jun 13 21:59:13 2009
 *
 *  Interfaz de la clase policeman.
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

#ifndef DOSE_POLICEMAN_H_
#define DOSE_POLICEMAN_H_

#include <dose/ent/pedestrian.hpp>

namespace dose
{
namespace ent
{

class policeman : public pedestrian
{
public:
    policeman (float walk_speed = DEFAULT_WALK_SPEED,
	       float rotate_speed = DEFAULT_ROTATE_SPEED);

    void handle_collision (yage::game::entity& other,
			   yage::game::collidable& box,
			   yage::game::dynamic_collision& col);

    void update (int delta);
    
private:
    void follow_state (int delta);
    bool player_in_fov ();
    bool player_in_line ();
    bool player_has_drugs ();
    bool player_in_distance ();

    int m_old_action;
};

typedef boost::shared_ptr<policeman> policeman_ptr;

} /* namespace ent */
} /* namespace dose */

#endif /* DOSE_POLICEMAN_H_ */
