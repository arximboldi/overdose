/**
 *  Time-stamp:  <2009-06-12 18:48:22 raskolnikov>
 *
 *  @file        font.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May 17 20:57:37 2009
 *
 *  Interfaz de la clase font.
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

#ifndef YAGE_FONT_H_
#define YAGE_FONT_H_

#include <SDL/SDL_ttf.h>
#include <string>
#include <boost/shared_ptr.hpp>

#include <yage/base/exception.hpp>
#include <yage/base/point3.hpp>

namespace yage
{
namespace gra
{

class texture;

YAGE_DECLARE_ERROR (base::yage_error, font_error);

class font
{
public:
    typedef boost::shared_ptr<texture> texture_ptr;
    
    enum render_mode
    {
	SOLID,
	SHADED,
	BLENDED
    };
    
    font (const std::string& fname, int ptsize = 12);
    ~font ();

    int get_height () const;
    void get_size (const std::string& text,
		   int& w, int& h) const;

    int get_style () const;
    void set_style (int st);
    bool is_fixed_width () const;

    texture_ptr render (const std::string& str,
			const base::point3f& color,
			render_mode mode);

    SDL_Surface*
    render_surface (const std::string& str,
		    const base::point3f& color,
		    render_mode mode);
    
private:
    mutable TTF_Font* m_font;
};

typedef boost::shared_ptr<font> font_ptr;

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_FONT_H_ */
