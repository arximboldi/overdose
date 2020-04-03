/**
 *  @file        hell.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Mon Jun 15 10:05:03 2009
 *
 *  Implementación de la clase hell.
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

#include <yage/core/system.hpp>

#include <yage/gra/light.hpp>
#include <yage/gra/fog.hpp>
#include <yage/gra/scene.hpp>

#include "dose/ent/invisible.hpp"
#include "dose/ent/player.hpp"
#include "hell.hpp"

using namespace yage;
using namespace yage::base;

namespace dose
{
namespace st
{

void hell::setup_floor ()
{
    add_floor ("floor2.png", 20000, 20000, 0, 50, 50, point3f (0, -2, 0));
}

void hell::setup_buildings ()
{
    add_entity ("bounds_south", game::entity_ptr (
		    new ent::invisible (point3f (-5000, 0, -5000), point3f (-5000, 0, 5000))));
    add_entity ("bounds_north", game::entity_ptr (
		    new ent::invisible (point3f (5000, 0, -5000), point3f (5000, 0, 5000))));
    add_entity ("bounds_east", game::entity_ptr (
		    new ent::invisible (point3f (-5000, 0, 5000), point3f (5000, 0, 5000))));
    add_entity ("bounds_west", game::entity_ptr (
		    new ent::invisible (point3f (-5000, 0, -5000), point3f (5000, 0, -5000))));
}

void hell::setup_lights ()
{
    {
	gra::light_ptr lit (new gra::light);

	lit->enable ();
	lit->set_diffuse (base::point4f (1, 0.2, 0.2, 1));
	lit->set_ambient (base::point4f (0.3, 0.1, 0.1, 1));
	lit->set_specular (base::point4f (1, 0.9, 0.9, 1));

	get_scene ()->get_root ().get_child ("light0").add_drawable (lit);
	get_scene ()->get_root ().get_child ("light0").set_position (base::point3f (0, -1000, 0));
    }

    {
	gra::light_ptr lit (new gra::light);

	lit->enable ();
	lit->set_diffuse (base::point4f (1, 0.2, 0.2, 1));
	lit->set_ambient (base::point4f (0.3, 0.1, 0.1, 1));
	lit->set_specular (base::point4f (1, 0.9, 0.9, 1));

	get_scene ()->get_root ().get_child ("light1").add_drawable (lit);
	get_scene ()->get_root ().get_child ("light1").set_position (base::point3f (0, 1000, 0));
    }

    get_scene ()->get_fog ()->set_color (point4f (0, 0, 0, 1));
    core::system::self ().graphic ().set_clear_color (
	get_scene ()->get_fog ()->get_color ());
}

void hell::setup_people ()
{
    const play_area area = { -2000, -2000, 2000, 2000};

    const int num_pedestrian_models = 2;
    const md2_id pedestrian_models [] =
	{ {"momia.md2", "momia.tga", true},
	  {"bauul.md2", "bauul.png", true}};

    const int num_dealer_models = 2;
    const md2_id dealer_models [] =
	{ {"beelzabub.md2", "beelzabub.png", true},
	  {"jack.md2", "jack_demon.pcx", false} };

    const int max_drug = 20;

    const int num_dealer = 30;
    const int num_pedestrian = 30;

    for (int i = 0; i < num_pedestrian; ++i)
	add_random_pedestrian (num_pedestrian_models, pedestrian_models, area);
    for (int i = 0; i < num_dealer; ++i)
	add_random_dealer (num_dealer_models, dealer_models, area, max_drug);
}

void hell::init ()
{
    set_sky ("hell_mid_fog.png");

    setup_buildings ();
    setup_lights ();
    setup_people ();

    setup_floor ();
    finish_setup ();

    get_player ()->set_god (true);
}

std::string hell::loading ()
{
    return "hell.png";
}

} /* namespace st */
} /* namespace dose */
