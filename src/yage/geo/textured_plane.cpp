/**
 *  @file        textured_plane.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 17 18:23:25 2009
 *
 *  Implementación de textured_plane.
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

#include "textured_plane.hpp"

using namespace yage::base;

namespace yage
{
namespace geo
{

textured_plane::textured_plane (float htiles,
				float vtiles,
                                int hdiv,
                                int vdiv)
{
    hdiv = std::max(1, hdiv);
    vdiv = std::max(1, vdiv);

    const float hl = 1.0 / hdiv;
    const float vl = 1.0 / vdiv;
    const float x = -.5;
    const float y = -.5;
    begin (QUADS);

    for (auto i = 0; i < hdiv; ++i) {
        for (auto j = 0; j < vdiv; ++j) {
            auto x0 = i * hl;
            auto x1 = (i + 1) * hl;
            auto y0 = j * vl;
            auto y1 = (j + 1) * vl;
            tex_coord (point2f (x0 * htiles, y0 * vtiles));
            point (point3f (0, y + y0, x + x0));
            tex_coord (point2f (x1 * htiles, y0 * vtiles));
            point (point3f (0, y + y0, x + x1));
            tex_coord (point2f (x1 * htiles, y1 * vtiles));
            point (point3f (0, y + y1, x + x1));
            tex_coord (point2f (x0 * htiles, y1 * vtiles));
            point (point3f (0, y + y1, x + x0));
        }
    }

    end ();
}


} /* namespace geo */
} /* namespace yage */
