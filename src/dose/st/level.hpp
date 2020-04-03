/**
 *  @file        level.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 11:55:08 2009
 *
 *  Interfaz de la clase level.
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

#ifndef DOSE_LEVEL_H_
#define DOSE_LEVEL_H_

#include <yage/gra/camera.hpp>
#include <yage/game/state.hpp>
#include <yage/game/entity.hpp>
#include <yage/game/entity_manager.hpp>

#include <dose/ent/player_controller.hpp>
#include <dose/tool/fly_camera_controller.hpp>
#include <dose/tool/follow_camera_controller.hpp>

namespace dose
{

namespace ent
{
class person;
class dealer;
class player;
} /* namespace ent */

namespace st
{


class level : public yage::game::state
	    , public yage::core::key_listener
{
public:
    static const int STATIC_CAMERAS = 4;

    typedef boost::shared_ptr<ent::person> person_ptr;
    typedef boost::shared_ptr<ent::dealer> dealer_ptr;
    typedef boost::shared_ptr<ent::player> player_ptr;

    typedef std::list<dealer_ptr>::iterator dealer_iterator;

    level ();
    ~level ();

    bool handle_key_press (SDL_Event& event);
    bool handle_key_release (SDL_Event& event);

    yage::game::entity_manager_ptr entities ()
    {
	return m_entities;
    }

    player_ptr get_player ()
    {
	return m_player_ent;
    }

    ent::player_controller& get_player_controller ()
    {
	return m_player_ctl;
    }

    yage::gra::camera_ptr get_player_camera ()
    {
	return m_player_cam;
    }

    tool::follow_camera_controller& get_player_camera_controller ()
    {
	return m_player_cam_ctl;
    }

    dealer_iterator dealers_begin ()
    {
	return m_dealers.begin ();
    }

    dealer_iterator dealers_end ()
    {
	return m_dealers.end ();
    }

    void enable_finish ()
    {
	m_can_finish = true;
    }

    void set_next_level (const std::string& next)
    {
	m_next_level = next;
    }

protected:
    struct play_area
    {
	float min_x;
	float min_z;
	float max_x;
	float max_z;
    };

    struct md2_id
    {
	const char* tris;
	const char* tex;
	bool normals;
    };

    void add_floor (const std::string& tex,
		    float wide, float len, float angle,
		    float htile, float vtile,
		    const yage::base::point3f& pos);

    void add_object (const std::string& tris,
		     const std::string& tex,
		     yage::game::collidable col,
		     const yage::base::point3f& pos,
		     const yage::base::point3f& scale = yage::base::point3f (1, 1, 1));

    void add_building (const std::string& ftex,
		       const std::string& stex,
		       const std::string& ttex,
		       float wide, float deep, float high,
		       const yage::base::point3f& pos,
		       float tile_f = 1, float tile_s = 1, float tile_t = 1);
    void set_random_position (person_ptr p, const play_area& area);
    void add_random_pedestrian (int num_skins,
				const md2_id* skins,
				const play_area& area);
    void add_random_dealer (int num_skins,
			    const md2_id* skins,
			    const play_area& area,
			    int max_drugs);
    void add_random_policeman (const play_area& area);

    void add_entity (const std::string& name,
		     yage::game::entity_ptr ent);
    void add_dealer (const std::string& name,
		     dealer_ptr ent);
    void add_person (const std::string& name,
		     person_ptr ent);
    void add_static (yage::gra::drawable_ptr drawable);
    void set_sky (const std::string& str);
    void finish_setup ();

    yage::gra::scene_node& get_static ()
    {
	return m_static;
    }

private:
    void unset_camera ();

    yage::game::entity_manager_ptr m_entities;
    yage::gra::scene_node m_static;
    std::list<dealer_ptr> m_dealers;

    player_ptr m_player_ent;
    ent::player_controller m_player_ctl;

    yage::gra::camera_ptr m_player_cam;
    tool::follow_camera_controller m_player_cam_ctl;
    yage::gra::camera_ptr m_fly_cam;
    tool::fly_camera_controller_ptr m_fly_cam_ctl;
    yage::gra::camera_ptr m_static_cam [STATIC_CAMERAS];

    SDLKey m_old_cam;

    int m_unique_count;
    bool m_can_finish;
    std::string m_next_level;
};

typedef boost::shared_ptr<level> level_ptr;

} /* namespace st */
} /* namespace dose */

#endif /* DOSE_LEVEL_H_ */
