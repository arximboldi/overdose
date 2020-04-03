/**
 *  Time-stamp:  <2009-05-22 21:42:46 raskolnikov>
 *
 *  @file        game_app.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 16:21:19 2009
 *
 *  Interfaz de la clase game_app.
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

#ifndef YAGE_GAME_APP_H_
#define YAGE_GAME_APP_H_


#include <yage/core/task.hpp>
#include <yage/app/yage_app.hpp>
#include <yage/game/state_manager.hpp>

namespace yage
{
namespace app
{

class game_app : public yage_app
{
public:
    game_app (const std::string& name,
	      const std::string& version,
	      const std::string& description,
	      const std::string& copyright_date,
	      const std::string& author);

protected:
    virtual void register_states (boost::shared_ptr<game::state_manager> states) = 0;
    virtual std::string initial_state () = 0;
    
    int execute ();
    
private:
    void handle_state_manager_finish (game::state_manager&);
    
    boost::shared_ptr<game::state_manager> m_game_states;
};

} /* namespace app */
} /* namespace yage */

#endif /* YAGE_GAME_APP_H_ */
