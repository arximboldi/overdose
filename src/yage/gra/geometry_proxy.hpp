/**
 *  Time-stamp:  <2009-05-23 21:24:45 raskolnikov>
 *
 *  @file        geometry_proxy.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sat May 23 20:55:19 2009
 *
 *  Interfaz de geometry_proxy.
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

#ifndef YAGE_GEOMETRY_PROXY_H_
#define YAGE_GEOMETRY_PROXY_H_

#include <yage/gra/geometry.hpp>

namespace yage
{
namespace gra
{

class geometry_proxy : public geometry
{
public:
    geometry_proxy (boost::shared_ptr<geometry> proxy);
    
    void draw ();
    void draw_raw ();

    void set_proxy (boost::shared_ptr<geometry> proxy)
    {
	m_proxy = proxy;
    }

    void set_material (boost::shared_ptr<material> material)
    {
	m_material = material;
    }

    void set_texture (boost::shared_ptr<texture> texture)
    {
	m_texture = texture;
    }

private:
    boost::shared_ptr<texture>  m_texture;
    boost::shared_ptr<material> m_material;
    boost::shared_ptr<geometry> m_proxy;
};

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_GEOMETRY_PROXY_H_ */
