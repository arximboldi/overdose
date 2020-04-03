/**
 *  Time-stamp:  <2009-06-13 19:42:09 raskolnikov>
 *
 *  @file        adrenaline.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sat Jun 13 19:39:09 2009
 *
 *  Interfaz de la clase adrenaline.
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

#ifndef DOSE_ADRENALINE_H_
#define DOSE_ADRENALINE_H_

#include <dose/drug/dope.hpp>

namespace dose
{
namespace drug
{

class adrenaline : public dope
{
public:
    adrenaline ();
    
    void take ();
    void accumulate (dope_ptr p);
    void handle_finish ();
};

} /* namespace drug */
} /* namespace dose */

#endif /* DOSE_ADRENALINE_H_ */
