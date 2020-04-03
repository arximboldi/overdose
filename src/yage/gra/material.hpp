/*
 *  File:       material.hpp
 *  Author:     Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  Date:       Sun May 10 18:33:37 2009
 *
 *  Interfaz de la clase material.
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

#ifndef YAGE_MATERIAL_H_
#define YAGE_MATERIAL_H_

#include <boost/shared_ptr.hpp>
#include <yage/base/point4.hpp>

namespace yage
{
namespace gra
{

class material
{
public:
    material (const base::point4f& ambient  = base::point4f (1.0, 1.0, 1.0, 1.0),
	      const base::point4f& diffuse  = base::point4f (1.0, 1.0, 1.0, 1.0),
	      const base::point4f& specular = base::point4f (1.0, 1.0, 1.0, 1.0),
	      int shininess = 128);

    void apply ();

    void set_ambient (const base::point4f& ambient)
    {
	m_ambient = ambient;
    }

    void set_diffuse (const base::point4f& diffuse)
    {
	m_diffuse = diffuse;
    }

    void set_specular (const base::point4f& specular)
    {
	m_specular = specular;
    }

    void set_shininess (int shininess)
    {
	m_shininess = shininess;
    }

    const base::point4f& get_ambient () const
    {
	return m_ambient;
    }

    const base::point4f& get_diffuse () const
    {
	return m_diffuse;
    }

    const base::point4f& get_specular () const
    {
	return m_specular;
    }

    int get_shininess () const
    {
	return m_shininess;
    }

private:
    base::point4f m_ambient;
    base::point4f m_diffuse;
    base::point4f m_specular;
    int m_shininess;
};

typedef boost::shared_ptr<material> material_ptr;

} /* namespace gra */
} /* namespace yage */



#endif /* YAGE_MATERIAL_H_ */
