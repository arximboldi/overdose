/**
 *  Time-stamp:  <2009-06-15 19:53:23 raskolnikov>
 *
 *  @file        player.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu Jun 11 23:12:33 2009
 *
 *  Implementación de la clase player.
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

#include <cfloat>

#include <boost/bind.hpp>
#include <yage/base/misc.hpp>
#include <yage/core/trigger_task.hpp>
#include <yage/gra/scene.hpp>
#include <yage/gra/fog.hpp>

#include "dose/drug/dope.hpp"
#include "dose/st/level.hpp"
#include "player.hpp"
#include "dealer.hpp"

using namespace yage;
using namespace yage::base;

namespace dose
{
namespace ent
{

player::player (const std::string& model,
		const std::string& texture,
		bool inverse_normals,
		float walk_speed,
		float rotate_speed)
    : person (model, texture, inverse_normals, walk_speed, rotate_speed)
    , m_dead (false)
    , m_god (false)
    , m_on_adrenaline (false)
    , m_buy_shit (false)
{
}

void player::update (int delta)
{
    if (!m_dead) {
	person::update (delta);
	m_hud.update (delta);

	/* Disminuimos los efectos */
	float dec = -0.00001 * delta;
	m_hud.set_psychodelia (std::max (m_hud.get_psychodelia () + dec, 0.0f));
	m_hud.set_ecstasy (std::max (m_hud.get_ecstasy () + dec, 0.0f));
	m_hud.set_euphoria (std::max (m_hud.get_euphoria () + dec, 0.0f));
    
	/* Buscamos al camello mas cercano */
	level_ptr l = get_level ();
	st::level::dealer_iterator it;
	float min_dist = FLT_MAX;
	dealer_ptr best;

	for (it = l->dealers_begin (); it != l->dealers_end (); ++it) {
	    float this_dist =
		((*it)->get_node ().get_world_position () -
		 get_node ().get_world_position ()).sq_length (); 

	    if (this_dist < min_dist) {
		best = *it;
		min_dist = this_dist; 
	    }
	}

	/* Si hay algun camello cercano trabajamos con el */
	if (min_dist < dealer::PLAYER_DISTANCE * dealer::PLAYER_DISTANCE)
	    manage_dealer (best);
	else
	    m_hud.set_player_message ("");
    
	m_buy_shit = false;

	/* Comprobamos si ha terminado la partida */
	if (m_hud.get_psychodelia () >= player_hud::DRUG_SCALE &&
	    m_hud.get_ecstasy () >= player_hud::DRUG_SCALE &&
	    m_hud.get_euphoria () >= player_hud::DRUG_SCALE &&
	    !m_god)
	{
#if 0
	    get_animation_task ()->add_next (
		core::task_ptr (new core::trigger_task<> (bind (&player::kill, this))));
#else
	    kill ();
#endif
	    m_god = true;
	}
    }
}

void player::manage_dealer (dealer_ptr p)
{
    if (m_buy_shit && p->has_shit ()) {
	if (!m_hud.full ())
	    m_hud.add_drug (p->take_shit ());
	else
	    m_hud.set_player_alert ("You can not carry more drugs!");
    }
    
    if (p->has_shit ())
	m_hud.set_player_message (
	    std::string ("Do you want to buy some ") +
	    p->current_offer ()->get_name () + "?");
    else
	m_hud.set_player_message ("This dealer does not have more drugs!");
}

void player::take_some_shit ()
{
    if (!m_dead && !m_hud.empty () && !is_blocked ()) {
	if (!m_on_adrenaline) {
	    drug::dope_ptr d = m_hud.take_drug ();
	    d->set_level (get_level ());
	    play ("taunt");
	    get_animation_task ()->set_length (
		get_animation_task ()->get_animation ()->get_loop_offset ());
	    get_animation_task ()->add_next (
		core::task_ptr (
		    new core::trigger_task<> (
			bind (&player_hud::apply_drug, &m_hud, d))));
	} else
	    m_hud.set_player_alert ("Can not take drugs on adrenaline!");
    }
}

void player::start_adrenaline ()
{
    m_on_adrenaline = true;
    m_hud.finish_drugs ();
}

void player::finish_adrenaline ()
{
    m_on_adrenaline = false;
}

void player::handle_police ()
{
    if (!m_dead) {
	if (!m_hud.empty ()){
	    m_hud.clear_drugs ();
	    m_hud.set_player_alert ("The police has stolen your dope!");
	}
    }
}

void player::kill ()
{
    st::level_ptr l = get_level ();
    tool::follow_camera_controller&  cam = l->get_player_camera_controller ();

    m_dead = true;
    
    /* Desconectamos las señales del usuario */
    cam.core::mouse_listener::disconnect_all ();
    l->get_player_controller ().disconnect_all ();

    m_hud.finish_drugs ();
    const char* death_anim [] = { "death1", "death2", "death3" };
    play (death_anim [base::ranged_random (0, 3)], 0.3f);
        
    /* Efecto de rotacion horizontal */
    {
	float min = cam.get_hangle ();
	float max = min + 4 * M_PI;
	
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&tool::follow_camera_controller::set_hangle, &cam,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		8000.0f, true));
    }

    /* Ponemos la camara arriba */
    {
	float min = cam.get_vangle ();
	float max = 0.4 * M_PI;

	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&tool::follow_camera_controller::set_vangle, &cam,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		4000.0f));
    }

    /* Ponemos la distancia adecuada */
    {
	float min = cam.get_distance ();
	float max = 200;

	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&tool::follow_camera_controller::set_distance, &cam,
		      bind (gra::linear_function<float,float>, min, max, _1)),
		4000.0f));
    }

    gra::fog_ptr fog = l->get_scene ()->get_fog ();
    /* Ponemos la niebla roja */
    {
	base::point4f min = fog->get_color ();
	base::point4f max = base::point4f (0.8, 0, 0, 1);
    
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&gra::fog::set_color, fog,
		      bind (gra::linear_function<base::point4f, float>, min, max, _1)),
		4000
		));
    }

    /* Ponemos la niebla roja */
    {
	float min = fog->get_density ();
	float max = 0.003;
    
	get_level ()->get_tasks ().add (
	    gra::create_function_task<float> (
		bind (&gra::fog::set_density, fog,
		      bind (gra::linear_function<float, float>, min, max, _1)),
		4000
		));
    }
    
    /* Ya podemos saltar de nivel. */
    l->enable_finish ();
    m_hud.set_player_alert ("Drugs have killed you. Press ENTER to continue.", 15000);
}

} /* namespace ent */
} /* namespace dose */
