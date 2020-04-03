/**
 *  Time-stamp:  <2009-05-24 12:06:00 raskolnikov>
 *
 *  @file        person_observer.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 24 11:30:31 2009
 *
 *  Implementación del patron observer para person.
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

#include "entity_observer.hpp"

namespace yage
{
namespace game
{

void entity_subject::add_listener (entity_listener& l)
{
    on_entity_move.connect (sigc::mem_fun (l, &entity_listener::handle_entity_move));
    on_entity_rotate.connect (sigc::mem_fun (l, &entity_listener::handle_entity_rotate));
}

void entity_subject::del_listener (entity_listener& l)
{
    remove_slot (on_entity_move, sigc::mem_fun (l, &entity_listener::handle_entity_move));
    remove_slot (on_entity_rotate, sigc::mem_fun (l, &entity_listener::handle_entity_rotate));
}

} /* namespace game */
} /* namespace yage */
