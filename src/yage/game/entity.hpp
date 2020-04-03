/**
 *  @file        entity.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 12:14:37 2009
 *
 *  Declaracion de las entidades del sistema.
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

#ifndef YAGE_ENTITY_H_
#define YAGE_ENTITY_H_

#include <boost/weak_ptr.hpp>
#include <yage/core/task.hpp>
#include <yage/gra/scene_node.hpp>
#include <yage/game/entity_observer.hpp>
#include <yage/game/collidable.hpp>

namespace yage
{
namespace game
{

class entity_manager;
class dynamic_collision;

class entity : public core::task
	     , public entity_subject
{
public:
    entity (bool dynamic = false);
    virtual ~entity ();

    virtual void handle_collision (entity& other,
				   collidable& box,
				   dynamic_collision& col) = 0;
    virtual base::point3f get_orientation ();

    void apply_movement ();
    void move (const base::point3f& movement);
    void set_movement (const base::point3f& movement);

    bool has_moved ()
    {
	return m_moved;
    }

    bool is_dynamic () const
    {
	return m_dynamic;
    }

    void set_bounds (const collidable& bounds)
    {
	m_bounds = bounds;
    }

    const collidable& get_bounds () const
    {
	return m_bounds;
    }

    const base::point3f& get_movement () const
    {
	return m_movement;
    }

    gra::scene_node& get_node ()
    {
	return m_node;
    }

    const gra::scene_node& get_node () const
    {
	return m_node;
    }

    boost::shared_ptr<entity_manager> get_entity_parent ()
    {
	return boost::shared_ptr<entity_manager> (m_parent);
    }

    void set_entity_parent (boost::weak_ptr<entity_manager> parent)
    {
	m_parent = parent;
    }

private:
    boost::weak_ptr<entity_manager> m_parent;
    gra::scene_node m_node;

    base::point3f m_movement;
    collidable m_bounds;

    bool m_moved;
    bool m_dynamic;
};

typedef boost::shared_ptr<entity> entity_ptr;

} /* namespace game */
} /* namespace yage */

#endif /* YAGE_ENTITY_H_ */
