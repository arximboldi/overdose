/**
 *  Time-stamp:  <2009-06-15 16:50:17 raskolnikov>
 *
 *  @file        player_hud.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu Jun 11 23:41:08 2009
 *
 *  Interfaz de la clase player_hud.
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

#ifndef DOSE_PLAYER_HUD_H_
#define DOSE_PLAYER_HUD_H_

#include <boost/shared_ptr.hpp>
#include <yage/gra/scene_node.hpp>
#include <yage/gra/text.hpp>
#include <dose/drug/dope_effect.hpp>

namespace dose
{

namespace drug { class dope; }
namespace st { class level; }

namespace ent
{

class player_hud
{
public:
    static const int MAX_DRUG = 6;
    static const int ALERT_DURATION = 3000;
    static const float DRUG_SCALE = 10;
    
    typedef boost::shared_ptr<drug::dope> dope_ptr;
    typedef boost::shared_ptr<st::level> level_ptr;
    
    player_hud ();
    virtual ~player_hud ();

    void set_psychodelia (float psychodelia);
    void set_ecstasy (float ecstasy);
    void set_euphoria (float euphoria);

    void apply_drug (dope_ptr dope);
    dope_ptr take_drug ();
    void finish_drugs ();
    
    void add_drug (dope_ptr p);
    void select_prev ();
    void select_next ();
    void change_selected (int new_sel);
    void clear_drugs ();
    
    void set_player_message (const std::string& str);
    void set_player_alert (const std::string& str, int duration = ALERT_DURATION);

    void update (int delta);
    
    float get_psychodelia () const
    {
	return m_psychodelia;
    }

    float get_ecstasy () const
    {
	return m_ecstasy;
    }
    
    float get_euphoria () const
    {
	return m_euphoria;
    }
    
    yage::gra::scene_node& get_node ()
    {
	return m_node;
    }

    bool empty () const
    {
	return m_drugs.empty ();
    }

    bool full () const
    {
	return m_drugs.size () >= 5;
    }

private:
    typedef std::vector<dope_ptr> dope_list;
    typedef std::list<boost::weak_ptr<drug::dope_effect> > effect_list;
	
    yage::gra::scene_node& get_slot (int i);
    void clean_effects ();
    
    float m_psychodelia;
    float m_ecstasy;
    float m_euphoria;

    yage::gra::drawable_ptr m_selected_bg;
    yage::gra::text_ptr m_player_msg;
    yage::gra::text_ptr m_player_alert;
    int m_alert_count;

    effect_list m_effects;
    
    dope_list m_drugs;
    int m_selected;
    yage::gra::scene_node m_node;
};

} /* namespace ent */
} /* namespace dose */

#endif /* DOSE_PLAYER_HUD_H_ */
