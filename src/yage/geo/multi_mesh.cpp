/**
 *  Time-stamp:  <2009-05-23 21:22:28 raskolnikov>
 *
 *  @file        multi_mesh.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 10 21:51:30 2009
 *
 *  Implementación de la clase multi_mesh.
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

#include "multi_mesh.hpp"

using namespace std;

namespace yage
{
namespace geo
{

YAGE_DEFINE_ERROR_WHERE_WHAT (multi_mesh_error, "multi_mesh",
			      "Invalid multi_mesh state.");

void multi_mesh::set_material (boost::shared_ptr<gra::material> material)
{
    for (vector<mesh>::iterator it = m_mesh.begin (); it != m_mesh.end (); ++it)
	it->set_material (material);
}

void multi_mesh::set_texture (boost::shared_ptr<gra::texture> texture)
{
    for (vector<mesh>::iterator it = m_mesh.begin (); it != m_mesh.end (); ++it)
	it->set_texture (texture);
}

void multi_mesh::begin (mesh::polygon_type mode,
			int n_vertex_est,
			mesh::normal_type normal)
{
    check_state (false);
    m_mesh.push_back (mesh ());
    m_mesh.back ().begin (mode, n_vertex_est, normal);
}

void multi_mesh::end ()
{
    check_state (true);
    m_mesh.back ().end ();
}

void multi_mesh::point (const base::point3f& p)
{
    check_state (true);
    m_mesh.back ().point (p);
}

void multi_mesh::tex_coord (const base::point2f & t)
{
    check_state (true);
    m_mesh.back ().tex_coord (t);
}

void multi_mesh::colour (const base::point3f& p)
{
    check_state (true);
    m_mesh.back ().colour (p);
}
    
void multi_mesh::draw ()
{
    check_state (false);
    for (vector<mesh>::iterator it = m_mesh.begin (); it != m_mesh.end (); ++it)
	it->draw ();
}

void multi_mesh::draw_raw ()
{
    check_state (false);
    for (vector<mesh>::iterator it = m_mesh.begin (); it != m_mesh.end (); ++it)
	it->draw_raw ();
}

} /* namespace geo */
} /* namespace yage */
