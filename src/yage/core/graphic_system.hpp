/**
 *  @file        graphic_system.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 15 13:15:50 2009
 *
 *  Interfaz de la clase graphic_system.
 *
 *  @todo Sería lo suyo conseguir crear una interfaz común entre ply_model,
 * md2_model y potencialmente otros tipos de modelos para evitar necesitar un
 *        manager diferente para cada uno. Habría que modificar también
 *        file_resource_manager pero sería trivial, bastaría añadir un
 *        registro de factorías por extensiones (file_mgr_node ya soporta
 * busqueda por extensión).
 *
 *  @todo También estaría bien aplicar Pimpl para evitar incluir los tipos
 *        de todos los recursos.
 *
 *  @todo También hay que hacer un font_manager.
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

#ifndef YAGE_GRAPHIC_SYSTEM_H_
#define YAGE_GRAPHIC_SYSTEM_H_

#include <SDL_opengl.h>
#include <algorithm>
#include <boost/utility.hpp>

#include <yage/base/exception.hpp>
#include <yage/core/video_observer.hpp>

#include <yage/core/file_resource_manager.hpp>
#include <yage/core/font_manager.hpp>

#include <yage/gra/geometry.hpp>
#include <yage/gra/material.hpp>
#include <yage/gra/texture.hpp>

namespace yage {

namespace gra {
class scene;
}

namespace core {

typedef resource_manager<std::string, gra::material> material_manager;
typedef file_resource_manager<std::string, gra::texture> texture_manager;
typedef file_resource_manager<std::string,
                              gra::geometry,
                              factory_file_resource_policy<gra::geometry>>
    geometry_manager;

YAGE_DECLARE_ERROR(base::yage_error, graphic_system_error);

class graphic_system
    : public boost::noncopyable
    , public video_listener
{
public:
    enum polygon_mode
    {
        FILL  = GL_FILL,
        LINE  = GL_LINE,
        POINT = GL_POINT,
    };

    enum shading_mode
    {
        FLAT   = GL_FLAT,
        SMOOTH = GL_SMOOTH
    };

    static const int DEFAULT_SCREEN_WIDTH  = 640;
    static const int DEFAULT_SCREEN_HEIGHT = 480;
    static const bool DEFAULT_FULLSCREEN   = false;

    /*
     * The 2D overlay is scaled so that an 800x600 area fits in the
     * window. When the window has another aspect ratio, the overlay
     * extends further along one axis: see get_hud_width ().
     */
    static const int HUD_WIDTH  = 800;
    static const int HUD_HEIGHT = 600;

    ~graphic_system();

    void init(int sc_w  = DEFAULT_SCREEN_WIDTH,
              int sc_h  = DEFAULT_SCREEN_HEIGHT,
              bool fs   = DEFAULT_FULLSCREEN,
              bool grab = false);

    void init(const std::string& title,
              int sc_w  = DEFAULT_SCREEN_WIDTH,
              int sc_h  = DEFAULT_SCREEN_HEIGHT,
              bool fs   = DEFAULT_FULLSCREEN,
              bool grab = false);

    void close();

    void set_polygon_mode(polygon_mode mode = FILL);
    void set_shading_mode(shading_mode mode = SMOOTH);
    void set_clear_color(const base::point4f& col);

    void update();

    bool handle_video_resize(SDL_Event& ev);
    bool handle_video_update(SDL_Event& ev);

    void resize_window(int sc_w  = DEFAULT_SCREEN_WIDTH,
                       int sc_h  = DEFAULT_SCREEN_HEIGHT,
                       bool fs   = DEFAULT_FULLSCREEN,
                       bool grab = false);

    /*
     * Switches between the window and a fullscreen mode at the
     * resolution of the screen. In a browser, the page decides how
     * the game is shown, and this asks it to toggle fullscreen.
     */
    void toggle_fullscreen();

    bool is_init() { return m_isinit; }

    boost::shared_ptr<gra::scene> get_scene() { return m_scene; }

    /*
     * The size of the 2D overlay, which covers the whole window: at
     * least HUD_WIDTH x HUD_HEIGHT, larger along one axis when the
     * window is wider or taller than 4:3. Its origin is the top left
     * corner of the window.
     */
    float get_hud_width() { return m_sc_width / hud_scale(); }

    float get_hud_height() { return m_sc_height / hud_scale(); }

    void set_scene(boost::shared_ptr<gra::scene> scene) { m_scene = scene; }

    texture_manager& textures() { return m_textures; }

    material_manager& materials() { return m_materials; }

    geometry_manager& geometries() { return m_geometries; }

    font_manager& fonts() { return m_fonts; }

private:
    friend class system_impl;

    graphic_system();
    void do_init();
    void set_video_mode();
#ifdef __EMSCRIPTEN__
    void fit_canvas();
#endif

    /* Window pixels per unit of the 2D overlay. */
    float hud_scale()
    {
        return std::min(float(m_sc_width) / HUD_WIDTH,
                        float(m_sc_height) / HUD_HEIGHT);
    }

    int m_sc_width;
    int m_sc_height;
    int m_win_width;
    int m_win_height;
    int m_desktop_width;
    int m_desktop_height;
    bool m_fullsc;
    bool m_grab;
    std::string m_title;
    bool m_isinit;

    boost::shared_ptr<gra::scene> m_scene;

    texture_manager m_textures;
    material_manager m_materials;
    geometry_manager m_geometries;
    font_manager m_fonts;
};

} /* namespace core */
} /* namespace yage */

#endif /* YAGE_GRAPHIC_SYSTEM_H_ */
