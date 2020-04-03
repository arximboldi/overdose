/**
 *  Time-stamp:  <2009-06-13 20:32:51 raskolnikov>
 *
 *  @file        dope_effect.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri Jun 12 21:14:57 2009
 *
 *  Interfaz de la clase dope_effect.
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

#ifndef DOSE_DOPE_EFFECT_H_
#define DOSE_DOPE_EFFECT_H_

#include <boost/enable_shared_from_this.hpp>
#include <yage/core/task.hpp>
#include <yage/gra/scene_node.hpp>

namespace dose
{

namespace st { class level; }

namespace drug
{

class dope;

class dope_effect : public yage::core::task
		  , public boost::enable_shared_from_this<dope_effect>
{
public:
    typedef boost::shared_ptr<dope> dope_ptr;
    typedef boost::shared_ptr<st::level> level_ptr;

    dope_effect (dope_ptr p);
    ~dope_effect ();
    
    void take ();
    void accumulate (dope_ptr d);
    void update (int delta);
    const std::string& get_name () const;
    void force_finish ();
    
    yage::gra::scene_node& get_node ()
    {
	return m_node;
    }

    dope_ptr get_dope ()
    {
	return m_dope;
    }
    
private:
    dope_ptr m_dope;
    yage::gra::scene_node m_node;
};

typedef boost::shared_ptr<dope_effect> dope_effect_ptr;

} /* namespace drug */
} /* namespace dose */

#endif /* DOSE_DOPE_EFFECT_H_ */
