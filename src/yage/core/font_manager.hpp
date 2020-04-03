/**
 *  Time-stamp:  <2009-05-20 12:22:44 raskolnikov>
 *
 *  @file        font_manager.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Wed May 20 11:17:18 2009
 *
 *  Interfaz de la clase font_manager.
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

#ifndef YAGE_FONT_MANAGER_H_
#define YAGE_FONT_MANAGER_H_

#include <yage/core/file_resource_manager.hpp>
#include <yage/gra/font.hpp>

namespace yage
{
namespace core
{

class font_manager_policy
{
public:
    typedef std::pair<std::string, int> key_type;

    std::string file_name (const key_type& key);

    boost::shared_ptr<gra::font>
    load_resource (const std::string& path, const key_type& key);
};

class font_manager : public file_resource_manager<std::pair<std::string, int>,
						  gra::font,
						  font_manager_policy>
{
public:
    boost::shared_ptr<gra::font>
    find (const std::string& font_name, int font_size);
};

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_FONT_MANAGER_H_ */
