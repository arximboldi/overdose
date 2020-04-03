/**
 *  Time-stamp:  <2009-06-10 22:45:44 raskolnikov>
 *
 *  @file        fly_camera_controller.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 18:56:59 2009
 *
 *  Interfaz de fly_camera_controller.hpp
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

#ifndef DOSE_FLY_CAMERA_CONTROLLER_H_
#define DOSE_FLY_CAMERA_CONTROLLER_H_

#include <yage/core/key_observer.hpp>
#include <yage/core/mouse_observer.hpp>
#include <yage/core/task.hpp>
#include <yage/gra/camera.hpp>

namespace dose
{
namespace tool
{

class fly_camera_controller : public yage::core::key_listener
			    , public yage::core::mouse_listener
			    , public yage::core::task
{
public:
    static const float DEFAULT_MOVE_SPEED = 0.5;
    static const float DEFAULT_ROTATE_SPEED = 0.005;
    
    fly_camera_controller (yage::gra::camera_ptr cam = yage::gra::camera_ptr (),
			   float move_speed   = DEFAULT_MOVE_SPEED,
			   float rotate_speed = DEFAULT_ROTATE_SPEED);
    
    void update (int delta);
    
    bool handle_key_press (SDL_Event& ev);
    bool handle_key_release (SDL_Event& ev);
    bool handle_mouse_move (SDL_Event& ev);
    
    bool handle_mouse_button_press (SDL_Event& ev)
    {
	return false;
    }
    
    bool handle_mouse_button_release (SDL_Event& ev)
    {
	return false;
    }
    
    void set_camera (yage::gra::camera_ptr cam)
    {
	m_camera = cam;
    }
    
private:
    enum movement
    {
	STRAFE_LEFT   = 1,
	STRAFE_RIGHT  = 1 << 2,
	MOVE_FORWARD  = 1 << 3,
	MOVE_BACKWARD = 1 << 4
    };

    yage::gra::camera_ptr m_camera;
    float m_move_speed;
    float m_rotate_speed;
    int m_move;
};

typedef boost::shared_ptr<fly_camera_controller> fly_camera_controller_ptr;

} /* namespace tool */
} /* namespace dose */

#endif /* DOSE_FLY_CAMERA_CONTROLLER_H_ */
