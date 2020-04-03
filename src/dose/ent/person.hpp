/**
 *  @file        person.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sat May 23 14:34:53 2009
 *
 *  Interfaz de la clase person.
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

#ifndef DOSE_PERSON_H_
#define DOSE_PERSON_H_

#include <yage/game/entity.hpp>
#include <yage/geo/md2_model.hpp>
#include <yage/gra/animation_task.hpp>

namespace dose
{

namespace st { class level; }

namespace ent
{

class person : public yage::game::entity
{
public:
    typedef boost::shared_ptr<st::level> level_ptr;

    enum action
    {
	RUN_FW   = 1,
	RUN_BW   = 1 << 1,
	RUN_L    = 1 << 2,
	RUN_R    = 1 << 3,
	ROTATE_L = 1 << 4,
	ROTATE_R = 1 << 5
    };

#if 1
    static constexpr float DEFAULT_WALK_SPEED = 0.2;
    static constexpr float DEFAULT_ROTATE_SPEED = 0.003;
#else
    static constexpr float DEFAULT_WALK_SPEED = 0.4;
    static constexpr float DEFAULT_ROTATE_SPEED = 0.004;
#endif

    static yage::geo::md2_model_ptr
    load_model (const std::string& tris,
		const std::string& tex,
		bool inverse_normals = false);

    person (const std::string& model,
	    const std::string& texture,
	    const bool inverse_normals = false,
	    float walk_speed = DEFAULT_WALK_SPEED,
	    float rotate_speed = DEFAULT_ROTATE_SPEED);

    ~person ();

    void update (int);
    void handle_collision (yage::game::entity& ent,
			   yage::game::collidable& box,
			   yage::game::dynamic_collision& col);

    void activate_action (int action);
    void deactivate_action (int action);
    void set_action (int action);
    void toggle_action (int action);

    void play (const std::string& anim, float speed = 1.0f);
    void jump ();
    void finish_animation ();
    bool is_blocked ();

    void alternate_model (yage::geo::md2_model_ptr m);
    void restore_model ();

    void set_look_angle (float angle);

    bool has_action (int action)
    {
	return m_action & action;
    }

    yage::base::point3f get_orientation ()
    {
	return m_dir;
    }

    int get_action ()
    {
	return m_action;
    }

    float get_look_angle () const
    {
	return m_angle;
    }

    void set_level (boost::weak_ptr<st::level> lvl)
    {
	m_level = lvl;
    }

    level_ptr get_level ()
    {
	return level_ptr (m_level);
    }

    float get_rotate_speed () const
    {
	return m_rotate_speed;
    }

    float get_walk_speed () const
    {
	return m_walk_speed;
    }

    void set_rotate_speed (float speed)
    {
	m_rotate_speed = speed;
    }

    void set_walk_speed (float speed)
    {
	m_walk_speed = speed;
    }

    yage::gra::animation_task_ptr get_animation_task ()
    {
	return yage::gra::animation_task_ptr (m_anim);
    }

protected:
    void set_animation (const std::string& name, float speed = 1.0f, bool force = false);

private:
    boost::weak_ptr<st::level> m_level;

    float m_walk_speed;
    float m_rotate_speed;
    bool  m_wait;

    boost::weak_ptr<yage::gra::animation_task> m_anim;

    yage::geo::md2_model_ptr m_real_model;
    yage::geo::md2_model_ptr m_model;

    yage::base::point3f m_dir;
    float m_angle;

    int m_action;
};

typedef boost::shared_ptr<person> person_ptr;

} /* namespace ent */
} /* namespace dose */

#endif /* DOSE_PERSON_H_ */
