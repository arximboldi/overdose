/**
 *  @file        tester.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Fri May 22 17:01:17 2009
 *
 *  Implementación de la clase tester.
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

#include "tester.hpp"

using namespace yage;

namespace dose
{
namespace st
{

tester::tester ()
{
    yage::core::graphic_system& graphic = yage::core::system::self ().graphic ();

    get_keys ().add_listener (*this);
    get_mouse ().add_listener (*this);

    boost::shared_ptr<geo::mesh> sky (new geo::textured_hemisphere);
    sky->set_texture (graphic.textures ().find ("sky_mid.png"));
    get_scene ()->set_sky (sky);

    std::cout << "test 2.1\n";
    m_model = boost::dynamic_pointer_cast<geo::md2_model> (
	graphic.geometries ().find ("civi.md2"));
    m_light.reset (new gra::light);
    m_camera.reset (new gra::camera);
    //m_model.reset (new geo::textured_plane);
    m_text.reset (new gra::text (graphic.fonts ().find ("DejaVuSans.ttf", 16),
				 "Texto de prueba."));

    m_light->enable ();
    m_model->set_material (
	boost::shared_ptr<gra::material> (
	    new gra::material (
		base::point4f (0.5, 0.5, 0.5, 1),
		base::point4f (1, 1, 1, 1),
		base::point4f (1, 1, 1, 1)
		)));

    get_scene ()->get_hud_root ().get_child ("text").add_drawable (m_text);
    get_scene ()->get_hud_root ().get_child ("text").set_position (base::point3f (50, 50, 0));
    get_scene ()->get_root ().get_child ("model").add_drawable (m_model);
    get_scene ()->get_root ().get_child ("light").add_drawable (m_light);
    get_scene ()->get_root ().get_child ("light").set_position (base::point3f (-100, -100, -100));
    m_light->set_diffuse (base::point4f (0.75, 0.75, 0.5, 1));
    m_light->set_ambient (base::point4f (0.5, 0.5, 0.5, 1));
    m_light->set_specular (base::point4f (1, 1, 1, 1));

#if 0
    std::cout << "test 3\n";
    std::copy (m_model->anims_begin (), m_model->anims_end (),
	       std::ostream_iterator<std::string> (std::cout, "\n"));
    std::cout << "----\n";
    std::copy (m_model->skins_begin (), m_model->skins_end (),
	       std::ostream_iterator<std::string> (std::cout, "\n"));
#endif
    m_model->set_animation ("attack");

    m_model->set_texture (graphic.textures ().find ("civi.tga"));

    m_camera->set_position (base::point3f (0, 0, 10));
    //m_camera->set_plane_normal (base::point3f (0, 0, -1));
    m_camera->look_at (base::point3f (0, 0, 0));

    get_scene ()->set_camera (m_camera);

    m_rad = 60;
    m_angle = 0;
    m_angle2 = 0;

    boost::shared_ptr<gra::fog> fog (new gra::fog ());
    fog->set_color (base::point4f (0.5, 0.5, 0.5, 1));
    fog->set_end (100);
    fog->set_mode (gra::fog::LINEAR);
    fog->set_start (60);
    fog->set_density (0.35);
    get_scene ()->set_fog (fog);

    m_camera->set_position (base::point3f (m_rad * cos (m_angle), 0, m_rad * sin (m_angle)));
    m_camera->look_at (base::point3f ());

    core::system::self ().tasks ().add (
	boost::shared_ptr<core::task> (new gra::animation_task (m_model,
								0.001,
								true)));
}

bool tester::handle_key_press (SDL_Event& ev)
{
    switch (ev.key.keysym.sym)
    {
    case SDLK_a:
	m_angle -= 0.1;
	m_text->set_text ("Tecla a");
	break;
    case SDLK_d:
	m_angle += 0.1;
	m_text->set_text ("Tecla b");
	break;
    case SDLK_w:
	m_text->set_text ("P");
	m_angle2 += 0.1;
	break;
    case SDLK_s:
	m_text->set_text ("Erase una vez un niño al que le gustaba cantar saetas.");
	m_angle2 -= 0.1;
    default:
	break;
    }
    m_camera->set_position (base::point3f (m_rad * cos (m_angle) * cos (m_angle2),
					   m_rad * sin (m_angle2),
					   m_rad * sin (m_angle) * cos (m_angle2)));
    m_camera->look_at (base::point3f ());

    return false;
}


} /* namespace st */
} /* namespace dose */
