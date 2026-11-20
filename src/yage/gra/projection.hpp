/**
 *  @file        projection.hpp
 *
 *  Perspective projection without depending on GLU.
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

#ifndef YAGE_PROJECTION_H_
#define YAGE_PROJECTION_H_

#include <cmath>
#include <SDL_opengl.h>

namespace yage
{
namespace gra
{

/**
 * Multiplies the current matrix by a perspective projection, exactly
 * like gluPerspective. GLU is not available everywhere (WebGL, for
 * example), but glFrustum is.
 *
 * @param fovy   Vertical field of view, in degrees.
 * @param aspect Width divided by height of the viewport.
 * @param znear  Distance to the near clipping plane.
 * @param zfar   Distance to the far clipping plane.
 */
inline void perspective (double fovy, double aspect, double znear, double zfar)
{
    const double top = znear * std::tan (fovy * M_PI / 360.0);
    const double right = top * aspect;
    glFrustum (-right, right, -top, top, znear, zfar);
}

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_PROJECTION_H_ */
