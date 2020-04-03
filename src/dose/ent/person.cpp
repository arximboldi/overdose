/**
 *  Time-stamp:  <2009-06-15 22:41:18 raskolnikov>
 *
 *  @file        person.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sat May 23 14:36:08 2009
 *
 *  Implementación de la clase person.
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

#include <cmath>
#include <yage/base/misc.hpp>
#include <yage/core/system.hpp>
#include <yage/core/task_manager.hpp>
#include <yage/gra/animation_task.hpp>
#include <yage/game/collidable.hpp>
#include <yage/game/collision_util.hpp>
#include <yage/game/dynamic_collision.hpp>

#include "person.hpp"

using namespace yage;
using namespace yage::base;
using namespace boost;

namespace dose
{
namespace ent
{

geo::md2_model_ptr
person::load_model (const std::string& tris,
		    const std::string& tex,
		    bool inverse_normals)
{
    core::graphic_system& graph = core::system::self ().graphic ();

    geo::md2_model_impl_ptr impl =
	dynamic_pointer_cast<geo::md2_model_impl> (graph.geometries ().find (tris)); 
    impl->set_inverse_normals (inverse_normals);

    geo::md2_model_ptr model (new geo::md2_model (impl));
    model->set_texture (graph.textures ().find (tex));
    
    try {
	model->set_material (graph.materials ().find ("person"));
    } catch (base::yage_error& err) {
	gra::material_ptr mat (
	    new gra::material (base::point4f (0.6, 0.6, 0.6, 1),
			       base::point4f (0.7, 0.7, 0.7, 1),
			       base::point4f (1, 1, 1, 1)));
	model->set_material (mat);
	graph.materials ().add ("person", mat);
    }

    return model;
}

person::person (const std::string& model,
		const std::string& texture,
		bool inverse_normals,
		float walk_speed,
		float rotate_speed)
    : game::entity (true)
    , m_walk_speed (walk_speed)
    , m_rotate_speed (rotate_speed)
    , m_wait (false)
    , m_dir (1, 0, 0)
    , m_angle (0)
    , m_action (0)
{
    m_real_model = m_model = load_model (model, texture, inverse_normals);
    
    gra::scene_node& node = get_node ().get_child ("model"); 
    node.add_drawable (m_model);
    node.set_position (get_node ().get_position () +
		       base::point3f (0, 25, 0)); 
    
#if 0
    std::cout << "-- " << model << "--------------\n";
    std::copy (m_model->get_impl ()->anims_begin (),
	       m_model->get_impl ()->anims_end (),
	       std::ostream_iterator<std::string> (std::cout, "\n"));
#endif

    game::capsule bbox;
    bbox.rad = 10;
    bbox.p1  = base::point3f (0, 10, 0);
    bbox.p2  = base::point3f (0, 60, 0);
    set_bounds (bbox);
}

person::~person ()
{
    if (!m_anim.expired ())
	get_animation_task ()->finish ();
}

void person::jump ()
{
    /* TODO */
}

void person::activate_action (int action)
{
    toggle_action (~m_action & action);
}

void person::deactivate_action (int action)
{
    toggle_action (m_action & action);
}

void person::set_action (int action)
{
    toggle_action (m_action);
    toggle_action (action);
}

void person::toggle_action (int action)
{
    m_action ^= action;
    if (m_action & (RUN_FW | RUN_BW | RUN_L | RUN_R))
	set_animation ("run");
    else {
	set_animation ("stand");
    }
}

void person::play (const std::string& anim, float speed)
{
    set_animation (anim, speed, true);
    get_animation_task ()->set_loop (false);
}

void person::update (int delta)
{
    const float DEG = 180.0f / M_PI;

    if (m_model->get_animation () == "run") {
	if (m_action & RUN_FW)
	    move (m_dir * delta * m_walk_speed);
	if (m_action & RUN_BW)
	    move ((base::point3f () - m_dir) * delta * m_walk_speed);
	if (m_action & RUN_L)
	    move (m_dir.normal (base::point3f (0, 1, 0)) * delta * m_walk_speed);
	if (m_action & RUN_R)
	    move (base::point3f () - m_dir.normal (base::point3f (0, 1, 0)) * delta * m_walk_speed);
    }
    
    if (m_action & ROTATE_L) {
	m_angle -= delta * m_rotate_speed;
	get_node ().set_rotate (base::point4f (-m_angle * DEG, 0, 1, 0));
	m_dir = base::point3f (std::cos (m_angle), 0, std::sin (m_angle));
    }
    if (m_action & ROTATE_R) {
	m_angle += delta * m_rotate_speed;
	get_node ().set_rotate (base::point4f (-m_angle * DEG, 0, 1, 0));
	m_dir = base::point3f (std::cos (m_angle), 0, std::sin (m_angle));
    }

    if (m_action & (ROTATE_L | ROTATE_R))
	on_entity_rotate (*this);

    if (m_anim.expired ())
	set_animation ("stand");
}

void person::set_look_angle (float angle)
{
    const float DEG = 180.0 / M_PI;

    m_angle = angle;
    get_node ().set_rotate (base::point4f (-m_angle * DEG, 0, 1, 0));
    m_dir = base::point3f (std::cos (m_angle), 0, std::sin (m_angle));    
}

void person::handle_collision (yage::game::entity& ent,
			       yage::game::collidable& bounds,
			       yage::game::dynamic_collision& col)
{
    const float NEAR_ONE = 0.999;
    
    point3f dest_col = get_movement () * col.get_time () * NEAR_ONE;
    point3f perp = col.get_normal ().cross (point3f (0, 1, 0)).normalize ();

    float dist = game::sq_dist_point_line (dest_col, dest_col + perp, get_movement ());
    
    move (col.get_normal () * std::sqrt (dist));
}

bool person::is_blocked ()
{
    if (m_anim.expired () || get_animation_task ()->get_loop ())
	return false;

    return true;
}

void person::set_animation (const std::string& anim, float speed, bool force)
{
    if (m_anim.expired () || get_animation_task ()->is_finished ())
    {
	gra::animation_task_ptr t (new gra::animation_task (m_model));
	t->set_loop (true);
	m_anim = t;
	get_task_parent ()->add (t);
    }
    
    if (force ||
	(get_animation_task ()->get_loop () &&
	 m_model->get_animation () != anim)) {
	m_model->set_animation (anim);
	get_animation_task ()->seek (0);
	get_animation_task ()->set_speed (speed);
    }
}

void person::finish_animation ()
{
    if (!m_anim.expired ()) {
	gra::animation_task_ptr anim (m_anim);
	anim->finish ();
    }
}

void person::alternate_model (geo::md2_model_ptr m)
{
    m->set_animation (m_model->get_animation ());
    if (!m_anim.expired ())
	get_animation_task ()->set_animation (m);
    
    m_model = m;

    gra::scene_node& node = get_node ().get_child ("model");
    node.clear_drawables ();
    node.add_drawable (m);
}

void person::restore_model ()
{
    alternate_model (m_real_model);
}

} /* namespace ent */
} /* namespace dose */
