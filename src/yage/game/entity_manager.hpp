/**
 *  @file        entity_manager.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Sun May  3 12:18:32 2009
 *
 *  Declaracion del gestor de entidades.
 */

#ifndef YAGE_ENTITY_MANAGER_H_
#define YAGE_ENTITY_MANAGER_H_

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <yage/core/task.hpp>
#include <yage/game/collidable.hpp>

namespace yage
{
namespace game
{

class entity;

class entity_manager : public core::task
		     , public boost::enable_shared_from_this<entity_manager>
{
public:
    typedef boost::shared_ptr<entity> entity_ptr;

    typedef std::list <entity_ptr> entity_list;
    typedef entity_list::iterator iterator;

    ~entity_manager ();
    void add_entity (entity_ptr ent);
    void update (int delta_ticks);
    void find_collisions (entity_list& list, const collidable& who);
    bool find_collisions (const collidable& who);
    bool find_dynamic_static_collisions (const collidable& who,
					 const base::point3f& move);

    void clear ();

    iterator dynamic_begin ()
    {
	return m_dynamic.begin ();
    }

    iterator dynamic_end ()
    {
	return m_dynamic.end ();
    }

private:
    void check_collision (entity& a, entity& b, const base::point3f& move);

    std::list <entity_ptr> m_dynamic;
    std::list <entity_ptr> m_static;
};

typedef boost::shared_ptr<entity_manager> entity_manager_ptr;

} /* namespace game */
} /* namespace yage */

#endif /* YAGE_ENTITYMANAGER */
