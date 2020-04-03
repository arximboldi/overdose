/**
 *  Time-stamp:  <2009-05-24 12:05:37 raskolnikov>
 *
 *  @file        entity_observer.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sat May 23 14:55:54 2009
 *
 *  Implementación de utilitarios para observar a las entidades.
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

#ifndef DOSE_PERSON_OBSERVER_H_
#define DOSE_PERSON_OBSERVER_H_

#include <yage/base/observer.hpp>

namespace yage
{
namespace game
{

class entity;

class entity_listener : public yage::base::listener_base
{
public:
    virtual void handle_entity_move (entity& p) = 0;
    virtual void handle_entity_rotate (entity& p) = 0;
};

class entity_subject : public yage::base::subject_base<entity_listener>
{
public:
    typedef sigc::signal1<void, entity&> signal_type;

    signal_type on_entity_move;
    signal_type on_entity_rotate;

    void add_listener (entity_listener& l);
    void del_listener (entity_listener& l);
};

} /* namespace game */
} /* namespace yage */

#endif /* YAGE_ENTITY_OBSERVER_H_ */
