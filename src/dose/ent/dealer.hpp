/**
 *  Time-stamp:  <2009-06-12 18:10:03 raskolnikov>
 *
 *  @file        dealer.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu Jun 11 19:44:50 2009
 *
 *  Interfaz de la clase dealer.
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

#ifndef DOSE_DEALER_H_
#define DOSE_DEALER_H_

#include <dose/ent/pedestrian.hpp>

namespace dose
{

namespace drug { class dope; }

namespace ent
{

class dealer : public pedestrian
{
public:
    static const float PLAYER_DISTANCE = 100.0f;
    
    typedef boost::shared_ptr<drug::dope> dope_ptr;
    
    dealer (const std::string& model,
	    const std::string& texture,
	    bool inverse_normals = false,
	    float walk_speed = DEFAULT_WALK_SPEED,
	    float rotate_speed = DEFAULT_ROTATE_SPEED);

    void update (int delta);
    
    void add_drug (dope_ptr d);

    dope_ptr current_offer ();
    dope_ptr take_shit ();
    bool has_shit () const;
    
private:
    bool player_near ();
    void salute_state (int delta);
    
    std::list<dope_ptr> m_drugs;
};

typedef boost::shared_ptr<dealer> dealer_ptr;

} /* namespace ent */
} /* namespace dose */

#endif /* DOSE_DEALER_H_ */
