/**
 *  @file        resource_manager.tpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Tue May 19 22:09:39 2009
 *
 *  Implementación de la plantilla resource_manager.
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

#ifndef YAGE_RESOURCE_MANAGER_T_
#define YAGE_RESOURCE_MANAGER_T_

#include <yage/core/resource_manager.hpp>

namespace yage
{
namespace core
{

template <class K, class R>
typename resource_manager<K, R>::resource_ptr
resource_manager<K, R>::find (const K& name)
{
    typename resource_map::iterator it = m_resources.find (name);

    if (it != m_resources.end ())
	return it->second;

    return handle_not_found (name);
}

template <class K, class R>
void resource_manager<K, R>::add (const K& name, resource_ptr res)
{
    m_resources [name] = res;
}

template <class K, class R>
void resource_manager<K, R>::del (const K& name)
{
    m_resources.erase (name);
}

template <class K, class R>
void resource_manager<K, R>::clear ()
{
    m_resources.clear ();
}

template <class K, class R>
typename resource_manager<K, R>::resource_ptr
resource_manager<K, R>::handle_not_found (const K& name)
{
    throw resource_manager_error (
	std::string ("Could not find resource."));
}

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_RESOURCE_MANAGER_T_ */
