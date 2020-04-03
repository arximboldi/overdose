/**
 *  @file        camera.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 12:04:06 2009
 *
 *  Declaracion de la camara.
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

#ifndef YAGE_CAMERA_H
#define YAGE_CAMERA_H

#include <boost/shared_ptr.hpp>
#include <yage/base/point3.hpp>

namespace yage
{
namespace gra
{

class camera
{
public:
    static constexpr float DEFAULT_RATIO = 1.0f;
    static constexpr float DEFAULT_FOV = 45.0f;

    camera (const base::point3f& pos = base::point3f (0, 0, 0));

    void apply_projection (size_t viewport_width,
			   size_t viewport_height);

    void apply_model_rotation ();
    void apply_model_translation ();

    float get_fov () const
    {
	return m_fov;
    }

    float get_ratio () const
    {
	return m_ratio;
    }

    void set_fov (float angle)
    {
	m_fov = angle;
    }

    void set_ratio (float ratio)
    {
	m_ratio = ratio;
    }

    void set_near_plane (float val)
    {
	m_near = val;
    }

    void set_far_plane (float val)
    {
	m_far = val;
    }

    void set_position (const base::point3f& pos);
    void set_plane_normal (const base::point3f& pos);
    void set_up_vector (const base::point3f& pos);

    void look_at (const base::point3f& pos);

    const base::point3f& get_position () const
    {
	return m_vrp;
    }

    const base::point3f& get_plane_normal () const
    {
	return m_vpn;
    }

    const base::point3f& get_up_vector () const
    {
	return m_vup;
    }

private:
    float m_fov;
    float m_ratio;
    float m_near;
    float m_far;

    base::point3f m_vrp;
    base::point3f m_vpn;
    base::point3f m_vup;
};

typedef boost::shared_ptr<camera> camera_ptr;

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_CAMERA_H */
