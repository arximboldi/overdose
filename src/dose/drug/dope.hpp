/**
 *  Time-stamp:  <2020-04-03 16:03:15 raskolnikov>
 *
 *  @file        dope.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Thu Jun 11 19:05:24 2009
 *
 *  Interfaz de la clase dope.
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

#ifndef DOSE_DOPE_H_
#define DOSE_DOPE_H_

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <yage/gra/texture.hpp>

namespace dose
{

namespace st { class level; }

namespace drug
{

class dope
{
public:
    static constexpr float DEFAULT_DOPE_SPEED = 0.00003;

    typedef boost::shared_ptr<st::level> level_ptr;
    typedef boost::shared_ptr<dope> dope_ptr;

    dope (const std::string& name,
	  const std::string& tex,
	  float psychodelia,
	  float ecstasy,
	  float euphoria,
	  float progress = 1.0f,
	  float speed = DEFAULT_DOPE_SPEED);

    virtual ~dope () {}

    virtual void take () = 0;
    virtual void accumulate (dope_ptr d) = 0;
    virtual void handle_finish () = 0;

    void update (int delta);

    float get_progress () const
    {
	return m_progress;
    }

    void set_progress (float progress)
    {
	m_progress = progress;
    }

    const std::string& get_name () const
    {
	return m_name;
    }

    yage::gra::texture_ptr get_texture ()
    {
	return m_texture;
    }

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

    level_ptr get_level ()
    {
	return level_ptr (m_level);
    }

    void set_level (boost::weak_ptr<st::level> level)
    {
	m_level = level;
    }

private:
    boost::weak_ptr<st::level> m_level;
    std::string m_name;
    yage::gra::texture_ptr m_texture;
    float m_psychodelia;
    float m_ecstasy;
    float m_euphoria;
    float m_progress;
    float m_speed;
};

typedef boost::shared_ptr<dope> dope_ptr;

} /* namespace drug */
} /* namespace dose */

#endif /* DOSE_DOPE_H_ */
