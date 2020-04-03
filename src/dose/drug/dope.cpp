/**
 *  Time-stamp:  <2009-06-13 12:31:24 raskolnikov>
 *
 *  @file        dope.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu Jun 11 19:13:55 2009
 *
 *  Implementación de la clase dope.
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

#include <algorithm>
#include <yage/core/system.hpp>
#include "dope.hpp"

using namespace yage;

namespace dose
{
namespace drug
{

dope::dope (const std::string& name,
	    const std::string& tex,
	    float psychodelia,
	    float ecstasy,
	    float euphoria,
	    float progress,
	    float speed)
    : m_name (name)
    , m_texture (yage::core::system::self ().graphic ().textures ().find (tex))
    , m_psychodelia (psychodelia)
    , m_ecstasy (ecstasy)
    , m_euphoria (euphoria)
    , m_progress (progress)
    , m_speed (speed)
{
    m_texture->set_blending (true);
}

void dope::update (int delta)
{
    m_progress = std::max (m_progress - m_speed * delta, 0.0f);
}

} /* namespace drug */
} /* namespace dose */
