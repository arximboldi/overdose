/**
 *  Time-stamp:  <2009-06-14 22:24:27 raskolnikov>
 *
 *  @file        lsd.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 11:58:09 2009
 *
 *  Implementación de la clase lsd.
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
#include <yage/gra/fog.hpp>
#include <yage/gra/scene.hpp>
#include <yage/game/entity_manager.hpp>

#include "dose/st/level.hpp"
#include "dose/ent/person.hpp"
#include "lsd.hpp"

using namespace yage;
using namespace boost;

namespace dose
{
namespace drug
{

namespace
{

const float FX_DURATION = 2000.0f;

const base::point4f& random_color ()
{
    const int NUM_COLOR = 3;
    static const base::point4f colors[] =
    {
	base::point4f (0.1, 1, 0.1, 1),
	base::point4f (1, 0.3, 0.1, 1),
	base::point4f (0.4, 0.1, 1, 1)
    };

    return colors [base::ranged_random (0, NUM_COLOR)];
}

} /* anonymous ns */

lsd::lsd ()
    : dope ("LSD", "lsd.png", 3, 1, 0)
{
}

void lsd::take ()
{
    randomize_models ();

    gra::fog_ptr fog = get_level ()->get_scene ()->get_fog ();
    m_orig_fog_color = fog->get_color ();

    base::point4f min = m_orig_fog_color;
    base::point4f max = random_color ();
    
    get_level ()->get_tasks ().add (
	gra::create_function_task<float> (
	    bind (&gra::fog::set_color, fog,
		  bind (gra::linear_function<base::point4f, float>, min, max, _1)),
	    FX_DURATION
	    ));
}

void lsd::accumulate (dope_ptr d)
{
    set_progress (get_progress () + 0.8);
    randomize_models ();
    
    gra::fog_ptr fog = get_level ()->get_scene ()->get_fog ();
    
    base::point4f min = fog->get_color ();
    base::point4f max = random_color ();
    
    get_level ()->get_tasks ().add (
	gra::create_function_task<float> (
	    bind (&gra::fog::set_color, fog,
		  bind (gra::linear_function<base::point4f, float>, min, max, _1)),
	    FX_DURATION
	    ));
}

void lsd::handle_finish ()
{
    restore_models ();

    gra::fog_ptr fog = get_level ()->get_scene ()->get_fog ();
    
    base::point4f min = fog->get_color ();
    base::point4f max = m_orig_fog_color;
    
    get_level ()->get_tasks ().add (
	gra::create_function_task<float> (
	    bind (&gra::fog::set_color, fog,
		  bind (gra::linear_function<base::point4f, float>, min, max, _1)),
	    FX_DURATION
	    ));
}

void lsd::randomize_models ()
{
    const int num_models = 4;
    const char* models [num_models][3] = {
	{"lala.md2", "lala.pcx", (const char*) 1},
	{"lala.md2", "lala_po.pcx", (const char*) 1},
	{"lala.md2", "lala_tinkywinky.pcx", (const char*) 1},
	{"lala.md2", "lala_dipsy.pcx", (const char*) 1}
    };

    game::entity_manager_ptr ents = get_level ()->entities ();
    int m = base::ranged_random (0, num_models);

    for (game::entity_manager::iterator it = ents->dynamic_begin ();
	 it != ents->dynamic_end (); ++it)
    {
	ent::person_ptr p = dynamic_pointer_cast<ent::person> (*it);
	if (p)
	    p->alternate_model (ent::person::load_model (
				    models [m][0], models [m][1], models [m][2]));
	m = (m + 1) % num_models;
    }
}

void lsd::restore_models ()
{
    game::entity_manager_ptr ents = get_level ()->entities ();
    
    for (game::entity_manager::iterator it = ents->dynamic_begin ();
	 it != ents->dynamic_end (); ++it)
    {
	ent::person_ptr p = dynamic_pointer_cast<ent::person> (*it);
	if (p)
	    p->restore_model ();	
    }
}    

} /* namespace drug */
} /* namespace dose */
