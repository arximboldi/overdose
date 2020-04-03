/**
 *  Time-stamp:  <2009-06-17 11:56:01 raskolnikov>
 *
 *  @file        alcohol.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 12:02:12 2009
 *
 *  Implementación de la clase alcohol.
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

#include <yage/gra/animation_task.hpp>
#include <yage/gra/fog.hpp>
#include <yage/gra/scene.hpp>

#include "dose/st/level.hpp"
#include "alcohol.hpp"

using namespace yage;
using namespace boost;

namespace dose
{
namespace drug
{


const float FX_FOG = 0.006f;
const float FX_DURATION = 2000.0f;

alcohol::alcohol ()
    : dope ("alcohol", "alcohol.png", 0, 1, 1)
{
}

void alcohol::take ()
{
    gra::fog_ptr fog = get_level ()->get_scene ()->get_fog ();
    m_orig_fog = fog->get_density ();

    float min = m_orig_fog;
    float max = FX_FOG;
    
    get_level ()->get_tasks ().add (
	gra::create_function_task<float> (
	    bind (&gra::fog::set_density, fog,
		  bind (gra::linear_function<float,float>, min, max,
			bind (gra::sinusoid<float>, _1))),
	    FX_DURATION
	    ));
}

void alcohol::accumulate (dope_ptr d)
{
    set_progress (get_progress () + 0.5);
    
    gra::fog_ptr fog = get_level ()->get_scene ()->get_fog ();

    float min = fog->get_density ();
    float max = min + (min - m_orig_fog) / 2;
    
    get_level ()->get_tasks ().add (
	gra::create_function_task<float> (
	    bind (&gra::fog::set_density, fog,
		  bind (gra::linear_function<float,float>, min, max, _1)),
	    FX_DURATION));
}

void alcohol::handle_finish ()
{
    gra::fog_ptr fog = get_level ()->get_scene ()->get_fog ();

    const float DEFAULT_FOG = 0.0005;
    float min = fog->get_density ();
    float max = DEFAULT_FOG;
    
    get_level ()->get_tasks ().add (
	gra::create_function_task<float> (
	    bind (&gra::fog::set_density, fog,
		  bind (gra::linear_function<float,float>, min, max, _1)),
	    FX_DURATION));
}

} /* namespace drug */
} /* namespace dose */
