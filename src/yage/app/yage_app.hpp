/**
 *  Time-stamp:  <2009-06-15 10:13:04 raskolnikov>
 *
 *  @file        yage_app.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Mon May 18 17:49:26 2009
 *
 *  Interfaz de la clase yage_app.
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

#ifndef YAGE_YAGE_APP_H_
#define YAGE_YAGE_APP_H_

#include <boost/filesystem.hpp>
#include <yage/base/arg_parser.hpp>
#include <yage/base/util.hpp>
#include <yage/base/config.hpp>

namespace yage
{
namespace app
{

class yage_app : public base::non_copyable
{
public:
    virtual ~yage_app () {}
    
    yage_app (const std::string& name,
	      const std::string& version,
	      const std::string& description,
	      const std::string& copyright_date,
	      const std::string& author);
    
    int run (int argc, const char* argv []);
    
    boost::filesystem::path get_config_path ()
    {
	return m_cfg_dir;
    }
    
    boost::filesystem::path get_data_path ()
    {
	return m_data_dir;
    }
    
protected:
    virtual void prepare (base::arg_parser& args) = 0;
    virtual int execute () = 0;

    virtual void print_help (std::ostream& out);
    virtual void print_version (std::ostream& out);
    
private:
    int parse_args (int argc, const char* argv []);
    void generate_paths ();
    void print_base_options (std::ostream& out);
    void load_config ();
    void store_config ();
    
    std::string m_name;
    std::string m_version;
    std::string m_description;
    std::string m_copyright_date;
    std::string m_author;

    base::conf_node& m_config;
    
    boost::filesystem::path m_cfg_dir;
    boost::filesystem::path m_data_dir;
};

} /* namespace app */
} /* namespace yage */

#endif /* YAGE_YAGE_APP_H_ */
