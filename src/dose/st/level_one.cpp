/**
 *  Time-stamp:  <2010-01-14 19:49:04 raskolnikov>
 *
 *  @file        level_one.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 18:45:59 2009
 *
 *  Implementación de la clase level_one.
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

#include <yage/base/misc.hpp>
#include <yage/core/system.hpp>

#include <yage/gra/scene.hpp>
#include <yage/gra/light.hpp>
#include <yage/gra/fog.hpp>

#include "dose/ent/invisible.hpp"
#include "dose/ent/empty.hpp"

#include "level_one.hpp"

using namespace yage;
using namespace yage::base;
using namespace yage::game;
using namespace boost;

namespace dose
{
namespace st
{

void level_one::setup_floor ()
{
    add_floor ("floor.png", 10000, 10000, 0, 20, 20, point3f (0, -2, 0));
    add_floor ("road_2.png", 200, 900, 0, 1.8, 1, point3f (0, 0, -50));
    add_floor ("troad.png", 10000, 400, 0, 1, 20, point3f (0, -0.5, -650));
    add_floor ("path.png", 150, 700, 0, 2, 1, point3f (-75, 0, -1180));
    add_floor ("path.png", 150, 700, 0, 2, 1, point3f (-520, 0, -1180));
    add_floor ("path.png", 150, 700, 0, 2, 1, point3f (970, 0, -1200));
    add_floor ("path.png", 150, 700, 0, 2, 1, point3f (-980, 0, -1180));
    add_floor ("path.png", 150, 2720, 90, 7, 1, point3f (-320, 1, -1580));
    add_floor ("path.png", 150, 1050, 90, 3, 1, point3f (500, -0.5, -1050));
    add_floor ("grass.png", 2600, 1000, 0, 4, 13, point3f (-400, -1, -1300));
    add_floor ("asphalt2.png", 1400, 1150, 0, 4, 5, point3f (1700, 1, 135));
}

void level_one::setup_buildings ()
{
    add_object ("excavator_b.md2", "excavator.png",
		aabb (point3f (-80, 0, -50), point3f (150, 200, 50)),
		point3f (500, 0, 200)); 
    add_object ("excavator_t.md2", "excavator.png",
		aabb (),
		point3f (500, 0, 200));

    add_object ("excavator_b.md2", "excavator.png",
		aabb (point3f (-80, 0, -50), point3f (150, 200, 50)),
		point3f (-1100, 0, 250)); 
    add_object ("excavator_t.md2", "excavator.png",
		aabb (),
		point3f (-1100, 0, 250));
    
    add_object ("forktruck.md2", "forktruck.png",
		aabb (point3f (-25, 0, -60), point3f (25, 200, 70)),
		point3f (500, 0, -200));
    add_object ("car.md2", "car.png",
		aabb (point3f (-33, 0, -70), point3f (33, 200, 80)),
		point3f (1500, 0, 0), point3f (0.5, 0.5, 0.5));
    add_object ("van.md2", "van.tga",
		aabb (point3f (-80, 0, -40), point3f (80, 200, 40)),
		point3f (1500, 0, 300), point3f (0.39, 0.39, 0.39));
    add_object ("truck.md2", "truck.tga",
		aabb (point3f (-40, 0, -95), point3f (40, 200, 100)),
		point3f (2300, -15, 0));
    add_object ("fountan2.md2", "fountan2.tga",
		sphere (point3f (0, 30, 0), 140),
		point3f (300, 0, -1300));

    add_object ("policecar.md2", "policecar.tga",
		aabb (point3f (-30, 0, -100), point3f (30, 200, 100)),
		point3f (2500, 0, -700));
    add_object ("policecar.md2", "policecar.tga",
		aabb (point3f (-30, 0, -100), point3f (30, 200, 100)),
		point3f (2500, 0, -550));
    add_object ("policecar.md2", "policecar.tga",
		aabb (point3f (-30, 0, -100), point3f (30, 200, 100)),
		point3f (-1700, 0, -700));
    add_object ("policecar.md2", "policecar.tga",
		aabb (point3f (-30, 0, -100), point3f (30, 200, 100)),
		point3f (-1700, 0, -550));

    add_object ("cement_trailer.md2", "cement_trailer.tga",
		aabb (point3f (-50, 0, -180), point3f (50, 200, 10)),
		point3f (1500, 0, -1000), point3f (1, 1, 1));

    add_object ("crane_a.md2", "crane.tga",
		aabb (point3f (-105, 0, -150), point3f (105, 200, 150)),
		point3f (2000, 0, -1300), point3f (1.5, 1.5, 1.5));
    add_object ("crane_b.md2", "crane.tga",
		aabb (point3f (-10, 0, -10), point3f (10, 10, 10)),
		point3f (2000, 0, -1300), point3f (1.5, 1.5, 1.5));
    add_object ("crane_c.md2", "crane.tga",
		aabb (point3f (-10, 0, -10), point3f (10, 10, 10)),
		point3f (2000, 0, -1300), point3f (1.5, 1.5, 1.5));
    add_object ("crane_d.md2", "crane.tga",
		aabb (point3f (-10, 0, -10), point3f (10, 10, 10)),
		point3f (2000, 0, -1300), point3f (1.5, 1.5, 1.5));
    add_object ("crane_e.md2", "crane.tga",
		aabb (point3f (-10, 0, -10), point3f (10, 10, 10)),
		point3f (2000, 0, -1300), point3f (1.5, 1.5, 1.5));
    
    add_object ("skelet.md2", "skeleton.png",
		sphere (point3f (0, 30, -10), 30),
		point3f (-150, 0, 430));
    add_object ("motor.md2", "motor.tga",
		aabb (point3f (-40, 0, -10), point3f (30, 200, 10)),
		point3f (-1500, 0, 0));
    add_object ("motor.md2", "motor.tga",
		aabb (point3f (-40, 0, -10), point3f (30, 200, 10)),
		point3f (-1480, 0, 40));
	
    add_building ("industrial.png", "indus_s.png", "indus_t.png",
		  700, 100, 150, point3f (2000, 0, 0));
    add_building ("indus_s.png", "industrial2.png", "indus_t.png",
		  100, 800, 150, point3f (1550, 0, -400), 1, 2);
    add_building ("industrial3.png", "indus_s.png", "indus_t.png",
		  1000, 200, 250, point3f (2500, 0, 50), 2);

    /* Edificios de la zona en obras */
    add_building ("derelic2.png", "derelic2.png", "build1_t.png",
		  240, 240, 600, point3f (420, 0, 500));
    add_building ("derelic3.png", "derelic3.png", "build1_t.png",
		  600, 300, 400, point3f (920, 0, 250), 2);

    /* Barreras de la zona en obras */
    add_building ("rooftile.png", "rooftile.png", "rooftile.png",
		  2, 200, 60, point3f (400, 0, -400), 0.05, 1, 1);
    add_building ("rooftile.png", "rooftile.png", "rooftile.png",
		  2, 200, 60, point3f (700, 0, -400), 0.05, 1, 1);
    add_building ("rooftile.png", "rooftile.png", "rooftile.png",
		  400, 2, 60, point3f (800, 0, -200), 2, 0.05, 1);
    add_building ("barrier.png", "barrier.png", "barrier.png",
		  10, 4200, 80, point3f (400, 0.5, 620), 1, 18, 18);
    add_building ("barrier.png", "barrier.png", "barrier.png",
		  200, 10, 80, point3f (2500, 0, 525), 1, 1, 0.02);
    add_building ("barrier.png", "barrier.png", "barrier.png",
		  1100, 10, 80, point3f (-1700, 0, 80), 5, 1, 0.02);
    
    /* Zona de salida */
    add_building ("build1_f.png", "build1_s.png", "build1_t.png",
		  800, 200, 500, point3f (200, 0, 0));
    add_building ("indus_f.png", "indus_s.png", "indus_t.png",
		  300, 100, 100, point3f (-150, 0, 0));
    add_building ("plank_2.png", "plank.png", "plank_3.png",
		  10, 300, 60, point3f (-50, 0, 400), 1, 2, 2);
    add_building ("plank.png", "plank_2.png", "plank_2.png",
		  800, 10, 60, point3f (-200, 0, 0), 5, 1, 1);

    /* Zona ruina */
    add_building ("build2_s.png", "wall.png", "build1_t.png",
		  150, 600, 400, point3f (-450, 0, -400));
    add_building ("wall.png", "build2_s.png", "build1_t.png",
		  600, 150, 400, point3f (-700, 0, 150));
    add_building ("derelic2.png", "derelic2.png", "build1_t.png",
		  240, 240, 600, point3f (-900, 0, 550));
    add_building ("derelic2.png", "derelic2.png", "build1_t.png",
		  240, 240, 600, point3f (-1200, 0, 550));
    add_building ("derelic4.png", "build2_s.png", "build1_t.png",
		  400, 150, 250, point3f (-1700, 0, 150));

    add_building ("rooftile.png", "rooftile.png", "rooftile.png",
		  2, 600, 60, point3f (-1100, 0, -450), 0.05, 3, 1);
	
    /* Calle principal y zona pija */
    add_building ("azulejo.png", "white.png", "build1_t.png", 150, 400, 450, point3f (190, 0, -900));

    add_building ("flat.png", "flat.png", "build1_t.png", 300, 300, 700, point3f (-290, 0, -960));
    add_building ("flat.png", "flat.png", "build1_t.png", 300, 300, 700, point3f (-290, 0, -1320));
    add_building ("flat.png", "flat.png", "build1_t.png", 300, 300, 700, point3f (-750, 0, -960));
    add_building ("flat.png", "flat.png", "build1_t.png", 300, 300, 700, point3f (-750, 0, -1320));
    add_building ("flat.png", "flat.png", "build1_t.png", 300, 300, 700, point3f (-1210, 0, -960));
    add_building ("flat.png", "flat.png", "build1_t.png", 300, 300, 700, point3f (-1210, 0, -1320));

    add_building ("plank_2.png", "plank.png", "plank_3.png", 10, 4200, 60, point3f (400, 0.5, -1750), 1, 28, 28);
    add_building ("plank.png", "plank_2.png", "plank_2.png", 950, 10, 60, point3f (-1700, 0, -1270), 6, 1, 1);
    add_building ("plank.png", "plank_2.png", "plank_2.png", 950, 10, 60, point3f (2500, 0, -1270), 6, 1, 1);

    add_building ("rooftile.png", "rooftile.png", "rooftile.png", 600, 2, 60, point3f (1030, 0, -1140),
		  3, 0.05, 1);
    add_building ("rooftile.png", "rooftile.png", "rooftile.png", 2, 600, 60, point3f (1330, 0, -840),
		  0.05, 3, 1);
    
    add_building ("build1_s.png", "apartment.png", "build1_t.png", 200, 2400, 500, point3f (300, 0, -1750),
		  1, 4, 1);
    add_building ("build1_s.png", "derelic.png", "build1_t.png", 200, 500, 500, point3f (640, 0, -900));
}

void level_one::setup_lights ()
{
    gra::light_ptr lit (new gra::light);
    lit->enable ();
    lit->set_diffuse (base::point4f (1, 1, 1, 1));
    lit->set_ambient (base::point4f (0.3, 0.3, 0.3, 1));
    lit->set_specular (base::point4f (1, 1, 1, 1));

    get_scene ()->get_root ().get_child ("light").add_drawable (lit);
    get_scene ()->get_root ().get_child ("light").set_position (base::point3f (-1000, 1000, 1000));

    core::system::self ().graphic ().set_clear_color (
	get_scene ()->get_fog ()->get_color ());
}

void level_one::setup_people ()
{
    const play_area area = { -1700.0f, -1200.0f, 2400.0f, 600.0f };

    const int num_pedestrian_models = 7;
    const md2_id pedestrian_models [] =
	{ {"scarlet.md2", "scarlet_rwb.png", false},
	  {"scarlet.md2", "scarlet_dress_red.png", false},
	  {"scarlet.md2", "scarlet_dress_blue.png", false},
	  {"billgates.md2", "billgates.png", true},
	  {"dgirl.md2", "dgirl.png", true},
	  {"vicar.md2", "vicar.png", true},
	  {"faust.md2", "faust.png", true},
	};
    
    const int num_dealer_models = 5;
    const md2_id dealer_models [] =
	{ {"tigger.md2", "tigger.pcx", false},
	  {"oddjob.md2", "oddjob.png", true},
	  {"smiley.md2", "smiley.png", true},
	  {"bong.md2", "bong_gethigh.png", true},
	  {"bong.md2", "bong_weedies.png", true}
	};

    const int max_drug = 5;
    
    const int NUM_PEDESTRIANS = 30;
    const int NUM_DEALERS = 10;
    const int NUM_POLICEMAN = 5;

#if 1
    for (int i = 0; i < NUM_PEDESTRIANS; ++i)
	add_random_pedestrian (num_pedestrian_models, pedestrian_models, area);

    for (int i = 0; i < NUM_DEALERS; ++i)
	add_random_dealer (num_dealer_models, dealer_models, area, max_drug);

    for (int i = 0; i < NUM_POLICEMAN; ++i)
	add_random_policeman (area);
#endif
}

void level_one::init ()
{
    set_sky ("sky_mid_fog.png");

    setup_floor ();
    setup_buildings ();
    setup_lights ();
    setup_people ();

    finish_setup ();
}

level_one::level_one ()
{
    set_next_level ("hell");
}

std::string level_one::loading ()
{
    return "level_one.png";
}

} /* namespace st */
} /* namespace dose */
