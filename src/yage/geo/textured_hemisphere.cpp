/**
 *  Time-stamp:  <2009-05-19 12:47:25 raskolnikov>
 *
 *  @file        textured_hemisphere.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Tue May 19 11:06:14 2009
 *
 *  Implementación de la clase textured_hemisphere.
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

#include "textured_hemisphere.hpp"

using namespace yage::base;

namespace yage
{
namespace geo
{

textured_hemisphere::textured_hemisphere (size_t division)
{
    begin (mesh::QUADS);
    for (size_t i = 0; i < division; ++i)
    {	
	for (size_t j = 0; j < division; j++) {
	    point3f pn;
	    
	    point3f p0 (sin (M_PI * (float) j / division) * 
			cos (M_PI * (float) i / division),
			sin (M_PI * (float) j / division) * 
			sin (M_PI * (float) i / division),
			cos (M_PI * (float) j / division));
	    pn = p0.normalize ();
	    point2f t0 (atan2f (pn.x (), pn.z ()) / (M_PI * 2) + 0.5f,
			1 - asinf (pn.y ()) / M_PI + 0.5f);
	    
	    point3f p1 (sin (M_PI * (float) j / division) *
			cos (M_PI * (float) (i+1) /division),
			sin (M_PI * (float) j / division) * 
			sin (M_PI * (float) (i+1) /division),
			cos (M_PI * (float) j / division));
	    pn = p1.normalize ();
	    point2f t1 (atan2f (pn.x (), pn.z ()) / (M_PI * 2) + 0.5f,
			1 - asinf (pn.y ()) / M_PI + 0.5f);
	    
	    point3f p2 (sin (M_PI * (float) (j+1) / division) * 
			cos (M_PI * (float) (i+1) / division),
			sin (M_PI * (float) (j+1) / division) *
			sin (M_PI * (float) (i+1) / division),
			cos (M_PI * (float) (j+1) / division));
	    pn = p2.normalize ();
	    point2f t2 (atan2f (pn.x (), pn.z ()) / (M_PI * 2) + 0.5f,
			1 - asinf (pn.y ()) / M_PI + 0.5f);

			
	    point3f p3 (sin (M_PI * (float) (j+1) / division) *
			cos (M_PI * (float) i / division),
			sin (M_PI * (float) (j+1) / division) *
			sin (M_PI * (float) i / division),
			cos (M_PI * (float) (j+1) / division));
	    pn = p3.normalize ();
	    point2f t3 (atan2f (pn.x (), pn.z ()) / (M_PI * 2) + 0.5f,
			1 - asinf (pn.y ()) / M_PI + 0.5f);

#define FIX_TEX(t0, t1)				\
	    if (t0[0] - t1[0] > 0.8)		\
		t1[0] += 1.0f;			\
	    else if (t1[0] - t0[0] > 0.8)	\
		t0[0] += 1.0f;			\
	    if (t0[1] - t1[1] > 0.8)		\
		t1[1] += 1.0f;			\
	    else if (t1[1] - t0[1] > 0.8)	\
		t0[1] += 1.0f;

	    FIX_TEX(t0, t1);
	    FIX_TEX(t1, t2);
	    FIX_TEX(t2, t3);	    
	    
#undef FIX_TEX
	    
	    tex_coord (t0);
	    point (p0);
	    tex_coord (t1);
	    point (p1);
	    tex_coord (t2);
	    point (p2);
	    tex_coord (t3);
	    point (p3);
	}
    }
    end ();
}

} /* namespace geo */
} /* namespace yage */
