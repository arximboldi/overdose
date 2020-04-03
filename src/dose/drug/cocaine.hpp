/**
 *  Time-stamp:  <2009-06-13 16:48:23 raskolnikov>
 *
 *  @file        cocaine.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 11:51:51 2009
 *
 *  Interfaz de la clase cocaine.
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

#ifndef DOSE_COCAINE_H_
#define DOSE_COCAINE_H_

#include <dose/drug/dope.hpp>

namespace dose
{
namespace drug
{

class cocaine : public dope
{
public:
    cocaine ();
    
    void take ();
    void accumulate (dope_ptr dp);
    void handle_finish ();

private:
    float m_orig_walk_speed;
    float m_orig_rotate_speed;
};

} /* namespace drug */
} /* namespace dose */

#endif /* DOSE_COCAINE_H_ */
