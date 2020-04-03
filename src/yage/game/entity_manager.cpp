/**
 *  @file        entity_manager.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 12:20:08 2009
 *
 *  Implementación del gestor de entidades.
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

#include <algorithm>

#include "yage/core/task_manager.hpp"

#include "dynamic_collision.hpp"
#include "static_collision.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"

using namespace std;

namespace yage
{
namespace game
{

entity_manager::~entity_manager ()
{
}

void entity_manager::add_entity (boost::shared_ptr<entity> ent)
{
    if (ent->is_dynamic ())
	m_dynamic.push_back (ent);
    else
	m_static.push_back (ent);

    ent->set_entity_parent (shared_from_this ());

    if (ent->is_dynamic ()) {
	try {
	    get_task_parent ()->add (ent);
	} catch (boost::bad_weak_ptr&) {}
    }
}

void entity_manager::clear ()
{
    m_dynamic.clear ();
    m_static.clear ();
}

void entity_manager::check_collision (entity& a, entity& b,
				      const base::point3f& move)
{
    dynamic_collision col;

    collidable
	ab = a.get_bounds (),
	bb = b.get_bounds ();

    translate_collidable (ab, a.get_node ().get_world_position ());
    translate_collidable (bb, b.get_node ().get_world_position ());

    if (col.test (ab, bb,  move))
    {
	a.handle_collision (b, ab, col);
	if (!a.has_moved () || !b.has_moved ())
	    b.handle_collision (a, bb, col);
    }
}

void entity_manager::find_collisions (entity_list& list, const collidable& who)
{
    typedef entity_list::iterator iterator;
    static_collision col;

    for (iterator iter = m_static.begin (); iter != m_static.end (); ++iter)
    {
	collidable other = (*iter)->get_bounds ();
	translate_collidable (other, (*iter)->get_node ().get_world_position ());
	if (col.test (who, other))
	    list.push_back (*iter);
    }
    for (iterator iter = m_dynamic.begin (); iter != m_dynamic.end (); ++iter)
    {
	collidable other = (*iter)->get_bounds ();
	translate_collidable (other, (*iter)->get_node ().get_world_position ());
	if (col.test (who, other))
	    list.push_back (*iter);
    }
}

bool entity_manager::find_collisions (const collidable& who)
{
    typedef entity_list::iterator iterator;
    static_collision col;

    for (iterator iter = m_static.begin (); iter != m_static.end (); ++iter)
    {
	collidable other = (*iter)->get_bounds ();
	translate_collidable (other, (*iter)->get_node ().get_world_position ());
	if (col.test (who, other))
	    return true;
    }
    for (iterator iter = m_dynamic.begin (); iter != m_dynamic.end (); ++iter)
    {
	collidable other = (*iter)->get_bounds ();
	translate_collidable (other, (*iter)->get_node ().get_world_position ());
	if (col.test (who, other))
	    return true;
    }

    return false;
}

bool
entity_manager::find_dynamic_static_collisions (const collidable& who,
						const base::point3f& move)
{
    typedef entity_list::iterator iterator;

    for (iterator iter = m_static.begin (); iter != m_static.end (); ++iter)
    {
	dynamic_collision col;
	collidable other = (*iter)->get_bounds ();
	translate_collidable (other, (*iter)->get_node ().get_world_position ());
	if (col.test (who, other, move))
	    return true;
    }

    return false;
}

void entity_manager::update (int delta_ticks)
{
    typedef base::ptr_iterator<entity_list::iterator> iterator;

    /* Borrar las entidades que tengan que morir. */
    for (iterator iter = m_static.begin (); iter != m_static.end ();)
	if (iter->is_finished ()) m_static.erase (iter++);
	else ++iter;
    for (iterator iter = m_dynamic.begin (); iter != m_dynamic.end ();)
	if (iter->is_finished ()) m_dynamic.erase (iter++);
	else ++iter;

    /* Comprobar las colisiones. */
    for (iterator iter_a = m_dynamic.begin (); iter_a != m_dynamic.end (); ++iter_a)
    {
	if (iter_a->has_moved ()) {
	    for (iterator iter_b = m_dynamic.begin (); iter_b != m_dynamic.end (); ++iter_b)
		if (iter_a != iter_b)
		    check_collision (*iter_a, *iter_b,
				     iter_a->get_movement () - iter_b->get_movement ());
	    for (iterator iter_b = m_static.begin (); iter_b != m_static.end (); ++iter_b)
		check_collision (*iter_a, *iter_b, iter_a->get_movement ());
	}
    }

    /* Actualizar todas las entidades */
    for (iterator iter = m_dynamic.begin (); iter != m_dynamic.end (); ++iter)
	iter->apply_movement ();
}

} /* namespace game */
} /* namespace yage */
