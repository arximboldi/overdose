/**
 *  Time-stamp:  <2009-06-12 18:50:30 raskolnikov>
 *
 *  @file        text.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 17 21:03:58 2009
 *
 *  Interfaz de la clase text.
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

#ifndef YAGE_TEXT_H_
#define YAGE_TEXT_H_

#include <boost/shared_ptr.hpp>

#include <yage/base/point3.hpp>
#include <yage/gra/font.hpp>
#include <yage/gra/drawable.hpp>

namespace yage
{
namespace gra
{

YAGE_DECLARE_ERROR (base::yage_error, text_error);

class text : public drawable
{
public:
    text (font_ptr font,
	  const std::string& str = "",
	  const base::point3f& color = base::point3f (1, 1, 1),
	  font::render_mode mode = font::BLENDED);

    font::texture_ptr get_texture ();
    void draw ();
    size_t get_width ();
    size_t get_height ();
        
    const std::string& get_text () const
    {
	return m_str;
    }

    void set_text (const std::string& str)
    {
	m_str = str;
	m_need_update = true;
    }

    const base::point3f& get_color () const
    {
	return m_color;
    }

    void set_color (const base::point3f& color)
    {
	m_color = color;
	m_need_update = true;
    }
    
    font::render_mode get_mode () const
    {
	return m_mode;
    }

    void set_mode (font::render_mode mode)
    {
	m_mode = mode;
	m_need_update = true;
    }

    boost::shared_ptr<font> get_font ()
    {
	return m_font;
    }

    void set_font (font_ptr font)
    {
	m_font = font;
	m_need_update = true;
    }

public:
    void update_texture ();
    
    bool m_need_update;
    font_ptr m_font;
    std::string m_str;
    base::point3f m_color;
    font::render_mode m_mode;

    size_t m_real_width;
    size_t m_real_height;
    size_t m_width;
    size_t m_height;
    font::texture_ptr m_tex;
};

typedef boost::shared_ptr<text> text_ptr;

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_TEXT_H_ */
