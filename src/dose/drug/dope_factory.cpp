/**
 *  Time-stamp:  <2009-06-13 20:04:38 raskolnikov>
 *
 *  @file        dope_factory.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 12:09:43 2009
 *
 *  Implementación de la clase dope_factory.
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

#include <yage/base/misc.hpp>

#include "marihuana.hpp"
#include "cocaine.hpp"
#include "lsd.hpp"
#include "alcohol.hpp"
#include "adrenaline.hpp"

#include "dope_factory.hpp"

using namespace yage;

namespace dose
{
namespace drug
{

dope_factory_impl::dope_factory_impl ()
{
    add<cocaine> ("cocaine");
    add<marihuana> ("marihuana");
    add<lsd> ("lsd");
    add<alcohol> ("alcohol");
    add<adrenaline> ("adrenaline");
}

dope_factory_impl::ptr_type
dope_factory_impl::create_random ()
{
    int index = base::ranged_random<int> (0, size ());

    iterator it;
    for (it = begin (); it != end () && index > 0; ++it, --index);
    
    if (it == end ())
	throw base::factory_error ("Error in dope_factory_impl::create_random ()");

    return create (*it);
}

} /* namespace drug */
} /* namespace dose */
