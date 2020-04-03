/**
 *  @file        marihuana.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 11:46:46 2009
 *
 *  Implementación de la clase marihuana.
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

#include <boost/bind.hpp>

#include <yage/base/misc.hpp>
#include <yage/gra/animation_task.hpp>

#include "dose/st/level.hpp"
#include "bubbly_camera.hpp"
#include "marihuana.hpp"

using namespace yage;
using namespace boost;

namespace dose
{
namespace drug
{

const float FX_DEPTH = 0.15;
const float FX_SPEED_MIN = 0.002;
const float FX_SPEED_MAX = 0.008;
const float FX_DURATION = 2000.0f;

marihuana::marihuana ()
    : dope ("marihuana",
	    "marihuana.png",
	    1.0f, 2.0f, 0.0f)
{
}

void marihuana::take ()
{
    m_camfx.reset (
	new bubbly_camera (get_level ()->get_player_camera (), FX_DEPTH,
			   base::ranged_random (FX_SPEED_MIN, FX_SPEED_MAX),
			   base::ranged_random (FX_SPEED_MIN, FX_SPEED_MAX)));
    get_level ()->get_tasks ().add (m_camfx);
}

void marihuana::accumulate (dope_ptr d)
{
    set_progress (get_progress () + 0.5);

    m_camfx->set_ratio_speed (m_camfx->get_ratio_speed () *
			      base::ranged_random (1.6, 1.8));
    m_camfx->set_fov_speed (m_camfx->get_fov_speed () *
			    base::ranged_random (1.6, 1.8));
    m_camfx->set_depth (m_camfx->get_depth () *
			base::ranged_random (1.6, 1.8));
}

void marihuana::handle_finish ()
{
    m_camfx->finish ();

    /* Restore fov */
    {
	gra::camera_ptr cam = m_camfx->get_camera ();
	float min = cam->get_ratio ();
	float max = m_camfx->get_original_ratio ();

	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&gra::camera::set_ratio, cam,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }

    /* Restore ratio */
    {
	gra::camera_ptr cam = m_camfx->get_camera ();
	float min = cam->get_fov ();
	float max = m_camfx->get_original_fov ();

	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&gra::camera::set_fov, cam,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }
}

} /* namespace drug */
} /* namespace dose */
