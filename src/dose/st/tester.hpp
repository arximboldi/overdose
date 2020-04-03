/**
 *  @file        tester.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 16:54:01 2009
 *
 *  Declaración de la clase tester.
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

#ifndef DOSE_TESTER_H_
#define DOSE_TESTER_H_

#include <yage/core/system.hpp>
#include <yage/gra/light.hpp>
#include <yage/gra/scene.hpp>
#include <yage/gra/camera.hpp>
#include <yage/gra/texture.hpp>
#include <yage/gra/text.hpp>
#include <yage/gra/fog.hpp>
#include <yage/gra/material.hpp>
#include <yage/geo/md2_model.hpp>
#include <yage/geo/sphere.hpp>
#include <yage/geo/textured_plane.hpp>
#include <yage/geo/textured_hemisphere.hpp>
#include <yage/gra/animation_task.hpp>
#include <yage/game/state.hpp>

namespace dose
{
namespace st
{

class tester : public yage::game::state
	     , public yage::core::key_listener
	     , public yage::core::mouse_listener
{
public:
    tester ();

    bool handle_key_press (SDL_Event& ev);

    bool handle_key_release (SDL_Event& ev)
    {
	return false;
    }

    bool handle_mouse_move (SDL_Event& ev)
    {
	return false;
    }

    bool handle_mouse_button_press (SDL_Event& ev)
    {
	return false;
    }

    bool handle_mouse_button_release (SDL_Event& ev)
    {
	return false;
    }

private:
    float m_rad;
    float m_angle, m_angle2;
    boost::shared_ptr<yage::geo::md2_model> m_model;
    boost::shared_ptr<yage::gra::light>     m_light;
    boost::shared_ptr<yage::gra::camera>    m_camera;
    boost::shared_ptr<yage::gra::text>      m_text;
};

} /* namespace st */
} /* namespace dose */

#endif /* DOSE_TESTER_H_ */
