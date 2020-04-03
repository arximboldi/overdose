/**
 *  @file        multi_textured_cube.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 24 19:08:45 2009
 *
 *  Interfaz de multi_textured_cube.
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

#ifndef YAGE_MULTI_TEXTURED_CUBE_H_
#define YAGE_MULTI_TEXTURED_CUBE_H_

#include <yage/geo/multi_mesh.hpp>

namespace yage
{
namespace geo
{

class multi_textured_cube : public multi_mesh
{
public:
    multi_textured_cube (float tile_f = 1, float tile_s = 1, float tile_t = 1);

    void set_top_bottom (boost::shared_ptr<gra::texture> tex);
    void set_front_back (boost::shared_ptr<gra::texture> tex);
    void set_left_right (boost::shared_ptr<gra::texture> tex);
};

} /* namespace geo */
} /* namespace yageyagyayy */

#endif /* YAGE_MULTI_TEXTURED_CUBE_H_ */
