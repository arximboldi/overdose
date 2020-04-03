/**
 *  @file        entity.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 12:16:44 2009
 *
 *  Implementación de las entidades.
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

#include <iostream>
#include "entity.hpp"

namespace yage
{
namespace game
{

entity::entity (bool dynamic)
    : m_moved (false)
    , m_dynamic (dynamic)
{
}

entity::~entity ()
{
    if (m_node.get_parent ())
	m_node.get_parent ()->detach (m_node.get_name ());
}

base::point3f entity::get_orientation ()
{
    return base::point3f (1, 0, 0);
}

void entity:: move (const base::point3f& movement)
{
    m_movement = m_movement + movement;
    m_moved = true;
}

void entity::set_movement (const base::point3f& movement)
{
    m_movement = movement;
    m_moved = true;
}

void entity::apply_movement ()
{
    if (m_moved) {
	m_node.set_position (m_node.get_position () + m_movement);
	on_entity_move (*this);
	m_movement = base::point3f ();
	m_moved = false;
    }
}

} /* namespace game */
} /* namespace yage */
