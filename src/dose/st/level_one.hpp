/**
 *  Time-stamp:  <2009-06-15 12:33:51 raskolnikov>
 *
 *  @file        level_one.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 11:59:48 2009
 *
 *  Interfaz de la clase level_one.
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

#ifndef DOSE_LEVEL_ONE_H_
#define DOSE_LEVEL_ONE_H_

#include <yage/game/collidable.hpp>
#include <dose/st/level.hpp>

namespace dose
{
namespace st
{

class level_one : public level
{
public:
    level_one ();

    void init ();
    std::string loading ();
    
private:
    void setup_floor ();
    void setup_buildings ();
    void setup_lights ();
    void setup_people ();
};

} /* namespace st */
} /* namespace dose */

#endif /* DOSE_LEVEL_ONE_H_ */
