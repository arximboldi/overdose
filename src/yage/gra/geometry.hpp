/**
 *  Time-stamp:  <2009-06-15 09:46:30 raskolnikov>
 *
 *  @file        geometry.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Wed May 20 12:58:40 2009
 *
 *  Interfaz geometry.
 *
 *  @todo Esta es una primera generalización cutre entre todas las
 *        clases que representan superficies. Deberíamos
 *        buscar generalizar geo::mesh y añadir comportamiento.
 *
 *  @todo Esto no debería heredar de animation, pero nos facilita
 *        la vida a la hora de manejar homogeneamente los
 *        recursos con geometry_manager.
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

#include <boost/shared_ptr.hpp>
#include <yage/gra/drawable.hpp>

#ifndef YAGE_GEOMETRY_H_
#define YAGE_GEOMETRY_H_

namespace yage
{
namespace gra
{

class material;
class texture;

class geometry : public drawable
{
public:
    virtual void draw_raw () = 0;
    virtual void set_material (boost::shared_ptr<material>) = 0;
    virtual void set_texture (boost::shared_ptr<texture>) = 0;
};

typedef boost::shared_ptr<geometry> geometry_ptr;

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_GEOMETRY_H_ */
