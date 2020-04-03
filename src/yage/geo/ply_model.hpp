/*
 *  File:       ply_model.hpp
 *  Author:     Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  Date:       Sun May 10 15:55:03 2009
 *
 *  Interfaz de los ficheros .ply
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

#ifndef YAGE_PLY_MODEL_H_
#define YAGE_PLY_MODEL_H_

#include <yage/geo/mesh.hpp>

namespace yage
{
namespace geo
{

YAGE_DECLARE_ERROR (base::yage_error, ply_model_error);

class ply_model : public mesh
{
public:
    ply_model (const std::string& fname);
};

} /* namespace geo */
} /* namespace yage */

#endif /* YAGE_PLY_MODEL_H_ */
