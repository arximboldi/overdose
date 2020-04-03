/**
 *  @file        resource_manager.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Mon May 18 19:15:07 2009
 *
 *  Interfaz de la clase resource_manager.
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

#ifndef YAGE_RESOURCE_MANAGER_H_
#define YAGE_RESOURCE_MANAGER_H_

#include <map>
#include <boost/shared_ptr.hpp>

#include <yage/base/exception.hpp>

namespace yage
{
namespace core
{

YAGE_DECLARE_ERROR (base::yage_error, resource_manager_error);

template<class Key, class Resource>
class resource_manager
{
public:
    typedef boost::shared_ptr<Resource> resource_ptr;

    resource_ptr find (const Key& name);
    void add (const Key& name, resource_ptr res);
    void del (const Key& name);
    void clear ();

protected:
    virtual resource_ptr handle_not_found (const Key& name);

private:
    typedef std::map<Key, resource_ptr> resource_map;
    resource_map m_resources;
};

} /* namespace core */
} /* namespace yage */

#include <yage/core/resource_manager.tpp>

#endif /* YAGE_RESOURCE_MANAGER_H_ */
