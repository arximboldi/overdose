/**
 *  Time-stamp:  <2009-05-19 23:29:01 raskolnikov>
 *
 *  @file        graphic_controller.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Tue May 19 09:49:05 2009
 *
 *  Interfaz de la clase graphic_controller.
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

#ifndef YAGE_GRAPHIC_CONTROLLER_H_
#define YAGE_GRAPHIC_CONTROLLER_H_

#include <yage/base/observer.hpp>

namespace yage
{

namespace base
{
class conf_node;
}

namespace app
{

class graphic_controller : public sigc::trackable
{
public:
    graphic_controller (base::conf_node& config)
	: m_conf (config)
    {};
    
    void init (const std::string& wname);
    
private:
    void setup_defaults ();
    void setup_resources ();
    void install_signals ();
    
    void handle_fps_change (base::conf_node& conf);
    void handle_window_nudge (base::conf_node& conf);

    base::conf_node& m_conf;
};

} /* namespace app */
} /* namespace yage */

#endif /* YAGE_GRAPHIC_CONTROLLER_H_ */
