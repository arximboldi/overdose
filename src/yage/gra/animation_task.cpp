/**
 *  @file        animation_task.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 17 20:29:21 2009
 *
 *  Implementación de animation_task.
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
#include <cmath>
#include "animation_task.hpp"

namespace yage
{
namespace gra
{

animation_task::animation_task (boost::shared_ptr<animation> anim,
				float speed,
				bool loop)
    : m_anim (anim)
    , m_len (1.0f)
    , m_pos (0.0f)
    , m_speed (speed)
    , m_loop (loop)
{
}

void animation_task::update (int delta)
{
    m_anim->animate (m_pos);
    m_pos += (float) delta * m_speed / m_anim->get_duration ();

    if (m_loop) {
	if (m_pos >= m_anim->get_loop_offset ())
	    m_pos = m_pos - m_anim->get_loop_offset ();
    } else if (m_pos >= m_len) {
	static int i = 0;
	++i;
	m_pos = m_len;
	finish ();
	m_anim->animate (m_pos);
    }
}

} /* namespace gra */
} /* namespace yage */
