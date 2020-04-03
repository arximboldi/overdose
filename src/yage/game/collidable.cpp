/**
 *  Time-stamp:  <2009-05-23 17:45:16 raskolnikov>
 *
 *  @file        collidable.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu May 21 19:08:02 2009
 *
 *  Implementación de los volúmenes de colisión.
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

#include "collidable.hpp"

namespace yage
{
namespace game
{

YAGE_DEFINE_ERROR_WHERE_WHAT (collision_error, "collision",
			      "Undefined collision test.");

namespace
{
class collidable_translator : public boost::static_visitor<void>
{
public:
    collidable_translator (const base::point3f& pos)
	: m_pos (pos)
    {}
    
    void operator () (sphere& col) const
    {
	col.center = col.center + m_pos;
    }
    
    void operator () (capsule& col) const
    {
	col.p1 = col.p1 + m_pos;
	col.p2 = col.p2 + m_pos;
    }
    
    void operator () (aabb& col) const
    {
	col.max = col.max + m_pos;
	col.min = col.min + m_pos;
    }

private:
    base::point3f m_pos;
};
}

void translate_collidable (collidable& col,
			   const base::point3f& pos)
{
    boost::apply_visitor (collidable_translator (pos), col);
}

} /* namespace game */
} /* namespace yage */
