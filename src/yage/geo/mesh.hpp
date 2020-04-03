/*
 *  File:       mesh.hpp
 *  Author:     Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  Date:       Sun May  3 13:18:21 2009
 *
 *  Declaracion de la clase Mesh.
 *
 *  @todo A esta clase le hacen falta dos cosas bastante importantes,
 *        que tal vez se puedan implementar colaborando con otras clases:
 *        a) Soporte para vertex buffers.
 *        b) Soporte para animaciones por keyframes, de tal forma
 *           que podamos unificar con md2_model_impl.
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

#ifndef YAGE_MESH_H
#define YAGE_MESH_H

#include <vector>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL.h>
#include <boost/shared_ptr.hpp>

#include <yage/base/point2.hpp>
#include <yage/base/point3.hpp>
#include <yage/base/point4.hpp>
#include <yage/base/exception.hpp>

#include <yage/gra/geometry.hpp>

namespace yage
{

namespace gra
{
class texture;
class material;
}

namespace geo
{

YAGE_DECLARE_ERROR (base::yage_error, mesh_error);

class mesh : public gra::geometry
{
public:
    enum polygon_type
    {
	TRIANGLES = GL_TRIANGLES,
	QUADS     = GL_QUADS
    };

    enum normal_type
    {
	NONE = 0,
	FACE,
	VERTEX
    };

    mesh ();

    void begin (polygon_type mode,
		int n_vertex_est = 0,
		normal_type normal = VERTEX);
    void end ();

    void point (const base::point3f& p);
    void tex_coord (const base::point2f& t);
    void colour (const base::point3f& p);

    void set_material (boost::shared_ptr<gra::material> material)
    {
	m_material = material;
    }

    void set_texture (boost::shared_ptr<gra::texture> texture)
    {
	m_texture = texture;
    }

    bool get_state () const
    {
	return m_working;
    }

    void draw ();

    void draw_raw ();

private:
    struct mesh_point
    {
	base::point2f tex;
	base::point3f point;
	base::point3f colour;
	base::point3f norm;
	bool has_colour;
	bool has_tex;
    };

    struct mesh_face
    {
	base::point3f tri [3];
	base::point3f norm;
    };

    std::vector<mesh_point> m_vertex;
    std::vector<mesh_face> m_faces;

    polygon_type m_poly_type;
    normal_type m_norm_type;

    bool m_working;
    mesh_point m_curr;

    bool m_faces_normal;
    bool m_vertex_normal;

    boost::shared_ptr<gra::texture>  m_texture;
    boost::shared_ptr<gra::material> m_material;

    void normalize_faces ();
    void normalize_vertex ();

    void check_state (bool expected)
    {
	if (m_working != expected)
	    throw mesh_error ();
    }
};

typedef boost::shared_ptr<geo::mesh> mesh_ptr;

} /* namespace geo */
} /* namespace yage */

#endif /* YAGE_MESH_H */
