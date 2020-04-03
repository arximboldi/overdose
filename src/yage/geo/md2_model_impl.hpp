/**
 *  @file        md2_model_impl.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Wed May 13 10:05:03 2009
 *
 *  Interfaz de la clase md2_model_impl.hpp
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

#ifndef YAGE_MD2_MODEL_IMPL_H_
#define YAGE_MD2_MODEL_IMPL_H_

#include <vector>
#include <map>

#include <boost/shared_ptr.hpp>
#include <SDL/SDL_opengl.h>

#include <yage/base/iterator.hpp>
#include <yage/base/exception.hpp>
#include <yage/gra/geometry.hpp>

namespace yage
{

namespace gra
{
class texture;
}

namespace geo
{

YAGE_DECLARE_ERROR (base::yage_error, md2_model_impl_error);

namespace detail
{

typedef GLfloat md2_vec2[2];
typedef GLfloat md2_vec3[3];

struct md2_header
{
    int ident;
    int version;

    int skinwidth;
    int skinheight;

    int framesize;

    int num_skins;
    int num_vertices;
    int num_st;
    int num_tris;
    int num_glcmds;
    int num_frames;

    int offset_skins;
    int offset_st;
    int offset_tris;
    int offset_frames;
    int offset_glcmds;
    int offset_end;
};

struct md2_skin
{
    char name[64];
};

struct md2_texcoord
{
    short s;
    short t;
};

struct md2_triangle
{
    unsigned short vertex[3];
    unsigned short st[3];
};

struct md2_vertex
{
    unsigned char v[3];
    unsigned char normal_index;
};

struct md2_frame
{
    md2_vec3 scale;
    md2_vec3 translate;
    char name[16];
    md2_vertex* verts;

    md2_frame () : verts (0) {}
    ~md2_frame () { delete verts; }
};

struct md2_glcmd
{
    float s;
    float t;
    int index;
};

struct md2_anim
{
    int start;
    int end;
    int fps;
};

} /* namespace detail */

class md2_model_impl : public gra::geometry
		     , public base::non_copyable
{
public:
    typedef
    base::map_key_iterator<std::string, detail::md2_anim>
    anim_iterator;

    typedef
    base::map_key_iterator<std::string, std::string>
    skin_iterator;

    md2_model_impl (const std::string& str);
    ~md2_model_impl ();

    void draw ();
    void draw_raw ();

    void set_texture (boost::shared_ptr<gra::texture> texture)
    {
	m_texture = texture;
    }

    void set_material (boost::shared_ptr<gra::material> material)
    {
	m_material = material;
    }

    anim_iterator anims_begin ()
    {
	return m_anim_map.begin ();
    }

    anim_iterator anims_end ()
    {
	return m_anim_map.end ();
    }

    skin_iterator skins_begin ()
    {
	return m_skin_map.begin ();
    }

    skin_iterator skins_end ()
    {
	return m_skin_map.end ();
    }

    void set_inverse_normals (bool inverse_normals)
    {
	m_inverse_normals = inverse_normals;
    }

    void draw_frame_triangles (size_t frame);
    void draw_frame_commands (size_t frame);
    void draw_frame_interpolated_triangles (size_t src_frame, size_t dst_frame, float interp);
    void draw_frame_interpolated_commands (size_t src_frame, size_t dst_frame, float interp);
    bool get_animation_bounds (const std::string& anim,
			       int& start, int& end, int& fps);

private:
    typedef std::map<std::string, detail::md2_anim> anim_map;
    typedef std::map<std::string, std::string> skin_map;

    void free_data ();
    void load_model (const std::string& fname);
    void setup_animations ();
    void setup_skins ();

    boost::shared_ptr<gra::texture> m_texture;
    boost::shared_ptr<gra::material> m_material;

    detail::md2_header    m_header;
    detail::md2_skin*     m_skins;
    detail::md2_texcoord* m_texcoords;
    detail::md2_triangle* m_triangles;
    detail::md2_frame*    m_frames;
    int*                  m_glcmds;

    skin_map m_skin_map;
    anim_map m_anim_map;

    bool m_inverse_normals;
};

typedef boost::shared_ptr<md2_model_impl> md2_model_impl_ptr;

} /* namespace geo */
} /* namespace yage */

#endif /* YAGE_MD2_MODEL_IMPL_H_ */
