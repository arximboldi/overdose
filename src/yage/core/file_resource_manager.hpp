/**
 *  Time-stamp:  <2020-04-03 17:02:58 raskolnikov>
 *
 *  @file        file_resource_manager.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Tue May 19 22:10:55 2009
 *
 *  Interfaz de la clase file_resource_manager.
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

#ifndef YAGE_FILE_RESOURCE_MANAGER_H_
#define YAGE_FILE_RESOURCE_MANAGER_H_

#include <yage/base/file_manager.hpp>
#include <yage/base/exception.hpp>
#include <yage/core/resource_manager.hpp>

namespace yage
{
namespace core
{

YAGE_DECLARE_ERROR (base::yage_error, file_resource_manager_error);

template <class Key, class Resource>
class default_file_resource_policy
{
public:
    std::string file_name (const Key& k);

    boost::shared_ptr<Resource>
    load_resource (const std::string& path, const Key& key);
};

template <class Key,
	  class Resource,
	  class FilePolicy = default_file_resource_policy<Key, Resource> >
class file_resource_manager : public resource_manager<Key, Resource>
{
public:
    file_resource_manager (base::file_mgr_node* mgr = 0);
    void set_file_manager (base::file_mgr_node* mgr);
    base::file_mgr_node* get_file_manager ();

    FilePolicy& get_policy ()
    {
	return m_policy;
    }

protected:
    typedef resource_manager<Key, Resource> super;

    virtual boost::shared_ptr<Resource> handle_not_found (const Key& str);

private:
    base::file_mgr_node* m_file_mgr;
    FilePolicy m_policy;
};

template <class Resource>
class file_resource_factory
{
public:
    virtual ~file_resource_factory() = default;
    virtual Resource* create (const std::string& path) = 0;
};

template <class Concrete, class Resource>
class concrete_file_resource_factory : public file_resource_factory<Resource>
{
public:
    virtual Concrete* create (const std::string& path);
};

template <class Resource>
class factory_file_resource_policy
{
public:
    std::string file_name (const std::string& k)
    {
	return k;
    }

    ~factory_file_resource_policy ();

    void attach_resource_factory (const std::string& ext,
				  file_resource_factory<Resource>* factory);

    template <class Concrete>
    void attach_default_factory (const std::string& ext);

    boost::shared_ptr<Resource>
    load_resource (const std::string& path, const std::string& key);

private:
    typedef std::map <std::string, file_resource_factory<Resource>*> factory_map;
    factory_map m_factory;
};

} /* namespace core */
} /* namespace yage */

#include <yage/core/file_resource_manager.tpp>

#endif /* YAGE_FILE_RESOURCE_MANAGER_H_ */
