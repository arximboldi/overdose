/**
 *  Time-stamp:  <2009-06-15 23:21:38 raskolnikov>
 *
 *  @file        yage_app.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Mon May 18 17:55:20 2009
 *
 *  Implementación de la clase yage_app.
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

#include "yage/base/conf_backend_xml.hpp"
#include "yage/base/option_conf.hpp"
#include "yage/base/arg_parser.hpp"
#include "yage/base/logger.hpp"
#include "yage/base/file_manager.hpp"

/* TODO limpiar */
#include "yage/core/system.hpp"
#include "yage/core/task_manager.hpp"

#include "yage_app.hpp"
#include "graphic_controller.hpp"

using namespace std;
namespace bf = boost::filesystem;

namespace yage
{
namespace app
{

yage_app::yage_app (const std::string& name,
		    const std::string& version,
		    const std::string& description,
		    const std::string& copyright_date,
		    const std::string& author)
    : m_name (name)
    , m_version (version)
    , m_description (description)
    , m_copyright_date (copyright_date)
    , m_author (author)
    , m_config (base::config::self ().get_child ("yage"))
{}

void yage_app::load_config ()
{
    try
    {
	base::config::self ().attach_backend (
	    new base::conf_backend_xml (
		(get_config_path () / "config.xml").string ()));
	
	base::config::self ().def_load ();
    }
    catch (base::yage_error& e)
    {
	e.log ();
    }
}

void yage_app::store_config ()
{
    try
    {
	base::config::self ().save ();
    }	
    catch (base::yage_error& e)
    {
	e.log ();
    }
}

int yage_app::run (int argc, const char* argv [])
{
    int ret = 0;
	
    base::logger::self ().attach_sink (new base::log_std_sink);
    
    try
    {
	generate_paths ();

	ret = parse_args (argc, argv);
	if (!ret) {
 	    load_config ();
	    graphic_controller ctrl (m_config.get_child ("graphic"));
	    ctrl.init (m_name + " " + m_version);
	
	    ret = execute ();
	    store_config ();
	}
    }
    catch (base::error& err)
    {
	err.log ();
	ret = 1;
    }
#if 1
    catch (std::exception& err)
    {
	base::logger::self ()
	    (base::log::error,
	     std::string ("Uncaught exception: ") + err.what ());
	ret = 1;
    }
    catch (...)
    {
	base::logger::self ()
	    (base::log::error, "Uncaught unknown exception.");
	ret = 1;
    }
#endif
    
    /* TODO: mover esto a otra parte */
    core::system::self ().tasks ().clear ();
    core::system::self ().clear_resources ();

    return ret;
}

int yage_app::parse_args (int argc, const char* argv [])
{
    base::arg_parser args;

    bool arg_show_help           = false;
    bool arg_show_version        = false;
    base::option* arg_width      = new base::option_conf<int> (
	m_config.get_path ("graphic.window.width"));
    base::option* arg_height     = new base::option_conf<int> (
	m_config.get_path ("graphic.window.height"));
    base::option* arg_fullscreen = new base::option_conf_value<int> (
	1, m_config.get_path ("graphic.window.fullscreen"));
    base::option* arg_windowed   = new base::option_conf_value<int> (
	0, m_config.get_path ("graphic.window.fullscreen"));
    base::option* arg_grab = new base::option_conf_value<int> (
	1, m_config.get_path ("graphic.window.grab"));
    base::option* arg_no_grab = new base::option_conf_value<int> (
	0, m_config.get_path ("graphic.window.grab"));
    base::option* arg_fps        = new base::option_conf<int> (
	m_config.get_path ("graphic.fps"));
    
    prepare (args);

    args.add ('h', "help",       &arg_show_help);
    args.add ('v', "version",    &arg_show_version);
    args.add ('W', "width",      arg_width);
    args.add ('H', "height",     arg_height);
    args.add ('f', "fullscreen", arg_fullscreen);
    args.add ('w', "windowed",   arg_windowed);
    args.add ('g', "grab",       arg_grab);
    args.add ('n', "no-grab",    arg_no_grab);
    args.add ('F', "fps",        arg_fps);

    args.parse (argc, argv);

    if (arg_show_help)
    {
	print_help (cout);
	return 255;
    }

    if (arg_show_version)
    {
	print_version (cout);
	return 255;
    }
    
    return 0;
}

void yage_app::generate_paths ()
{
#ifdef WIN32
    m_cfg_dir = ".";
#else
    bf::path home_dir = getenv  ("HOME");
    m_cfg_dir = home_dir / (std::string (".") + m_name);

    if (!bf::exists (m_cfg_dir))
	bf::create_directory (m_cfg_dir);
#endif

    /* TODO:
       - YAGE_DATA_DIR no debería apuntar al directorio concreto de overdose.
       - Mover la estructura de ficheros de overdose fuera de la biblioteca. */
    m_data_dir = YAGE_DATA_DIR;
    base::file_manager::self ().get_path ("yage").add_path (m_data_dir);
    base::file_manager::self ().get_path ("yage.tex").add_path (m_data_dir / "tex");
    base::file_manager::self ().get_path ("yage.tex").add_path (m_data_dir / "tex" / "player");
    base::file_manager::self ().get_path ("yage.tex").add_path (m_data_dir / "tex" / "object");
    base::file_manager::self ().get_path ("yage.tex").add_path (m_data_dir / "tex" / "scene");
    base::file_manager::self ().get_path ("yage.tex").add_path (m_data_dir / "tex" / "hud");
    base::file_manager::self ().get_path ("yage.md2").add_path (m_data_dir / "md2");
    base::file_manager::self ().get_path ("yage.md2").add_path (m_data_dir / "md2" / "player");
    base::file_manager::self ().get_path ("yage.md2").add_path (m_data_dir / "md2" / "object");
    base::file_manager::self ().get_path ("yage.ply").add_path (m_data_dir / "ply");
    base::file_manager::self ().get_path ("yage.font").add_path (m_data_dir / "font");
}

void yage_app::print_help (std::ostream& out)
{
    out << m_description << endl << endl
	<< "Usage: " << m_name << " [options]\n"
	"\nOptions:\n";
    print_base_options (out);
}

void yage_app::print_base_options (std::ostream& out)
{
    out <<
	"  -h, --help                 Display this information.\n"
	"  -v, --version              Display program version.\n"
	"  -W, --width <value>        Set the screen width.\n"
	"  -H, --height <value>       Set the screen height.\n"
	"  -f, --fullscreen           Toogle fullscreen mode on.\n"
	"  -w, --windowed             Toogle fullscreen mode off.\n"
	"  -F, --fps <value>          Change FPS limit.\n"
	"  -g, --grab                 Grab controls in window.\n"
	"  -n, --no-grab              Do no grab controls in window.\n";
}

void yage_app::print_version (std::ostream& out)
{
    out << m_name << " "
	<< m_version << endl << "Copyright (C) "
	<< m_copyright_date << " "
	<< m_author << endl
	<<
	"This is free software; see the source for copying conditions.  There is NO\n"
	"warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
	"\nWritten by "
	<< m_author
	<< endl;
}

} /* namespace app */
} /* namespace yage */
