/**
 *  Time-stamp:  <2009-05-22 12:29:17 raskolnikov>
 *
 *  @file        mouse_observer.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 12:19:01 2009
 *
 *  Implementación de clases del patrón observer para el ratón.
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

#include "mouse_observer.hpp"

namespace yage
{
namespace core
{

void mouse_subject::add_listener (mouse_listener& l)
{
    on_mouse_move.connect (sigc::mem_fun (l, &mouse_listener::handle_mouse_move));
    on_mouse_button_press.connect (sigc::mem_fun (l, &mouse_listener::handle_mouse_button_press));
    on_mouse_button_release.connect (sigc::mem_fun (l, &mouse_listener::handle_mouse_button_release));
}

void mouse_subject::del_listener (mouse_listener& l)
{
    remove_slot (on_mouse_move, sigc::mem_fun (l, &mouse_listener::handle_mouse_move));
    remove_slot (on_mouse_button_press, sigc::mem_fun (l, &mouse_listener::handle_mouse_button_press));
    remove_slot (on_mouse_button_release, sigc::mem_fun (l, &mouse_listener::handle_mouse_button_release));
}

} /* namespace core */
} /* namespace yage */
