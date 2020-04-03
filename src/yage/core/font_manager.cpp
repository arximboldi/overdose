/**
 *  Time-stamp:  <2009-05-20 12:03:52 raskolnikov>
 *
 *  @file        font_manager.tpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Wed May 20 11:35:30 2009
 *
 *  Implementación de la clase font_manager.
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

#include "font_manager.hpp"

namespace yage
{
namespace core
{

boost::shared_ptr<gra::font>
font_manager::find (const std::string& font_name, int font_size)
{
    return super::find (
	font_manager_policy::key_type (font_name, font_size));
}

std::string font_manager_policy::file_name (const key_type& key)
{
    return key.first;
}

boost::shared_ptr<gra::font>
font_manager_policy::load_resource (const std::string& path,
				    const key_type& key)
{
    return boost::shared_ptr<gra::font> (new gra::font (path, key.second));
}

} /* namespace core */
} /* namespace yage */

