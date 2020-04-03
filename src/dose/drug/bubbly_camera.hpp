/**
 *  Time-stamp:  <2009-06-13 19:26:40 raskolnikov>
 *
 *  @file        bubbly_camera.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sat Jun 13 18:32:15 2009
 *
 *  Interfaz de la clase bubbly_camera.
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

#ifndef DOSE_BUBBLY_CAMERA_H_
#define DOSE_BUBBLY_CAMERA_H_

#include <yage/core/task.hpp>
#include <yage/gra/camera.hpp>

namespace dose
{
namespace drug
{

class bubbly_camera : public yage::core::task
{
public:
    bubbly_camera (yage::gra::camera_ptr cam,
		   float depth = 0.5,
		   float ratio_speed = 0.01,
		   float fov_speed = 0.01);

    void update (int delta);

    yage::gra::camera_ptr get_camera ()
    {
	return m_camera;
    }
    
    void set_depth (float depth)
    {
	m_depth = depth; 
    }
    
    void set_ratio_speed (float speed)
    {
	m_ratio_speed = speed;
    }

    void set_fov_speed (float speed)
    {
	m_fov_speed = speed;
    }

    float get_depth () const
    {
	return m_depth;
    }
    
    float get_ratio_speed () const
    {
	return m_ratio_speed;
    }

    float get_fov_speed () const
    {
	return m_fov_speed;
    }
    
    float get_original_ratio ()
    {
	return m_orig_ratio;
    }

    float get_original_fov ()
    {
	return m_orig_fov;
    }
    
private:
    yage::gra::camera_ptr m_camera;

    float m_depth;
    
    float m_ratio_pos;
    float m_fov_pos;
    float m_ratio_speed;
    float m_fov_speed;
    
    float m_orig_ratio;
    float m_orig_fov;
};

typedef boost::shared_ptr<bubbly_camera> bubbly_camera_ptr;

} /* namespace drug */
} /* namespace dose */

#endif /* DOSE_BUBBLY_CAMERA_H_ */
