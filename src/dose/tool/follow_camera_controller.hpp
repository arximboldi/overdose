/**
 *  @file        follow_camera_controller.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 24 11:48:05 2009
 *
 *  Interfaz de follow_camera_controller.
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

#ifndef DOSE_FOLLOW_CAMERA_CONTROLLER_H_
#define DOSE_FOLLOW_CAMERA_CONTROLLER_H_

#include <cmath>
#include <boost/shared_ptr.hpp>

#include <yage/core/mouse_observer.hpp>
#include <yage/gra/camera.hpp>
#include <yage/game/entity_observer.hpp>
#include <yage/game/entity.hpp>

namespace dose
{
namespace tool
{

class follow_camera_controller : public yage::game::entity_listener
			       , public yage::core::mouse_listener
{
public:
    static constexpr float DEFAULT_DISTANCE = 80.0;
    static constexpr float DEFAULT_ANGLE    = M_PI / 16;
    static constexpr float DEFAULT_SPEED    = 0.01;

    follow_camera_controller (yage::gra::camera_ptr cam,
			      yage::game::entity_ptr ent,
			      float distance = 75.0,
			      float angle  = M_PI/16,
			      float speed = 0.01);

    void handle_entity_move (yage::game::entity& p);
    void handle_entity_rotate (yage::game::entity& p);

    bool handle_mouse_move (SDL_Event& ev);
    bool handle_mouse_button_press (SDL_Event& ev);
    bool handle_mouse_button_release (SDL_Event& ev);

    void recalculate ();

    float get_vangle ()
    {
	return m_angle;
    }

    void set_vangle (float angle)
    {
	m_angle = angle;
	recalculate ();
    }

    float get_hangle ()
    {
	return m_hangle;
    }

    void set_hangle (float angle)
    {
	m_hangle = angle;
	recalculate ();
    }

    float get_distance () const
    {
	return m_distance;
    }

    void set_distance (float distance)
    {
	m_distance = distance;
	recalculate ();
    }

private:
    yage::gra::camera_ptr m_camera;
    yage::game::entity_ptr m_entity;
    yage::base::point3f m_old_pos;
    yage::base::point3f m_old_orient;

    float m_distance;
    float m_angle;

    float m_hangle;
    float m_speed;
};

} /* namespace tool */
} /* namespace dose */

#endif /* DOSE_FOLLOW_CAMERA_CONTROLLER_H_ */
