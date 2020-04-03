/**
 *  @file        hell.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Mon Jun 15 10:02:16 2009
 *
 *  Interfaz de la clase hell.
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

#ifndef DOSE_HELL_H_
#define DOSE_HELL_H_

#include <dose/st/level.hpp>

namespace dose
{
namespace st
{

class hell : public st::level
{
public:
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

#endif /* DOSE_HELL_H_ */
