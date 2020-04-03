/**
 *  Time-stamp:  <2009-06-15 19:41:29 raskolnikov>
 *
 *  @file        md2_model_impl.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Wed May 13 10:06:07 2009
 *
 *  Implementación de la clase md2_model_impl.
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

#include "md2_model_impl.hpp"

#include <iostream>
#include <fstream>

#include "yage/base/misc.hpp"
#include "yage/gra/texture.hpp"
#include "yage/gra/material.hpp"

#include "md2_model.hpp"

using namespace std;
using namespace yage::geo::detail;

namespace yage
{
namespace geo
{

YAGE_DEFINE_ERROR_WHERE (md2_model_impl_error, "md2_model_impl");

static const int      MD2_IDENT   = 'I' + ('D'<<8) + ('P'<<16) + ('2'<<24);
static const int      MD2_VERSION = 8;
static const md2_vec3 MD2_NORMAL_TABLE [] =
{
    { -0.525731f,  0.000000f,  0.850651f }, 
    { -0.442863f,  0.238856f,  0.864188f }, 
    { -0.295242f,  0.000000f,  0.955423f }, 
    { -0.309017f,  0.500000f,  0.809017f }, 
    { -0.162460f,  0.262866f,  0.951056f }, 
    {  0.000000f,  0.000000f,  1.000000f }, 
    {  0.000000f,  0.850651f,  0.525731f }, 
    { -0.147621f,  0.716567f,  0.681718f }, 
    {  0.147621f,  0.716567f,  0.681718f }, 
    {  0.000000f,  0.525731f,  0.850651f }, 
    {  0.309017f,  0.500000f,  0.809017f }, 
    {  0.525731f,  0.000000f,  0.850651f }, 
    {  0.295242f,  0.000000f,  0.955423f }, 
    {  0.442863f,  0.238856f,  0.864188f }, 
    {  0.162460f,  0.262866f,  0.951056f }, 
    { -0.681718f,  0.147621f,  0.716567f }, 
    { -0.809017f,  0.309017f,  0.500000f }, 
    { -0.587785f,  0.425325f,  0.688191f }, 
    { -0.850651f,  0.525731f,  0.000000f }, 
    { -0.864188f,  0.442863f,  0.238856f }, 
    { -0.716567f,  0.681718f,  0.147621f }, 
    { -0.688191f,  0.587785f,  0.425325f }, 
    { -0.500000f,  0.809017f,  0.309017f }, 
    { -0.238856f,  0.864188f,  0.442863f }, 
    { -0.425325f,  0.688191f,  0.587785f }, 
    { -0.716567f,  0.681718f, -0.147621f }, 
    { -0.500000f,  0.809017f, -0.309017f }, 
    { -0.525731f,  0.850651f,  0.000000f }, 
    {  0.000000f,  0.850651f, -0.525731f }, 
    { -0.238856f,  0.864188f, -0.442863f }, 
    {  0.000000f,  0.955423f, -0.295242f }, 
    { -0.262866f,  0.951056f, -0.162460f }, 
    {  0.000000f,  1.000000f,  0.000000f }, 
    {  0.000000f,  0.955423f,  0.295242f }, 
    { -0.262866f,  0.951056f,  0.162460f }, 
    {  0.238856f,  0.864188f,  0.442863f }, 
    {  0.262866f,  0.951056f,  0.162460f }, 
    {  0.500000f,  0.809017f,  0.309017f }, 
    {  0.238856f,  0.864188f, -0.442863f }, 
    {  0.262866f,  0.951056f, -0.162460f }, 
    {  0.500000f,  0.809017f, -0.309017f }, 
    {  0.850651f,  0.525731f,  0.000000f }, 
    {  0.716567f,  0.681718f,  0.147621f }, 
    {  0.716567f,  0.681718f, -0.147621f }, 
    {  0.525731f,  0.850651f,  0.000000f }, 
    {  0.425325f,  0.688191f,  0.587785f }, 
    {  0.864188f,  0.442863f,  0.238856f }, 
    {  0.688191f,  0.587785f,  0.425325f }, 
    {  0.809017f,  0.309017f,  0.500000f }, 
    {  0.681718f,  0.147621f,  0.716567f }, 
    {  0.587785f,  0.425325f,  0.688191f }, 
    {  0.955423f,  0.295242f,  0.000000f }, 
    {  1.000000f,  0.000000f,  0.000000f }, 
    {  0.951056f,  0.162460f,  0.262866f }, 
    {  0.850651f, -0.525731f,  0.000000f }, 
    {  0.955423f, -0.295242f,  0.000000f }, 
    {  0.864188f, -0.442863f,  0.238856f }, 
    {  0.951056f, -0.162460f,  0.262866f }, 
    {  0.809017f, -0.309017f,  0.500000f }, 
    {  0.681718f, -0.147621f,  0.716567f }, 
    {  0.850651f,  0.000000f,  0.525731f }, 
    {  0.864188f,  0.442863f, -0.238856f }, 
    {  0.809017f,  0.309017f, -0.500000f }, 
    {  0.951056f,  0.162460f, -0.262866f }, 
    {  0.525731f,  0.000000f, -0.850651f }, 
    {  0.681718f,  0.147621f, -0.716567f }, 
    {  0.681718f, -0.147621f, -0.716567f }, 
    {  0.850651f,  0.000000f, -0.525731f }, 
    {  0.809017f, -0.309017f, -0.500000f }, 
    {  0.864188f, -0.442863f, -0.238856f }, 
    {  0.951056f, -0.162460f, -0.262866f }, 
    {  0.147621f,  0.716567f, -0.681718f }, 
    {  0.309017f,  0.500000f, -0.809017f }, 
    {  0.425325f,  0.688191f, -0.587785f }, 
    {  0.442863f,  0.238856f, -0.864188f }, 
    {  0.587785f,  0.425325f, -0.688191f }, 
    {  0.688191f,  0.587785f, -0.425325f }, 
    { -0.147621f,  0.716567f, -0.681718f }, 
    { -0.309017f,  0.500000f, -0.809017f }, 
    {  0.000000f,  0.525731f, -0.850651f }, 
    { -0.525731f,  0.000000f, -0.850651f }, 
    { -0.442863f,  0.238856f, -0.864188f }, 
    { -0.295242f,  0.000000f, -0.955423f }, 
    { -0.162460f,  0.262866f, -0.951056f }, 
    {  0.000000f,  0.000000f, -1.000000f }, 
    {  0.295242f,  0.000000f, -0.955423f }, 
    {  0.162460f,  0.262866f, -0.951056f }, 
    { -0.442863f, -0.238856f, -0.864188f }, 
    { -0.309017f, -0.500000f, -0.809017f }, 
    { -0.162460f, -0.262866f, -0.951056f }, 
    {  0.000000f, -0.850651f, -0.525731f }, 
    { -0.147621f, -0.716567f, -0.681718f }, 
    {  0.147621f, -0.716567f, -0.681718f }, 
    {  0.000000f, -0.525731f, -0.850651f }, 
    {  0.309017f, -0.500000f, -0.809017f }, 
    {  0.442863f, -0.238856f, -0.864188f }, 
    {  0.162460f, -0.262866f, -0.951056f }, 
    {  0.238856f, -0.864188f, -0.442863f }, 
    {  0.500000f, -0.809017f, -0.309017f }, 
    {  0.425325f, -0.688191f, -0.587785f }, 
    {  0.716567f, -0.681718f, -0.147621f }, 
    {  0.688191f, -0.587785f, -0.425325f }, 
    {  0.587785f, -0.425325f, -0.688191f }, 
    {  0.000000f, -0.955423f, -0.295242f }, 
    {  0.000000f, -1.000000f,  0.000000f }, 
    {  0.262866f, -0.951056f, -0.162460f }, 
    {  0.000000f, -0.850651f,  0.525731f }, 
    {  0.000000f, -0.955423f,  0.295242f }, 
    {  0.238856f, -0.864188f,  0.442863f }, 
    {  0.262866f, -0.951056f,  0.162460f }, 
    {  0.500000f, -0.809017f,  0.309017f }, 
    {  0.716567f, -0.681718f,  0.147621f }, 
    {  0.525731f, -0.850651f,  0.000000f }, 
    { -0.238856f, -0.864188f, -0.442863f }, 
    { -0.500000f, -0.809017f, -0.309017f }, 
    { -0.262866f, -0.951056f, -0.162460f }, 
    { -0.850651f, -0.525731f,  0.000000f }, 
    { -0.716567f, -0.681718f, -0.147621f }, 
    { -0.716567f, -0.681718f,  0.147621f }, 
    { -0.525731f, -0.850651f,  0.000000f }, 
    { -0.500000f, -0.809017f,  0.309017f }, 
    { -0.238856f, -0.864188f,  0.442863f }, 
    { -0.262866f, -0.951056f,  0.162460f }, 
    { -0.864188f, -0.442863f,  0.238856f }, 
    { -0.809017f, -0.309017f,  0.500000f }, 
    { -0.688191f, -0.587785f,  0.425325f }, 
    { -0.681718f, -0.147621f,  0.716567f }, 
    { -0.442863f, -0.238856f,  0.864188f }, 
    { -0.587785f, -0.425325f,  0.688191f }, 
    { -0.309017f, -0.500000f,  0.809017f }, 
    { -0.147621f, -0.716567f,  0.681718f }, 
    { -0.425325f, -0.688191f,  0.587785f }, 
    { -0.162460f, -0.262866f,  0.951056f }, 
    {  0.442863f, -0.238856f,  0.864188f }, 
    {  0.162460f, -0.262866f,  0.951056f }, 
    {  0.309017f, -0.500000f,  0.809017f }, 
    {  0.147621f, -0.716567f,  0.681718f }, 
    {  0.000000f, -0.525731f,  0.850651f }, 
    {  0.425325f, -0.688191f,  0.587785f }, 
    {  0.587785f, -0.425325f,  0.688191f }, 
    {  0.688191f, -0.587785f,  0.425325f }, 
    { -0.955423f,  0.295242f,  0.000000f }, 
    { -0.951056f,  0.162460f,  0.262866f }, 
    { -1.000000f,  0.000000f,  0.000000f }, 
    { -0.850651f,  0.000000f,  0.525731f }, 
    { -0.955423f, -0.295242f,  0.000000f }, 
    { -0.951056f, -0.162460f,  0.262866f }, 
    { -0.864188f,  0.442863f, -0.238856f }, 
    { -0.951056f,  0.162460f, -0.262866f }, 
    { -0.809017f,  0.309017f, -0.500000f }, 
    { -0.864188f, -0.442863f, -0.238856f }, 
    { -0.951056f, -0.162460f, -0.262866f }, 
    { -0.809017f, -0.309017f, -0.500000f }, 
    { -0.681718f,  0.147621f, -0.716567f }, 
    { -0.681718f, -0.147621f, -0.716567f }, 
    { -0.850651f,  0.000000f, -0.525731f }, 
    { -0.688191f,  0.587785f, -0.425325f }, 
    { -0.587785f,  0.425325f, -0.688191f }, 
    { -0.425325f,  0.688191f, -0.587785f }, 
    { -0.425325f, -0.688191f, -0.587785f }, 
    { -0.587785f, -0.425325f, -0.688191f }, 
    { -0.688191f, -0.587785f, -0.425325f }
};

void md2_model_impl::draw ()
{
    if (m_material)
	m_material->apply ();
    if (m_texture)
	m_texture->enable ();

    draw_frame_commands (0);
    
    if (m_texture)
	m_texture->disable ();
}

void md2_model_impl::draw_raw ()
{
    draw_frame_commands (0);
}

bool md2_model_impl::get_animation_bounds (const std::string& name,
					   int& start,
					   int& end,
					   int& fps)
{
    anim_map::iterator result = m_anim_map.find (name);

    if (result != m_anim_map.end ()) {
	start = result->second.start;
	end   = result->second.end;
	fps   = result->second.fps;

	return true;
    }

    return false;
}

void md2_model_impl::free_data ()
{
    delete [] m_skins;
    delete [] m_texcoords;
    delete [] m_triangles;
    delete [] m_frames;
    delete [] m_glcmds;
}

md2_model_impl::~md2_model_impl ()
{
    free_data ();
}

md2_model_impl::md2_model_impl (const std::string& fname)
    : m_skins (0)
    , m_texcoords (0)
    , m_triangles (0)
    , m_frames (0)
    , m_glcmds (0)
    , m_inverse_normals (false)
{
    load_model (fname);
    setup_animations ();
    setup_skins ();
}

void md2_model_impl::load_model (const std::string& fname)
{
    std::ifstream is (fname.c_str (), std::ios::binary);
    
    if (is.fail ())
	throw md2_model_impl_error (std::string ("Could not open file: ") + fname);

    /* Leemos la cabecera */
    is.read (reinterpret_cast<char*> (&m_header), sizeof (md2_header));

    if (m_header.ident   != MD2_IDENT ||
	m_header.version != MD2_VERSION)
	throw md2_model_impl_error (std::string ("Bad file version: ") + fname);

    try {
	m_skins     = new md2_skin [m_header.num_skins];
	m_texcoords = new md2_texcoord [m_header.num_st];
	m_triangles = new md2_triangle [m_header.num_tris];
	m_frames    = new md2_frame [m_header.num_frames];
	m_glcmds    = new int [m_header.num_glcmds];
    } catch (std::bad_alloc& e) {
	free_data ();
	throw e;
    }
    
    /* Leer los nombres de las skins */
    is.seekg (m_header.offset_skins, std::ios::beg);
    is.read (reinterpret_cast<char*> (m_skins),
	     sizeof (md2_skin) * m_header.num_skins);

    /* Leer las coordenadas de las texturas. */
    is.seekg (m_header.offset_st, std::ios::beg);
    is.read (reinterpret_cast<char*>(m_texcoords),
	     sizeof (md2_texcoord) * m_header.num_st);

    /* Leer los datos de los triángulos. */
    is.seekg (m_header.offset_tris, std::ios::beg);
    is.read (reinterpret_cast<char*> (m_triangles),
	     sizeof (md2_triangle) * m_header.num_tris);

    /* Leer los frames */
    is.seekg (m_header.offset_frames, std::ios::beg);
    for (int i = 0; i < m_header.num_frames; ++i) {
	m_frames[i].verts = new md2_vertex [m_header.num_vertices];
	is.read (reinterpret_cast<char*> (&m_frames[i].scale),
		 sizeof (md2_vec3));
	is.read (reinterpret_cast<char*> (&m_frames[i].translate),
		 sizeof (md2_vec3));
	is.read (reinterpret_cast<char*> (&m_frames[i].name),
		 sizeof (char) * 16);
	is.read (reinterpret_cast<char*> (m_frames[i].verts),
		 sizeof (md2_vertex) * m_header.num_vertices);
    }

    /* Leer los comandos Opengl */
    is.seekg (m_header.offset_glcmds, std::ios::beg);
    is.read (reinterpret_cast<char*>(m_glcmds),
	     sizeof (int) * m_header.num_glcmds);    
}

void md2_model_impl::setup_skins ()
{
    for (int i = 0; i < m_header.num_skins; ++i) {
	m_skin_map.insert (std::make_pair (base::basename_str (m_skins[i].name),
					   m_skins[i].name));
    }
}

void md2_model_impl::setup_animations ()
{
    string   curr_anim;
    md2_anim anim_info = { 0, 0, 0};

    for (int i = 0; i < m_header.num_frames; ++i)
    {
	string frame_name = m_frames[i].name;
	string frame_anim;

	/* Extraemos el nombre de la animación. */
	string::size_type len = frame_name.find_first_of ("0123456789");
	if (len == frame_name.length () - 3 && frame_name [len] != '0')
	    len ++;

	frame_anim.assign (frame_name, 0, len);

	if (curr_anim != frame_anim) {
	    if (i > 0) {
		m_anim_map.insert (make_pair (curr_anim, anim_info));
	    }
	    
	    anim_info.start = i;
	    anim_info.end   = i;
	    curr_anim       = frame_anim;
	} else {
	    anim_info.end = i;
	}
    }
    m_anim_map.insert (make_pair (curr_anim, anim_info));
}

void md2_model_impl::draw_frame_triangles (size_t frame)
{
    if (frame >= (size_t) m_header.num_frames)
	throw md2_model_impl_error ("Requested frame does not exist.");

    md2_frame* curr_frame = m_frames + frame;
    
    glBegin (GL_TRIANGLES);
    for (int i = 0; i < m_header.num_tris; ++i) {
	for (int j = 0; j < 3; ++j) {
	    md2_vertex*   curr_vert     = curr_frame->verts + m_triangles[i].vertex[j];
	    md2_texcoord* curr_texcoord = m_texcoords + m_triangles[i].st[j];

	    GLfloat s = (GLfloat) curr_texcoord->s / m_header.skinwidth;
	    GLfloat t = (GLfloat) curr_texcoord->t / m_header.skinheight;

	    glTexCoord2f (s, t);

	    if (!m_inverse_normals) {
		glNormal3fv (MD2_NORMAL_TABLE [curr_vert->normal_index]);
	    } else {
		float normal [] = {
		    -MD2_NORMAL_TABLE [curr_vert->normal_index][0],
		    -MD2_NORMAL_TABLE [curr_vert->normal_index][1],
		    -MD2_NORMAL_TABLE [curr_vert->normal_index][2]
		};
		glNormal3fv (normal);
	    }
	    
	    md2_vec3 v;
	    v[0] = curr_frame->scale[0] * curr_vert->v[0] + curr_frame->translate[0];
	    v[1] = curr_frame->scale[1] * curr_vert->v[1] + curr_frame->translate[1];
	    v[2] = curr_frame->scale[2] * curr_vert->v[2] + curr_frame->translate[2];

	    glVertex3fv (v);
	}
    }
    glEnd();
}

void md2_model_impl::draw_frame_commands (size_t frame)
{
    if (frame >= (size_t) m_header.num_frames)
	throw md2_model_impl_error ("Requested frame does not exist.");

    md2_frame* curr_frame = m_frames + frame;
    int* curr_glcmd_list = m_glcmds;
    int i;

    while ((i = *curr_glcmd_list++) != 0) {
	if (i < 0) {
	    glBegin (GL_TRIANGLE_FAN);
	    i = -i;
	} else
	    glBegin (GL_TRIANGLE_STRIP);

	for (; i > 0; --i, curr_glcmd_list += 3) {
	    md2_glcmd*  curr_glcmd = reinterpret_cast<md2_glcmd*> (curr_glcmd_list);
	    md2_vertex* curr_vert  = curr_frame->verts + curr_glcmd->index;

	    glTexCoord2f (curr_glcmd->s, curr_glcmd->t);
	    if (!m_inverse_normals) {
		glNormal3fv (MD2_NORMAL_TABLE [curr_vert->normal_index]);
	    } else {
		float normal [] = {
		    -MD2_NORMAL_TABLE [curr_vert->normal_index][0],
		    -MD2_NORMAL_TABLE [curr_vert->normal_index][1],
		    -MD2_NORMAL_TABLE [curr_vert->normal_index][2]
		};
		glNormal3fv (normal);
	    }
	    
	    md2_vec3 v;
	    v[0] = curr_frame->scale[0] * curr_vert->v[0] + curr_frame->translate[0];
	    v[1] = curr_frame->scale[1] * curr_vert->v[1] + curr_frame->translate[1];
	    v[2] = curr_frame->scale[2] * curr_vert->v[2] + curr_frame->translate[2];

	    glVertex3fv (v);
	}

	glEnd();
    }
}

void md2_model_impl::draw_frame_interpolated_triangles (size_t src_frame,
						   size_t dst_frame,
						   float interp)
{
    if (src_frame >= (size_t) m_header.num_frames ||
	dst_frame >= (size_t) m_header.num_frames)
	throw md2_model_impl_error ("Requested frame does not exist.");

    md2_frame* curr_src_frame = m_frames + src_frame;
    md2_frame* curr_dst_frame = m_frames + dst_frame;

    glBegin (GL_TRIANGLES);
    for (int i = 0; i < m_header.num_tris; ++i) {
	for (int j = 0; j < 3; ++j) {
	    md2_vertex*   curr_src_vert = curr_src_frame->verts + m_triangles[i].vertex[j];
	    md2_vertex*   curr_dst_vert = curr_dst_frame->verts + m_triangles[i].vertex[j];
	    md2_texcoord* curr_texcoord = m_texcoords + m_triangles[i].st[j];

	    GLfloat s = (GLfloat) curr_texcoord->s / m_header.skinwidth;
	    GLfloat t = (GLfloat) curr_texcoord->t / m_header.skinheight;

	    glTexCoord2f (s, t);

	    const GLfloat* src_norm = MD2_NORMAL_TABLE [curr_src_vert->normal_index];
	    const GLfloat* dst_norm = MD2_NORMAL_TABLE [curr_dst_vert->normal_index];
	    md2_vec3 n;
	    
	    n[0] = src_norm[0] + interp * (dst_norm[0] - src_norm[0]);
	    n[1] = src_norm[1] + interp * (dst_norm[1] - src_norm[1]);
	    n[2] = src_norm[2] + interp * (dst_norm[2] - src_norm[2]);
	    
	    if (!m_inverse_normals) {
		glNormal3fv (n);
	    } else {
		float normal [] = { -n[0], -n[1], -n[2] };
		glNormal3fv (normal);
	    }

	    md2_vec3 src_vec, dst_vec, v;
	    src_vec[0] = curr_src_frame->scale[0] * curr_src_vert->v[0] + curr_src_frame->translate[0];
	    src_vec[1] = curr_src_frame->scale[1] * curr_src_vert->v[1] + curr_src_frame->translate[1];
	    src_vec[2] = curr_src_frame->scale[2] * curr_src_vert->v[2] + curr_src_frame->translate[2];

	    dst_vec[0] = curr_dst_frame->scale[0] * curr_dst_vert->v[0] + curr_dst_frame->translate[0];
	    dst_vec[1] = curr_dst_frame->scale[1] * curr_dst_vert->v[1] + curr_dst_frame->translate[1];
	    dst_vec[2] = curr_dst_frame->scale[2] * curr_dst_vert->v[2] + curr_dst_frame->translate[2];

	    v[0] = src_vec[0] + interp * (dst_vec[0] - src_vec[0]);
	    v[1] = src_vec[1] + interp * (dst_vec[1] - src_vec[1]);
	    v[2] = src_vec[2] + interp * (dst_vec[2] - src_vec[2]);

	    glVertex3fv (v);
	}
    }
    glEnd();
}

void md2_model_impl::draw_frame_interpolated_commands (size_t src_frame,
						  size_t dst_frame,
						  float interp)
{
    if (src_frame >= (size_t) m_header.num_frames ||
	dst_frame >= (size_t) m_header.num_frames)
	throw md2_model_impl_error ("Requested frame does not exist.\n");

    md2_frame* curr_src_frame = m_frames + src_frame;
    md2_frame* curr_dst_frame = m_frames + dst_frame;
    int*       curr_glcmd_list = m_glcmds;
    int i;

    while ((i = *curr_glcmd_list++) != 0) {
	if (i < 0) {
	    glBegin (GL_TRIANGLE_FAN);
	    i = -i;
	} else
	    glBegin (GL_TRIANGLE_STRIP);

	for (; i > 0; --i, curr_glcmd_list += 3)
	{
	    md2_glcmd* curr_glcmd = reinterpret_cast<md2_glcmd*>(curr_glcmd_list);

	    md2_vertex* curr_src_vert = curr_src_frame->verts + curr_glcmd->index;
	    md2_vertex* curr_dst_vert = curr_dst_frame->verts + curr_glcmd->index;

	    glTexCoord2f (curr_glcmd->s, curr_glcmd->t);

	    const GLfloat* src_norm = MD2_NORMAL_TABLE [curr_src_vert->normal_index];
	    const GLfloat* dst_norm = MD2_NORMAL_TABLE [curr_dst_vert->normal_index];
	    md2_vec3 n;
	    
	    n[0] = src_norm[0] + interp * (dst_norm[0] - src_norm[0]);
	    n[1] = src_norm[1] + interp * (dst_norm[1] - src_norm[1]);
	    n[2] = src_norm[2] + interp * (dst_norm[2] - src_norm[2]);

	    if (!m_inverse_normals) {
		glNormal3fv (n);
	    } else {
		float normal [] = { -n[0], -n[1], -n[2] };
		glNormal3fv (normal);
	    }

	    md2_vec3 src_vec, dst_vec, v;
	    src_vec[0] = curr_src_frame->scale[0] * curr_src_vert->v[0] + curr_src_frame->translate[0];
	    src_vec[1] = curr_src_frame->scale[1] * curr_src_vert->v[1] + curr_src_frame->translate[1];
	    src_vec[2] = curr_src_frame->scale[2] * curr_src_vert->v[2] + curr_src_frame->translate[2];

	    dst_vec[0] = curr_dst_frame->scale[0] * curr_dst_vert->v[0] + curr_dst_frame->translate[0];
	    dst_vec[1] = curr_dst_frame->scale[1] * curr_dst_vert->v[1] + curr_dst_frame->translate[1];
	    dst_vec[2] = curr_dst_frame->scale[2] * curr_dst_vert->v[2] + curr_dst_frame->translate[2];

	    v[0] = src_vec[0] + interp * (dst_vec[0] - src_vec[0]);
	    v[1] = src_vec[1] + interp * (dst_vec[1] - src_vec[1]);
	    v[2] = src_vec[2] + interp * (dst_vec[2] - src_vec[2]);

	    glVertex3fv (v);
	}

	glEnd();
    }
}

} /* namespace geo */
} /* namespace yage */

