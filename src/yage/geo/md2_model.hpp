/**
 *  Time-stamp:  <2009-06-15 19:48:02 raskolnikov>
 *
 *  @file        md2_model.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Tue May 12 09:20:36 2009
 *
 *  Interfaz de la clase md2_model.
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

#ifndef YAGE_MD2_MODEL_H_
#define YAGE_MD2_MODEL_H_

#include <yage/geo/md2_model_impl.hpp>

#include <yage/gra/geometry.hpp>
#include <yage/gra/animation.hpp>

namespace yage
{

namespace gra
{
class material;
}

namespace geo
{

YAGE_DECLARE_ERROR (base::yage_error, md2_model_error);

class md2_model : public gra::geometry
		, public gra::animation
{
public:
    static const float FRAME_TICKS = 100;
    
    enum render_mode
    {
	TRIANGLES,
	COMMANDS
    };
    
    md2_model (boost::shared_ptr<md2_model_impl> impl,
	       render_mode mode = COMMANDS);

    void draw ();
    void draw_raw ();
    
    void animate (float percent);
    void set_animation (const std::string& name);
    float get_loop_offset ();
    
    const std::string& get_animation () const
    {
	return m_anim;
    }
    
    void set_material (boost::shared_ptr<gra::material> material)
    {
	m_material = material;
    }

    void set_texture (boost::shared_ptr<gra::texture> texture)
    {
	m_texture = texture;
    }

    float get_duration ()
    {
	return (m_anim_end - m_anim_start) * FRAME_TICKS;
    }

    boost::shared_ptr<md2_model_impl> get_impl ()
    {
	return m_impl;
    }
    
private:
    boost::shared_ptr<md2_model_impl> m_impl;
    render_mode m_mode;

    int m_curr_frame;
    int m_next_frame;
    float m_interp;
    float m_new_interp;
    
    int m_anim_start;
    int m_anim_end;
    int m_anim_fps;
    
    boost::shared_ptr<gra::material> m_material;
    boost::shared_ptr<gra::texture> m_texture;

    std::string m_anim;
};

typedef boost::shared_ptr<md2_model> md2_model_ptr;

} /* namespace geo */
} /* namespace yage */

#endif /* YAGE_MD2_MODEL_H_ */
