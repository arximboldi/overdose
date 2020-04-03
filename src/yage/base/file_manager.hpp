/**
 *  @file        file_manager.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        2008
 *
 *  Hierarchical file management system. Interface.
 */

/*
 *  Copyright (C) 2008, 2009 Juan Pedro Bolívar Puente
 *
 *  This file is part of Psychosynth.
 *
 *  Psychosynth is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Psychosynth is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef YAGE_FILEMANAGER_H
#define YAGE_FILEMANAGER_H

#include <yage/base/file_finder.hpp>
#include <yage/base/tree.hpp>
#include <yage/base/singleton.hpp>

namespace yage
{
namespace base
{

/**
 * @note This class is thread-safe.
 *
 * @todo Make thread-safety optional?
 * @todo Document.
 */
class file_mgr_node : public file_finder,
		      public tree_node <file_mgr_node>,
		      public YAGE_DEFAULT_THREADING <file_mgr_node>,
		      public non_copyable
{
    friend class tree_node <file_mgr_node>;

public:
    template <class PathPredicate>
    void find_if_all (PathPredicate pred,
		      file_finder::path_list& res) const;

    boost::filesystem::path
    find_all (const boost::filesystem::path& file) const;
};

template<class StringPredicate>
void file_mgr_node::find_if_all (StringPredicate pred,
				 file_finder::path_list& res) const
{
    lock lock (this);
    const_iterator it;

    res = find_if (pred, res);

    for (it = begin(); it != end(); ++it)
      it->find_if_all (pred, res);
}

typedef singleton_holder<file_mgr_node> file_manager;

} /* namespace base */
} /* namespace yage */

#endif /* YAGE_FILEMANAGER_H */
