/**
 *  Time-stamp:  <2009-06-13 19:05:21 raskolnikov>
 *
 *  @file        marihuana.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 11:45:35 2009
 *
 *  Interfaz de la clase marihuana.
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

#ifndef DOSE_MARIHUANA_H_
#define DOSE_MARIHUANA_H_

#include <dose/drug/dope.hpp>

namespace dose
{
namespace drug
{

class bubbly_camera;

class marihuana : public dope
{
public:
    typedef boost::shared_ptr<bubbly_camera> bubbly_camera_ptr;

    marihuana ();
    void take ();
    void accumulate (dope_ptr dp);
    void handle_finish ();

private:
    bubbly_camera_ptr m_camfx;
};

} /* namespace drug */
} /* namespace dose */

#endif /* DOSE_MARIHUANA_H_ */
