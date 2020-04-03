/**
 *  Time-stamp:  <2009-06-14 22:26:18 raskolnikov>
 *
 *  @file        adrenaline.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sat Jun 13 19:42:18 2009
 *
 *  Implementaciín de la clase adrenaline.
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

#include <yage/gra/camera.hpp>
#include <yage/gra/animation_task.hpp>

#include "dose/st/level.hpp"
#include "dose/ent/player.hpp"
#include "adrenaline.hpp"

using namespace boost;
using namespace yage;

namespace dose
{
namespace drug
{

const float FX_FOV = 90;
const float FX_WALK_SPEED = 0.5;
const float FX_ROTATE_SPEED = 0.007f;
const float FX_DURATION = 2100.0f;

adrenaline::adrenaline ()
    : dope ("adrenaline", "adrenaline.png",
	    -0.6, -0.6, 1.0, 1.0f, DEFAULT_DOPE_SPEED * 4.0f)
{
}

void adrenaline::take ()
{
    /* Anulamos otros efectos y bloqueamos el consumo de sustancias */
    get_level ()->get_player ()->start_adrenaline ();

    ent::player_ptr player = get_level ()->get_player ();
    gra::camera_ptr camera = get_level ()->get_player_camera ();
    
    /* Alteramos la velocidad al andar */
    {	
	float min = player->get_walk_speed ();
	float max = FX_WALK_SPEED;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&ent::player::set_walk_speed, player,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }

    /* Alteramos la velocidad al rotar */
    {	
	float min = player->get_rotate_speed ();
	float max = FX_ROTATE_SPEED;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&ent::player::set_rotate_speed, player,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }

    /* Alteramos el angulo de vision */
    {	
	float min = camera->get_fov ();
	float max = FX_FOV;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&gra::camera::set_fov, camera,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }
}

void adrenaline::accumulate (dope_ptr p)
{
    assert (false); /* La adrenalina deberia prohibir esto */
}

void adrenaline::handle_finish ()
{
    /* Liberamos de nuevo el bloqueo */
    get_level ()->get_player ()->finish_adrenaline ();

    ent::player_ptr player = get_level ()->get_player ();
    gra::camera_ptr camera = get_level ()->get_player_camera ();
    
    /* Alteramos la velocidad al andar */
    {	
	float min = player->get_walk_speed ();
	float max = ent::player::DEFAULT_WALK_SPEED;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&ent::player::set_walk_speed, player,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }

    /* Alteramos la velocidad al rotar */
    {	
	float min = player->get_rotate_speed ();
	float max = ent::player::DEFAULT_ROTATE_SPEED;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&ent::player::set_rotate_speed, player,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }

    /* Alteramos el angulo de vision */
    {	
	float min = camera->get_fov ();
	float max = gra::camera::DEFAULT_FOV;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&gra::camera::set_fov, camera,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }
}

} /* namespace drug */
} /* namespace dose */
