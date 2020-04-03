/**
 *  @file        overdose.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Mon May 18 18:57:29 2009
 *
 *  Interfaz de la clase overdose.
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

#include <yage/app/game_app.hpp>

namespace dose
{

class overdose : public yage::app::game_app
{
public:
    static float s_dope_level;

    overdose ();

    void prepare (yage::base::arg_parser& args);
    void register_states (boost::shared_ptr<yage::game::state_manager> mgr);
    std::string initial_state ();
    void print_help (std::ostream& out);

private:
    std::string m_initial_state;
};

} /* namespace odose */
