/**
 *  Time-stamp:  <2009-05-24 19:25:21 raskolnikov>
 *
 *  @file        multi_mesh.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 10 21:51:09 2009
 *
 *  Interfaz de la clase multi_mesh.
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

#ifndef YAGE_MULTI_MESH_H_
#define YAGE_MULTI_MESH_H_

#include <yage/geo/mesh.hpp>

namespace yage
{
namespace geo
{

YAGE_DECLARE_ERROR (base::yage_error, multi_mesh_error);

class multi_mesh : public gra::geometry
{
public:

    
    void set_material (boost::shared_ptr<gra::material> material);
    void set_texture (boost::shared_ptr<gra::texture> texture);
    
    void begin (mesh::polygon_type mode,
		int n_vertex_est = 0,
		mesh::normal_type normal = mesh::VERTEX);
    void end ();

    void point (const base::point3f& p);
    void tex_coord (const base::point2f & t);
    void colour (const base::point3f& p);
    
    void draw ();
    void draw_raw ();
    
    mesh& get (size_t index)
    {
	return m_mesh [index];
    }
    
private:
    std::vector<mesh> m_mesh;

    void check_state (bool expected)
    {
	if ((!m_mesh.empty () && m_mesh.back ().get_state () != expected) ||
	    (m_mesh.empty () && expected))
	    throw multi_mesh_error ();
    }
};

} /* namespace geo */
} /* namespace yage */

#endif /* YAGE_MULTI_MESH_H_ */
