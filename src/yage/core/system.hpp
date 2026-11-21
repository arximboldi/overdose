
#ifndef YAGE_SYSTEM_H
#define YAGE_SYSTEM_H

#include <string>

#include <yage/base/exception.hpp>
#include <yage/base/singleton.hpp>

#include <yage/core/graphic_system.hpp>
#include <yage/core/input_system.hpp>
#include <yage/core/sound_system.hpp>
#include <yage/core/timer.hpp>

namespace yage {

namespace gra {
class camera;
}

namespace core {

YAGE_DECLARE_ERROR(base::yage_error, system_error);

class task_manager;

/**
 * @todo Mejorar la implementación de singleton para evitar los
 * problemas con el orden de destrucción de la SDL.
 */
class system_impl
{
public:
    system_impl();

    void main_loop();
    void clear_resources();

    graphic_system& graphic() { return m_graphic; }

    sound_system& sound() { return m_sound; }

    input_system& input() { return m_input; }

    task_manager& tasks() { return *m_tasks; }

    void force_fps(int rate)
    {
        m_fps        = rate;
        m_update_fps = true;
    }

    void quit_loop() { m_must_quit = true; }

private:
    /** Runs one frame. Returns false when the loop has to stop. */
    bool iterate();
    void finish_loop();
#ifdef __EMSCRIPTEN__
    static void browser_frame(void* self);
#endif

    boost::shared_ptr<task_manager> m_tasks;
    timer m_timer;

    graphic_system m_graphic;
    sound_system m_sound;
    input_system m_input;

    int m_fps;
    bool m_update_fps;
    bool m_must_quit;
};

typedef base::singleton_holder<system_impl> system;

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_SYSTEM_H */
