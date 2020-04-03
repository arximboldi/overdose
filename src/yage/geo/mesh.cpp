/**
 *  Time-stamp:  <2011-08-22 23:34:51 raskolnikov>
 *
 *  @file        mesh.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 13:46:45 2009
 *
 *  Implementación de la clase Mesh.
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

#include <map>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>

#include "yage/gra/material.hpp"
#include "yage/gra/texture.hpp"

#include "mesh.hpp"

using namespace std;

namespace yage
{
namespace geo
{

YAGE_DEFINE_ERROR_WHERE_WHAT (mesh_error, "mesh", "Invalid mesh state.");

mesh::mesh ()
    : m_working (false)
    , m_faces_normal (false)
    , m_vertex_normal (false)
{
}

void mesh::begin (polygon_type poly,
		  int n_vertex_est,
		  normal_type norm)
{
    check_state (false);
    
    m_poly_type = poly;
    m_norm_type = norm;
    
    m_vertex.clear ();
    m_faces.clear ();
    m_vertex.reserve (n_vertex_est);
    m_faces.reserve (n_vertex_est / 3);
    
    m_working = true;
    
    m_curr.has_tex = false;
    m_curr.has_colour = false;
}
   
void mesh::point (const base::point3f& p)
{
    check_state (true);
    
    m_curr.point = p;    
    m_vertex.push_back (m_curr);
    
    switch (m_poly_type)
    {
    case TRIANGLES:
	if (m_vertex.size () % 3 == 0)
	{
	    mesh_face face;
	    face.tri [0] = (m_vertex.end () - 3)->point;
	    face.tri [1] = (m_vertex.end () - 2)->point;
	    face.tri [2] = (m_vertex.end () - 1)->point;
	    m_faces.push_back (face);
	}
	break;

    case QUADS:
	if (m_vertex.size () % 6 == 4)
	{
	    m_vertex.push_back (*(m_vertex.end ()-4));
	    m_vertex.push_back (*(m_vertex.end ()-3));

	    mesh_face face;
	    face.tri [0] = (m_vertex.end () - 6)->point;
	    face.tri [1] = (m_vertex.end () - 5)->point;
	    face.tri [2] = (m_vertex.end () - 4)->point;
	    m_faces.push_back (face);

	    face.tri [0] = (m_vertex.end () - 3)->point;
	    face.tri [1] = (m_vertex.end () - 2)->point;
	    face.tri [2] = (m_vertex.end () - 1)->point;
	    m_faces.push_back (face);
	}
	break;
	
    default:
	break;
    }

    m_curr.has_tex = false;
    m_curr.has_colour = false;
}

void mesh::tex_coord (const base::point2f& tex)
{
    check_state (true);
    
    m_curr.has_tex = true;
    m_curr.tex = tex;
}

void mesh::colour (const base::point3f& col)
{
    check_state (true);
    
    m_curr.has_colour = true;
    m_curr.colour = col;
}

void mesh::end ()
{
    check_state (true);

    m_working = false;
    
    switch (m_norm_type) {
    case VERTEX:
	normalize_vertex ();
	break;
	
    case FACE:
	normalize_faces ();
	break;
	
    default:
	break;
    }
}

void mesh::draw_raw ()
{
    check_state (false);
    
    glBegin (GL_TRIANGLES);
    for (size_t j = 0; j < m_vertex.size (); ++j)
    {	
	if (m_vertex[j].has_colour)
	    glColor3fv (&m_vertex[j].colour[0]);
	if (m_vertex[j].has_tex)
	    glTexCoord2f (m_vertex[j].tex[0], m_vertex[j].tex[1]);		
	
	if (m_vertex_normal)
	    glNormal3fv (m_vertex[j].norm.ptr ());
	else if (m_faces_normal && j % 3 == 0)
	    glNormal3fv (m_faces[j/3].norm.ptr ());
	
	glVertex3fv (m_vertex[j].point.ptr ());
    }
    glEnd ();
}

void mesh::draw ()
{
    check_state (false);
    
    if (m_texture)
	m_texture->enable ();
    if (m_material)
	m_material->apply ();

    draw_raw ();
    
    if (m_texture)
	m_texture->disable ();
}
  
void mesh::normalize_faces ()
{
    if (!m_faces_normal)
    {
	for (size_t j = 0; j < m_faces.size(); j++ )
	{
	    base::point3f* tri = m_faces [j].tri;
	    m_faces[j].norm =
		(tri [1] - tri [0]).normal (tri [2] - tri [0]);
	}

	m_faces_normal = true;
    }
}

namespace
{
struct comparator
{
    bool operator () (const base::point3f& a, const base::point3f& b)
    {
	const float epsilon = 0.0001;

	float diff_x = std::abs (a[0] - b[0]);
	float diff_y = std::abs (a[1] - b[1]);
	float diff_z = std::abs (a[2] - b[2]);

	if (diff_x < epsilon && diff_y < epsilon && diff_z < epsilon)
	    return false;
	return a < b;
    }
};
}

void mesh::normalize_vertex ()
{
    if (!m_vertex_normal)
    {
	normalize_faces ();
	
	std::map <base::point3f, std::pair<base::point3f, int>, comparator> norm;
	
	for (vector<mesh_face>::iterator it = m_faces.begin();
	     it != m_faces.end();
	     ++it)
	{
	    norm [it->tri[0]].first += it->norm; ++norm[it->tri[0]].second;
	    norm [it->tri[1]].first += it->norm; ++norm[it->tri[1]].second;
	    norm [it->tri[2]].first += it->norm; ++norm[it->tri[2]].second;
	}

	for (size_t i = 0; i < m_vertex.size (); ++i)
	{
	    m_vertex [i].norm =
		norm [m_vertex[i].point].first * (1.0f / norm [m_vertex[i].point].second);
	}
	
	m_vertex_normal = true;
    }
}

} /* namespace geo */
} /* namespace yage */
