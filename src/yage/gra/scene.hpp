/**
 *  @file        scene.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 21 20:47:02 2009
 *
 *  Interfaz de la clase scene.
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

#ifndef YAGE_SCENE_H_
#define YAGE_SCENE_H_

#include <yage/gra/scene_node.hpp>

namespace yage
{
namespace gra
{

class camera;
class fog;

class scene
{
public:
    void render (int vp_width, int vp_height);

    scene_node& get_root ()
    {
	return m_root;
    }

    scene_node& get_hud_root ()
    {
	return m_hud_root;
    }

    boost::shared_ptr<drawable> get_sky ()
    {
	return m_sky;
    }

    void set_sky (boost::shared_ptr<drawable> sky,
		  const base::point3f& scale = base::point3f (15000, 15000, 15000))
    {
	m_sky = sky;
	m_sky_scale = scale;
    }

    boost::shared_ptr<camera> get_camera ()
    {
	return m_camera;
    }

    void set_camera (boost::shared_ptr<camera> cam)
    {
	m_camera = cam;
    }

    boost::shared_ptr<fog> get_fog ()
    {
	return m_fog;
    }

    void set_fog (boost::shared_ptr<fog> fog)
    {
	m_fog = fog;
    }

private:
    void setup_perspective (int vp_width, int vp_height);
    void setup_ortho (int vp_width, int vp_height);

    base::point3f m_sky_scale;
    boost::shared_ptr<drawable> m_sky;
    boost::shared_ptr<camera>   m_camera;
    boost::shared_ptr<fog>      m_fog;
    scene_node m_root;
    scene_node m_hud_root;
};

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_SCENE_H_ */
