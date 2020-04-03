/**
 *  Time-stamp:  <2009-05-22 12:03:02 raskolnikov>
 *
 *  @file        exception.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 12:00:54 2009
 *
 *  Declaración de las excepciones base de la aplicación.
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

#ifndef DOSE_EXCEPTION_H_
#define DOSE_EXCEPTION_H_

#include <yage/base/exception.hpp>

namespace dose
{

YAGE_DECLARE_ERROR (yage::base::error, overdose_error);

} /* namespace dose */

#endif /* DOSE_EXCEPTION_H_ */
