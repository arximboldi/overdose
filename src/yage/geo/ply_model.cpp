/*
 *  File:       ply_model.cpp
 *  Author:     Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  Date:       Sun May 10 15:56:36 2009
 *  Time-stamp: <2009-05-22 22:31:51 raskolnikov>
 *
 *  Implementación de los modelos ply.
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

#include <lib/file_ply_stl.h>
#include "ply_model.hpp"

using namespace yage::base;

namespace yage
{
namespace geo
{

YAGE_DEFINE_ERROR_WHERE (ply_model_error, "ply");

ply_model::ply_model (const std::string& fname)
{
    vector<float> vert;
    vector<int> fac;
    
    _file_ply file1;
   
    if (file1.open (fname.c_str ()) ||
	file1.read (vert, fac))
    {
	file1.close ();
	throw ply_model_error (std::string ("Error while loading: ") + fname);
    }
    file1.close ();

    begin (mesh::TRIANGLES);
    for (size_t i = 0; i < fac.size(); i++)
    {
	point (point3f (vert[fac[i]*3],
			vert[fac[i]*3+1],
			vert[fac[i]*3+2]));
    }
    end ();
}

} /* namespace geo */
} /* namespace yage */
