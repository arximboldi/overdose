/**
 *  @file        multi_textured_cube.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 24 19:17:28 2009
 *
 *  Implementación de multi_textured_cube.
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

#include "multi_textured_cube.hpp"

using namespace yage::base;

namespace yage
{
namespace geo
{

multi_textured_cube::multi_textured_cube (float tile_f, float tile_s, float tile_t)
{
    const float l = 0.5;

    begin (mesh::QUADS);
    tex_coord (point2f (0, 1));
    point (point3f (-l, -l,  l));
    tex_coord (point2f (tile_s, 1));
    point (point3f ( l, -l,  l));
    tex_coord (point2f (tile_s, 0));
    point (point3f ( l,  l,  l));
    tex_coord (point2f (0, 0));
    point (point3f (-l,  l,  l));
    end ();

    begin (mesh::QUADS);
    tex_coord (point2f (0, 1));
    point (point3f (l, -l, -l));
    tex_coord (point2f (0, 0));
    point (point3f (l,  l, -l));
    tex_coord (point2f (tile_f, 0));
    point (point3f (l,  l,  l));
    tex_coord (point2f (tile_f, 1));
    point (point3f (l, -l,  l));
    end ();

    begin (mesh::QUADS);
    tex_coord (point2f (0, 1));
    point (point3f (-l, -l, -l));
    tex_coord (point2f (tile_s, 1));
    point (point3f ( l, -l, -l));
    tex_coord (point2f (tile_s, 0));
    point (point3f ( l,  l, -l));
    tex_coord (point2f (0, 0));
    point (point3f (-l,  l, -l));
    end ();

    begin (mesh::QUADS);
    tex_coord (point2f (0, 1));
    point (point3f (-l, -l, -l));
    tex_coord (point2f (0, 0));
    point (point3f (-l,  l, -l));
    tex_coord (point2f (tile_f, 0));
    point (point3f (-l,  l,  l));
    tex_coord (point2f (tile_f, 1));
    point (point3f (-l, -l,  l));
    end ();

    begin (mesh::QUADS);
    tex_coord (point2f (0, 0));
    point (point3f (-l, l, -l));
    tex_coord (point2f (tile_t, 0));
    point (point3f ( l, l, -l));
    tex_coord (point2f (tile_t, 1));
    point (point3f ( l, l,  l));
    tex_coord (point2f (0, 1));
    point (point3f (-l, l,  l));
    end ();

    begin (mesh::QUADS);
    tex_coord (point2f (0, 0));
    point (point3f (-l, -l, -l));
    tex_coord (point2f (tile_t, 0));
    point (point3f ( l, -l, -l));
    tex_coord (point2f (tile_t, 1));
    point (point3f ( l, -l,  l));
    tex_coord (point2f (0, 1));
    point (point3f (-l, -l,  l));
    end ();
}

void multi_textured_cube::set_top_bottom (boost::shared_ptr<gra::texture> tex)
{
    get (4).set_texture (tex);
    get (5).set_texture (tex);
}

void multi_textured_cube::set_front_back (boost::shared_ptr<gra::texture> tex)
{
    get (1).set_texture (tex);
    get (3).set_texture (tex);
}

void multi_textured_cube::set_left_right (boost::shared_ptr<gra::texture> tex)
{
    get (0).set_texture (tex);
    get (2).set_texture (tex);
}


} /* namespace geo */
} /* namespace yage */
