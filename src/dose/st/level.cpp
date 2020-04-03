/**
 *  Time-stamp:  <2020-04-03 15:56:47 raskolnikov>
 *
 *  @file        level.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 11:58:33 2009
 *
 *  Implementación de la clase level.
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

#include <boost/lexical_cast.hpp>

#include <yage/core/system.hpp>

#include <yage/gra/scene.hpp>
#include <yage/gra/static_drawable.hpp>
#include <yage/gra/fog.hpp>

#include <yage/geo/textured_hemisphere.hpp>
#include <yage/geo/textured_plane.hpp>

#include <yage/game/entity.hpp>

#include "dose/ent/player.hpp"
#include "dose/ent/pedestrian.hpp"
#include "dose/ent/dealer.hpp"
#include "dose/ent/policeman.hpp"
#include "dose/ent/building.hpp"
#include "dose/ent/empty.hpp"

#include "dose/drug/dope_factory.hpp"

#include <yage/geo/cylinder.hpp>
#include <yage/geo/sphere.hpp>

#include "level.hpp"

using namespace yage;
using namespace yage::base;

namespace dose
{
namespace st
{

level::level ()
    : m_entities (new game::entity_manager)
    , m_player_ent (new ent::player ("civi.md2", "civi.tga"))
    , m_player_ctl (m_player_ent)
    , m_player_cam (new gra::camera)
    , m_player_cam_ctl (m_player_cam, m_player_ent)
    , m_fly_cam (new gra::camera)
    , m_fly_cam_ctl (new tool::fly_camera_controller (m_fly_cam))
    , m_unique_count (0)
    , m_can_finish (false)
{
    get_keys ().add_listener (*this);

    get_tasks ().add (m_entities);

    add_entity ("player", m_player_ent);
    get_scene ()->get_hud_root ().attach ("player_hud", m_player_ent->get_hud ().get_node ());

    get_scene ()->set_camera (m_player_cam);
    get_keys ().add_listener (m_player_ctl);
    get_mouse ().add_listener (m_player_cam_ctl);

    m_fly_cam->set_position (base::point3f (-100, 1000, 0));
    m_fly_cam->look_at (base::point3f (0, 0, 0));

    const float static_cam_pos [STATIC_CAMERAS][3] =
	{{1000, 1000, 1000},
	 {-1000, 1000, 1000},
	 {-1000, 1000, -1000},
	 {1000, 1000, -1000}};

    for (int i = 0; i < STATIC_CAMERAS; ++i) {
	m_static_cam [i].reset (new gra::camera);
	m_static_cam [i]->set_position (base::point3f (static_cam_pos [i]));
	m_static_cam [i]->look_at (base::point3f (0, 0, 0));
    }

    m_old_cam = SDLK_F1;

    /* Niebla por defecto */
    const float DEFAULT_FOG = 0.0005;
    gra::fog_ptr fog (new gra::fog);
    fog->set_mode (gra::fog::EXP2);
    fog->set_density (DEFAULT_FOG);
    fog->set_color (point4f (0.5, 0.5, 0.5, 1));
    get_scene ()->set_fog (fog);

#if 1
    get_scene ()->get_root ().get_child ("modelillo").set_scale (point3f (100, 100, 100));
#endif
}

level::~level ()
{
    /* Evitamos que las entidades sigan vivas cuando muera la escena asociada al estado. */
    m_entities->clear ();
    get_tasks ().clear ();
}

void level::unset_camera ()
{
    if (m_old_cam == SDLK_F1) {
	m_player_cam_ctl.core::mouse_listener::disconnect_all ();
    } else if (m_old_cam == SDLK_F2) {
	m_fly_cam_ctl->core::mouse_listener::disconnect_all ();
	m_fly_cam_ctl->core::key_listener::disconnect_all ();
	get_tasks ().del (m_fly_cam_ctl);
    } else if (m_old_cam >= SDLK_F3 &&
	       m_old_cam < SDLK_F3 + STATIC_CAMERAS) {
    }
}

bool level::handle_key_press (SDL_Event& ev)
{
    SDLKey key = ev.key.keysym.sym;

    if (key == SDLK_ESCAPE)
	leave_state ();
    if (key == SDLK_RETURN && m_can_finish)
	if (!m_next_level.empty ())
	    change_state (m_next_level);
	else
	    leave_state ();
#if 1
    else if (key == SDLK_F12)
	core::system::self ().graphic ().set_polygon_mode (core::graphic_system::LINE);
    else if (key == SDLK_F11)
	core::system::self ().graphic ().set_polygon_mode (core::graphic_system::POINT);
    else if (key == SDLK_F10)
    	core::system::self ().graphic ().set_polygon_mode (core::graphic_system::FILL);
    else if (key == SDLK_F9)
	core::system::self ().graphic ().set_shading_mode (core::graphic_system::FLAT);
    else if (key == SDLK_F8)
	core::system::self ().graphic ().set_shading_mode (core::graphic_system::SMOOTH);
    else if (key == SDLK_F7) {
	get_scene ()->get_root ().get_child ("modelillo").clear_drawables ();
	get_scene ()->get_root ().get_child ("modelillo").add_drawable (gra::drawable_ptr (new geo::cylinder));
    }
    else if (key == SDLK_F6) {
	get_scene ()->get_root ().get_child ("modelillo").clear_drawables ();
	get_scene ()->get_root ().get_child ("modelillo").add_drawable (gra::drawable_ptr (new geo::sphere));
    }
    else if (key == SDLK_F5) {
	get_scene ()->get_root ().get_child ("modelillo").clear_drawables ();
    }
#endif
    else if (key == SDLK_F1) {
	unset_camera ();
	get_scene ()->set_camera (m_player_cam);
	get_mouse ().add_listener (m_player_cam_ctl);
	m_old_cam = ev.key.keysym.sym;
    } else if (key == SDLK_F2) {
	unset_camera ();
	get_scene ()->set_camera (m_fly_cam);
	get_keys ().add_listener (*m_fly_cam_ctl);
	get_mouse ().add_listener (*m_fly_cam_ctl);
	get_tasks ().add (m_fly_cam_ctl);
	m_old_cam = ev.key.keysym.sym;
    } else if (key >= SDLK_F3 &&
	       key < SDLK_F3 + STATIC_CAMERAS) {
	unset_camera ();
	get_scene ()->set_camera (m_static_cam [ev.key.keysym.sym - SDLK_F3]);
	m_old_cam = ev.key.keysym.sym;
    }

    return false;
}

bool level::handle_key_release (SDL_Event& event)
{
    return false;
}

void level::add_entity (const std::string& name,
			boost::shared_ptr<yage::game::entity> ent)
{
    get_scene ()->get_root ().attach (name, ent->get_node ());
    m_entities->add_entity (ent);
}

void level::add_dealer (const std::string& name, dealer_ptr ent)
{
    add_entity (name, ent);
    m_dealers.push_back (ent);
    ent->set_level (boost::dynamic_pointer_cast<level> (shared_from_this ()));
}


void level::add_person (const std::string& name, person_ptr ent)
{
    add_entity (name, ent);
    ent->set_level (boost::dynamic_pointer_cast<level> (shared_from_this ()));
}

void level::add_static (boost::shared_ptr<gra::drawable> draw)
{
    m_static.add_drawable (draw);
}

void level::finish_setup ()
{
    boost::shared_ptr<gra::static_drawable> sd (new gra::static_drawable (m_static));
    get_scene ()->get_root ().get_child ("static").add_drawable (sd);
    m_static.clear_childs ();
    m_player_cam_ctl.recalculate ();
    m_player_ent->set_level (boost::dynamic_pointer_cast<level> (shared_from_this ()));
}

void level::set_random_position (person_ptr p, const play_area& area)
{
    game::sphere box;
    box.rad = 20;

    while (true) {
	box.center = base::point3f (base::ranged_random (area.min_x, area.max_x), 0,
				    base::ranged_random (area.min_z, area.max_z));
	if (!entities ()->find_collisions (game::collidable (box)))
	    break;
    }

    p->get_node ().set_position (p->get_node ().get_position () + box.center);
    p->set_look_angle (base::ranged_random<float> (0.0, 2 * M_PI));
}

void level::add_random_pedestrian (int num_models,
				   const md2_id* models,
				   const play_area& area)
{
    int model = base::ranged_random (0, num_models);
    ent::person_ptr p (new ent::pedestrian (
			   models[model].tris, models[model].tex, models[model].normals,
			   base::ranged_random (0.05, 0.25),
			   base::ranged_random (0.001, 0.005)));
    set_random_position (p, area);

    add_entity (std::string ("pedestrian_") +
		boost::lexical_cast<std::string> (m_unique_count), p);
    m_unique_count ++;
}

void level::add_random_dealer (int num_models,
			       const md2_id* models,
			       const play_area& area,
			       int max_drugs)
{
    int model = base::ranged_random (0, num_models);
    ent::dealer_ptr p (new ent::dealer (
			   models[model].tris, models[model].tex, models[model].normals,
			   base::ranged_random (0.05, 0.25),
			   base::ranged_random (0.001, 0.005)));
    set_random_position (p, area);

    add_dealer (std::string ("pedestrian_") +
		boost::lexical_cast<std::string> (m_unique_count), p);
    m_unique_count ++;

    int drugs = base::ranged_random (1, max_drugs);
    while (drugs--)
	p->add_drug (drug::dope_factory::self ().create_random ());
}

void level::add_random_policeman (const play_area& area)
{
    ent::policeman_ptr p (new ent::policeman ());
    set_random_position (p, area);
    add_person (std::string ("policeman_") +
		boost::lexical_cast<std::string> (m_unique_count), p);
    m_unique_count ++;
}

void level::set_sky (const std::string& tex)
{
    core::graphic_system& graphic = core::system::self ().graphic ();

    boost::shared_ptr<geo::mesh> sky (new geo::textured_hemisphere);
    sky->set_texture (graphic.textures().find (tex));
    get_scene ()->set_sky (sky);
}


void level::add_floor (const std::string& tex,
			   float wide, float len, float angle,
			   float htile, float vtile,
			   const yage::base::point3f& pos)
{
    core::graphic_system& graphic = core::system::self ().graphic ();

    gra::geometry_ptr road (new geo::textured_plane (htile, vtile));
    road->set_material (boost::shared_ptr<gra::material> (new gra::material ()));
    road->set_texture (graphic.textures ().find (tex));

    gra::scene_node_ptr node (new gra::scene_node);
    node->get_child ("road").add_drawable (road);
    node->get_child ("road").set_rotate (point4f (90, 0, 0, 1));
    node->set_rotate (point4f (angle, 0, 1, 0));
    node->set_scale (base::point3f (wide, 10, len));
    node->set_position (pos);

    add_static (node);
}

void level::add_building (const std::string& ftex,
			      const std::string& stex,
			      const std::string& ttex,
			      float wide, float deep, float high,
			      const yage::base::point3f& pos,
			      float tile_f, float tile_s, float tile_t)
{
    boost::shared_ptr<ent::building> build (
	new ent::building (wide, deep, high, ftex, stex, ttex, tile_f, tile_s, tile_t));
    build->get_node ().set_position (pos);
    entities ()->add_entity (build);

    std::string objname = std::string ("building_") +
	boost::lexical_cast<std::string> (m_unique_count++);
    gra::scene_node& node = get_static ().get_child (objname);
    gra::scene_node& dra_node = node.get_child ("dra");
    gra::scene_node& ent_node = build->get_node ().get_child ("building");

    dra_node.add_drawable (ent_node.drawable_begin (), ent_node.drawable_end());
    dra_node.set_position (ent_node.get_position ());
    dra_node.set_scale (ent_node.get_scale ());
    node.set_position (pos);
}

void level::add_object (const std::string& tris,
			const std::string& tex,
			yage::game::collidable col,
			const yage::base::point3f& pos,
			const yage::base::point3f& scale)
{
    /* todo: add_static_entity () ?? */
    std::string objname = std::string ("object_") +
	boost::lexical_cast<std::string> (m_unique_count++);
    gra::scene_node& node = get_static ().get_child (objname);

    node.add_drawable (ent::person::load_model (tris, tex, true));
    node.set_position (pos);
    node.set_scale (scale);

    game::entity_ptr ent (new ent::empty);
    ent->set_bounds (col);
    ent->get_node ().set_position (pos);
    entities ()->add_entity (ent);
}

} /* namespace st */
} /* namespace dose */
