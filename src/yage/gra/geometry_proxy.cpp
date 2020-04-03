/**
 *  @file        geometry_proxy.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sat May 23 21:11:15 2009
 *
 *  Implementación de geometry_proxy.
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

#include "geometry_proxy.hpp"
#include "material.hpp"
#include "texture.hpp"

namespace yage
{
namespace gra
{

geometry_proxy::geometry_proxy (boost::shared_ptr<geometry> proxy)
    : m_proxy (proxy)
{
}

void geometry_proxy::draw ()
{
    if (m_material)
	m_material->apply ();
    if (m_texture)
	m_texture->enable ();
    if (m_proxy)
	m_proxy->draw_raw ();
    if (m_texture)
	m_texture->disable ();
}

void geometry_proxy::draw_raw ()
{
    if (m_proxy)
	m_proxy->draw_raw ();
}

} /* namespace gra */
} /* namespace yage */
