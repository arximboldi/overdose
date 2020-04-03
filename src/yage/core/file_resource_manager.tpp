/**
 *  Time-stamp:  <2009-05-20 13:16:39 raskolnikov>
 *
 *  @file        file_resource_manager.tpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Tue May 19 22:14:32 2009
 *
 *  Implementación de la plantilal file_resource_manager.
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

#ifndef YAGE_FILE_RESOURCE_MANAGER_T_
#define YAGE_FILE_RESOURCE_MANAGER_T_

#include <boost/filesystem.hpp>
#include <yage/base/misc.hpp>
#include <yage/base/iterator.hpp>
#include <yage/core/file_resource_manager.hpp>

namespace yage
{
namespace core
{

template <class K, class R>
std::string default_file_resource_policy<K, R>::file_name (const K& k)
{
    return k;
}

template <class K, class R>
boost::shared_ptr<R>
default_file_resource_policy<K, R>::load_resource (const std::string& path,
						   const K& key)
{
    return boost::shared_ptr<R> (new R (path));
}

template <class K, class R, class P>
file_resource_manager<K, R, P>::file_resource_manager (base::file_mgr_node* mgr)
    : m_file_mgr (mgr)
{
}

template <class K, class R, class P>
void file_resource_manager<K, R, P>::set_file_manager (base::file_mgr_node* mgr)
{
    m_file_mgr = mgr;
}

template <class K, class R, class P>
base::file_mgr_node* file_resource_manager<K, R, P>::get_file_manager ()
{
    return m_file_mgr;
}

template <class K, class R, class P>
typename boost::shared_ptr<R>
file_resource_manager<K, R, P>::handle_not_found (const K& key)
{
    if (!m_file_mgr)
	throw file_resource_manager_error ("No file manager associated.");

    std::string fname            = m_policy.file_name (key);
    boost::filesystem::path file = m_file_mgr->find_all (fname);

    if (file.empty ())
	throw file_resource_manager_error ("Resource not found. " + fname);

    boost::shared_ptr<R> res = m_policy.load_resource (file.string (), key);
    super::add (key, res);

    return res;
}

template <class R>
boost::shared_ptr<R>
factory_file_resource_policy<R>::load_resource (const std::string& path,
						const std::string& key)
{
    std::string ext (base::get_extension (key.c_str ()));

    typename factory_map::iterator it = m_factory.find (ext);

    if (it == m_factory.end ())
	throw file_resource_manager_error (
	    std::string ("Unknown loader for extension: ") + ext);
    
    file_resource_factory<R>* factory = it->second;
    return boost::shared_ptr<R> (factory->create (path));
}

template <class R>
factory_file_resource_policy<R>::~factory_file_resource_policy ()
{
    base::map_iterator <std::string, file_resource_factory<R>*> iter;
    
    for (iter = m_factory.begin (); iter != m_factory.end (); ++iter)
	delete *iter;
}

template <class R>
void factory_file_resource_policy<R>::attach_resource_factory (
    const std::string& ext,
    file_resource_factory<R>* factory)
{
    base::map_iterator <std::string, file_resource_factory<R>*> iter;

    iter = m_factory.find (ext);
    if (iter != m_factory.end ())
	delete *iter;
    m_factory [ext] = factory;
}

template <class R>
template <class C>
void factory_file_resource_policy<R>::attach_default_factory (const std::string& ext)
{
    attach_resource_factory (ext, new concrete_file_resource_factory<C, R>);
}

template <class C, class R>
C* concrete_file_resource_factory<C, R>::create (const std::string& path)
{
    return new C (path);
}

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_FILE_RESOURCE_MANAGER_T_ */
