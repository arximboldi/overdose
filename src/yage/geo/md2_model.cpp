/**
 *  @file        md2_model.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Tue May 12 09:22:34 2009
 *
 *  Implementación de la clase md2_mode.cpp
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

#include <cmath>

#include "yage/base/point4.hpp"
#include "yage/gra/material.hpp"
#include "yage/gra/texture.hpp"
#include "md2_model.hpp"

namespace yage
{
namespace geo
{

YAGE_DEFINE_ERROR_WHERE (md2_model_error, "md2_model");

md2_model::md2_model (boost::shared_ptr<md2_model_impl> impl,
		      render_mode mode)
    : m_impl (impl)
    , m_mode (mode)
    , m_curr_frame (0)
    , m_next_frame (0)
    , m_interp (0)
    , m_anim_start (0)
    , m_anim_end (0)
{}

float md2_model::get_loop_offset ()
{
    return 1.0f + 1.0f / (m_anim_end - m_anim_start);
}

void md2_model::animate (float percent)
{
    size_t range = m_anim_end - m_anim_start;

    m_curr_frame = m_anim_start + int (range * percent) % (range + 1);
    m_next_frame = m_curr_frame + 1;
    if (m_next_frame > m_anim_end)
	m_next_frame -= range + 1;

    m_interp = range * percent - std::floor (range * percent);
}

void md2_model::draw_raw ()
{
    (m_impl.get ()->* (m_mode == TRIANGLES ?
	      &md2_model_impl::draw_frame_interpolated_triangles :
	      &md2_model_impl::draw_frame_interpolated_commands))
	(m_curr_frame, m_next_frame, m_interp);
}

void md2_model::draw ()
{
    glPushMatrix ();
    glRotatef (-90, 1, 0, 0); /* Corregir la orientación de los MD2 */

    if (m_material)
	m_material->apply ();
    if (m_texture)
	m_texture->enable ();

    draw_raw ();

    if (m_texture)
	m_texture->disable ();

    glPopMatrix ();
}

void md2_model::set_animation (const std::string& name)
{
    if (!m_impl->get_animation_bounds (name, m_anim_start, m_anim_end, m_anim_fps))
	throw md2_model_error ("Unknown animation: " + name);
    else {
	m_curr_frame = m_anim_start;
	m_next_frame = m_anim_start;
	m_interp = 0;
	m_anim = name;
    }
}

} /* namespace geo */
} /* namespace yage */
