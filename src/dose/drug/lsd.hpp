/**
 *  @file        lsd.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 11:55:47 2009
 *
 *  Interfaz de la clase lsd.
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

#ifndef DOSE_LSD_H_
#define DOSE_LSD_H_

#include <yage/base/point4.hpp>
#include <dose/drug/dope.hpp>

namespace dose
{
namespace drug
{

class lsd : public dope
{
public:
    lsd ();

    void take ();
    void accumulate (dope_ptr dp);
    void handle_finish ();

private:
    void randomize_models ();
    void restore_models ();

    yage::base::point4f m_orig_fog_color;
};

} /* namespace drug */
} /* namespace dose */

#endif /* DOSE_LSD_H_ */
