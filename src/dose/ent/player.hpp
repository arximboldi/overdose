/**
 *  @file        player.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu Jun 11 23:08:09 2009
 *
 *  Interfaz de la clase player.
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

#ifndef DOSE_PLAYER_H_
#define DOSE_PLAYER_H_

#include <dose/ent/person.hpp>
#include <dose/ent/player_hud.hpp>

namespace dose
{
namespace ent
{

class dealer;

class player : public person
{
public:
    typedef boost::shared_ptr<dealer> dealer_ptr;

    player (const std::string& model,
	    const std::string& texture,
	    bool inverse_normals = false,
	    float walk_speed = DEFAULT_WALK_SPEED,
	    float rotate_speed = DEFAULT_ROTATE_SPEED);

    void update (int delta);

    player_hud& get_hud ()
    {
	return m_hud;
    }

    void buy_some_shit ()
    {
	m_buy_shit = true;
    }

    void set_god (bool god)
    {
	m_god = god;
    }

    bool is_dead ()
    {
	return m_dead;
    }

    void kill ();

    void take_some_shit ();
    void start_adrenaline ();
    void finish_adrenaline ();
    void handle_police ();

private:
    void manage_dealer (dealer_ptr p);

    bool m_dead;
    bool m_god;
    bool m_on_adrenaline;
    bool m_buy_shit;
    player_hud m_hud;
};

typedef boost::shared_ptr<player> player_ptr;

} /* namespace ent */
} /* namespace dose */

#endif /* DOSE_PLAYER_H_ */
