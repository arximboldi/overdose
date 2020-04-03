/**
 *  @file        bubbly_camera.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sat Jun 13 18:33:52 2009
 *
 *  Implementación de la clase bubbly_camera.
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

#include <cmath>
#include "bubbly_camera.hpp"

namespace dose
{
namespace drug
{

bubbly_camera::bubbly_camera (yage::gra::camera_ptr cam,
			      float depth,
			      float ratio_speed,
			      float fov_speed)
    : m_camera (cam)
    , m_depth (depth)
    , m_ratio_pos (0)
    , m_fov_pos (0)
    , m_ratio_speed (ratio_speed)
    , m_fov_speed (fov_speed)
    , m_orig_ratio (cam->get_ratio ())
    , m_orig_fov (cam->get_fov ())
{
}

void bubbly_camera::update (int delta)
{
    m_camera->set_ratio (m_orig_ratio + m_orig_ratio * m_depth * std::sin (m_ratio_pos));
    m_camera->set_fov (m_orig_fov + m_orig_fov * m_depth * std::sin (m_fov_pos));

    m_ratio_pos += delta * m_ratio_speed;
    m_fov_pos += delta * m_fov_speed;
}

} /* namespace drug */
} /* namespace dose */
