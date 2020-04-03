/**
 *  @file        camera.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 12:05:33 2009
 *
 *  Implementación de la camara.
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

#include <iostream>
#include <cassert>
#include <cmath>
#include <SDL/SDL_opengl.h>

#include <lib/vertex.h>
#include <lib/matrix.h>

#include "camera.hpp"

using namespace yage::base;

static inline float to_deg (float rad)
{
    return rad * 180 / M_PI;
}

namespace yage
{
namespace gra
{

camera::camera (const point3f& pos)
    : m_fov (DEFAULT_FOV)
    , m_ratio (DEFAULT_RATIO)
    , m_near (1)
    , m_far (20000)
    , m_vrp (pos)
    , m_vpn (point3f (0.0, 0.0, -1.0))
    , m_vup (point3f (0.0, 1.0, 0.0))
{
}

void camera::apply_projection (size_t sc_width, size_t sc_height)
{
    gluPerspective (m_fov, (GLfloat) sc_width / sc_height * m_ratio, m_near, m_far);
}

void camera::apply_model_rotation ()
{
    float angle_x, angle_y, angle_z;

    point3f   u_aux;
    _vertex4f n, u;
    _matrix4f m;

    u_aux = m_vup.cross (m_vpn);
    n = _vertex4f (m_vpn[0], m_vpn[1], m_vpn[2], 1);
    u = _vertex4f (u_aux[0], u_aux[1], u_aux[2], 1);
    angle_x = to_deg (atan2 (n.y, n.z));

    m.rotate_axis_x (angle_x);
    n *= m;
    u *= m;
    angle_y = - to_deg (atan2 (n.x, n.z));

    m.rotate_axis_y (angle_y);
    u *= m;
    angle_z = - to_deg (atan2 (u.y, u.x));

    glRotatef (angle_z, 0, 0, 1);
    glRotatef (angle_y, 0, 1, 0);
    glRotatef (angle_x, 1, 0, 0);
}

void camera::apply_model_translation ()
{
    glTranslatef (-m_vrp.x (), -m_vrp.y (), -m_vrp.z ());
}

void camera::set_position (const point3f& vec)
{
    m_vrp = vec;
}

void camera::set_plane_normal (const point3f& vec)
{
    m_vpn = vec.normalize ();
}

void camera::set_up_vector (const point3f& vec)
{
    m_vup = vec;
}

void camera::look_at (const point3f& pos)
{
    m_vpn = (m_vrp - pos).normalize ();
}

} /* namespace gra */
} /* namespace yage */
