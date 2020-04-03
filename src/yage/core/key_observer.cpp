/**
 *  @file        key_observer.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 12:17:38 2009
 *
 *  Implementación de clases del patrón observer para el teclado.
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

#include "key_observer.hpp"

namespace yage
{
namespace core
{

void key_subject::add_listener (key_listener& l)
{
    on_key_press.connect (sigc::mem_fun (l, &key_listener::handle_key_press));
    on_key_release.connect (sigc::mem_fun (l, &key_listener::handle_key_release));
}

void key_subject::del_listener (key_listener& l)
{
    remove_slot (on_key_press, sigc::mem_fun (l, &key_listener::handle_key_press));
    remove_slot (on_key_release, sigc::mem_fun (l, &key_listener::handle_key_release));
}

} /* namespace core */
} /* namespace yage */
