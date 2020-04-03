/**
 *  Time-stamp:  <2009-06-10 19:41:13 raskolnikov>
 *
 *  @file        building.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 12:04:36 2009
 *
 *  Implementación de la clase building.
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

#include <yage/core/system.hpp>
#include <yage/geo/multi_textured_cube.hpp>

#include "building.hpp"

using namespace yage;

namespace dose
{
namespace ent
{


building::building (float wide,
		    float deep,
		    float high,
		    const std::string& f_tex,
		    const std::string& s_tex,
		    const std::string& t_tex,
		    float tile_f,
		    float tile_s,
		    float tile_t)
{
    core::graphic_system& graphic = core::system::self ().graphic ();
    
    boost::shared_ptr<geo::multi_textured_cube> model (
	new geo::multi_textured_cube (tile_f, tile_s, tile_t));
    model->set_front_back (graphic.textures ().find (f_tex));
    model->set_left_right (graphic.textures ().find (s_tex));
    model->set_top_bottom (graphic.textures ().find (t_tex));

    gra::scene_node& node = get_node ().get_child ("building");
    node.set_scale (base::point3f (deep, high, wide));
    node.set_position (base::point3f (0, high/2, 0));
    node.add_drawable (model);
    
    game::aabb bbox;
    bbox.min = base::point3f (-deep/2, 0, -wide/2);
    bbox.max = base::point3f ( deep/2, high,  wide/2);
    set_bounds (bbox);
}

void building::handle_collision (entity& col, game::collidable& box,
				 game::dynamic_collision& delta)
{
}

void building::update (int delta)
{
}

} /* namespace ent */
} /* namespace dose */
