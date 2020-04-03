/**
 *  Time-stamp:  <2009-05-22 12:02:25 raskolnikov>
 *
 *  @file        exception.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 12:01:28 2009
 *
 *  Implementación de las excepciones base de la aplicación.
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

#include "exception.hpp"

namespace dose
{

YAGE_DEFINE_ERROR_WHERE_WHAT (overdose_error, "overdose",
			      "Unknown overdose error");

} /* namespace dose */
