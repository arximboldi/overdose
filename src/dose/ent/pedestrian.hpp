/**
 *  @file        pedestrian.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Wed Jun 10 19:49:13 2009
 *
 *  Interfaz de la clase pedestrian.
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

#ifndef DOSE_PEDESTRIAN_H_
#define DOSE_PEDESTRIAN_H_

#include <yage/core/state_task.hpp>
#include <dose/ent/person.hpp>

namespace dose
{
namespace ent
{

class pedestrian : public person
{
public:
    pedestrian (const std::string& model,
		const std::string& texture,
		bool inverse_normals = false,
		float walk_speed = DEFAULT_WALK_SPEED,
		float rotate_speed = DEFAULT_ROTATE_SPEED);
    void update (int delta);
    void handle_collision (yage::game::entity& other,
			   yage::game::collidable& box,
			   yage::game::dynamic_collision& col);

protected:
    float angle_to_player ();
    float sq_distance_to_player ();

    yage::core::state_task& states ()
    {
	return m_states;
    }

private:
    void rotate_state (int delta);
    void walk_state (int delta);
    void idle_state (int delta);

    yage::core::state_task m_states;

    float m_dest_angle;
    int m_ticks;
    int m_old_action;
};

} /* namespace ent */
} /* namespace dose */

#endif /* DOSE_PEDESTRIAN_H_ */
