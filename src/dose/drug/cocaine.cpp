/**
 *  Time-stamp:  <2009-06-14 22:21:49 raskolnikov>
 *
 *  @file        cocaine.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 11:52:58 2009
 *
 *  Implementación de la clase cocaine.
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

#include "dose/st/level.hpp"
#include "dose/ent/player.hpp"
#include "cocaine.hpp"

using namespace yage;
using namespace boost;

namespace dose
{
namespace drug

{

const float FX_WALK_SPEED = 0.4f;
const float FX_ROTATE_SPEED = 0.006f;
const float FX_DURATION = 2000.0f;

cocaine::cocaine ()
    : dope ("cocaine", "cocaine.png", 0, 1, 2)
{
}

void cocaine::take ()
{
    /* Alteramos los controles */
    get_level ()->get_player_controller ().randomize_keys ();

    ent::player_ptr player = get_level ()->get_player ();

    /* Alteramos la velocidad al andar */
    {
	m_orig_walk_speed = player->get_walk_speed ();
	
	float min = m_orig_walk_speed;
	float max = FX_WALK_SPEED;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&ent::player::set_walk_speed, player,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }

    /* Alteramos la velocidad al rotar */
    {
	m_orig_rotate_speed = player->get_rotate_speed ();
	
	float min = m_orig_rotate_speed;
	float max = FX_ROTATE_SPEED;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&ent::player::set_rotate_speed, player,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }
}

void cocaine::accumulate (dope_ptr d)
{
    set_progress (get_progress () + 0.7);

    /* Alteramos las teclas */
    get_level ()->get_player_controller ().randomize_keys ();

    ent::player_ptr player = get_level ()->get_player ();
	
    /* Alteramos la velocidad al caminar */
    {	
	float min = player->get_walk_speed ();
	float max = min + (min - m_orig_walk_speed) / 2;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&ent::player::set_walk_speed, player,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }

    /* Alteramos la velocidad al rotar */
    {
	float min = player->get_rotate_speed ();
	float max = min + (min - m_orig_rotate_speed) / 2;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&ent::player::set_rotate_speed, player,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }
}

void cocaine::handle_finish ()
{
    /* Reestablecemos las teclas */
    get_level ()->get_player_controller ().restore_keys ();

    ent::player_ptr player = get_level ()->get_player ();
	
    /* Restauramos la velocidad al caminar */
    {	
	float min = player->get_walk_speed ();
	float max = ent::player::DEFAULT_WALK_SPEED;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&ent::player::set_walk_speed, player,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }

    /* Restauramos la velocidad al rotar */
    {
	float min = player->get_rotate_speed ();
	float max = ent::player::DEFAULT_ROTATE_SPEED;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&ent::player::set_rotate_speed, player,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		FX_DURATION));
    }
}

} /* namespace drug */
} /* namespace dose */
