/**
 *  Time-stamp:  <2009-06-15 23:47:40 raskolnikov>
 *
 *  @file        graphic_controller.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Tue May 19 09:54:35 2009
 *
 *  Implementación de la clase graphic_controller.
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

#include "yage/core/system.hpp"
#include "yage/base/config.hpp"
#include "graphic_controller.hpp"

namespace yage
{
namespace app
{

void graphic_controller::init (const std::string& wname)
{
    setup_defaults ();
    install_signals ();

    int sc_width  = m_conf.get_path ("window.width").get<int> ();
    int sc_height = m_conf.get_path ("window.height").get<int> ();
    int sc_fullsc = m_conf.get_path ("window.fullscreen").get<int> ();
    int sc_grab   = m_conf.get_path ("window.grab").get<int> ();
    int fps       = m_conf.get_path ("fps").get<int> ();
    
    core::system::self ().graphic (). init (
	wname, sc_width, sc_height, sc_fullsc, sc_grab);
    core::system::self ().force_fps (fps);

    setup_resources ();
}

void graphic_controller::setup_resources ()
{
    core::graphic_system& graphic = core::system::self ().graphic ();
    base::file_mgr_node* file_mgr = &base::file_manager::self ().get_child ("yage");

    graphic.textures ().set_file_manager (file_mgr);
    graphic.geometries ().set_file_manager (file_mgr);
    graphic.fonts ().set_file_manager (file_mgr);
}

void graphic_controller::setup_defaults ()
{
    m_conf.get_path ("window.width").def (int (800));
    m_conf.get_path ("window.height").def (int (600));
    m_conf.get_path ("window.fullscreen").def (int (0));
    m_conf.get_path ("window.grab").def (int (0));
    m_conf.get_path ("fps").def (int (60));
}

void graphic_controller::install_signals ()
{
    m_conf.get_child ("window").on_nudge.connect (
	sigc::mem_fun (this, &graphic_controller::handle_window_nudge));
    m_conf.get_child ("fps").on_change.connect (
	sigc::mem_fun (this, &graphic_controller::handle_fps_change));
}

void graphic_controller::handle_fps_change (base::conf_node& conf)
{
    int fps = conf.get<int> ();

    core::system::self ().force_fps (fps);
}

void graphic_controller::handle_window_nudge (base::conf_node& conf)
{
    int sc_width  = conf.get_child ("width").get<int> ();
    int sc_height = conf.get_child ("height").get<int> ();
    int sc_fullsc = conf.get_child ("fullscreen").get<int> ();
    int sc_grab   = conf.get_child ("grab").get<int> ();
    
    core::system::self ().graphic ().resize_window (sc_width, sc_height, sc_fullsc, sc_grab);
}

} /* namespace app */
} /* namespace yage */
