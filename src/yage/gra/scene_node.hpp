/**
 *  @file        scene_node.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 15:01:35 2009
 *
 *  Declaración del tipo scene_node
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

#ifndef YAGE_SCENENODE_H
#define YAGE_SCENENODE_H

#include <list>
#include <string>

#include <boost/shared_ptr.hpp>

#include <yage/base/tree.hpp>
#include <yage/base/point3.hpp>
#include <yage/base/point4.hpp>

#include <yage/gra/drawable.hpp>

namespace yage
{
namespace gra
{

class scene_node : public base::tree_node <scene_node>,
		   public drawable,
		   public YAGE_DEFAULT_THREADING <scene_node>
{
public:
    typedef std::list<drawable_ptr>::iterator drawable_iterator;

    scene_node ();

    drawable_iterator drawable_begin ()
    {
	return m_drawables.begin ();
    }

    drawable_iterator drawable_end ()
    {
	return m_drawables.end ();
    }

    void clear_drawables ()
    {
	m_drawables.clear ();
    }

    template <typename Iterator>
    void add_drawable (Iterator b, Iterator e)
    {
	m_drawables.insert (m_drawables.end (), b, e);
    }

    void add_drawable (drawable_ptr d)
    {
	m_drawables.push_back (d);
    }

    void del_drawable (drawable_ptr d)
    {
	m_drawables.remove(d);
    }

    void set_position (const base::point3f& pos)
    {
	m_position = pos;
    }

    void set_scale (const base::point3f& scale)
    {
	m_scale = scale;
    }

    void set_rotate (const base::point4f& rotate)
    {
	m_rotate = rotate;
    }

    const base::point3f& get_scale () const
    {
	return m_scale;
    }

    const base::point3f& get_position () const
    {
	return m_position;
    }

    base::point3f get_world_position () const
    {
	return get_parent () ?
	    m_position + get_parent ()->get_world_position ():
	    m_position;
    }

    float get_sq_distance (const scene_node& nod) const
    {
	return nod.get_parent () == get_parent () ?
	    (m_position - nod.m_position).sq_length() :
	    (get_world_position () - nod.get_world_position ()).length();
    }

    float get_distance (const scene_node& nod) const
    {
	return nod.get_parent () == get_parent () ?
	    (m_position - nod.m_position).length() :
	    (get_world_position () - nod.get_world_position ()).length();
    }

    void draw ();

private:
    typedef std::list<drawable_ptr> draw_list;

    draw_list     m_drawables;
    base::point3f m_position;
    base::point3f m_scale;
    base::point4f m_rotate;
};

typedef boost::shared_ptr<scene_node> scene_node_ptr;

} /* namespace gra */
} /* namespace yage */

#endif /* YAGE_SCENENODE_H */
