/**
 *  Time-stamp:  <2009-06-12 12:59:39 raskolnikov>
 *
 *  @file        dope_factory.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 12:06:45 2009
 *
 *  Interfaz de la clase dope_factory.
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

#ifndef DOSE_DOPE_FACTORY_H_
#define DOSE_DOPE_FACTORY_H_

#include <string>
#include <yage/base/factory_manager.hpp>
#include <yage/base/singleton.hpp>

namespace dose
{
namespace drug
{

class dope;

class dope_factory_impl : yage::base::factory_manager<std::string, dope, boost::shared_ptr<dope> >
{
public:
    dope_factory_impl ();
    ptr_type create_random ();
};

typedef yage::base::singleton_holder<dope_factory_impl> dope_factory;

} /* namespace drug */
} /* namespace dose */

#endif /* DOSE_DOPE_FACTORY_H_ */
