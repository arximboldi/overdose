/**
 *  Time-stamp:  <2009-05-24 18:01:27 raskolnikov>
 *
 *  @file        conf_backend_xml.hpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        2007
 *
 *  XML yaged configuration backend.
 */

/*
 *  Copyright (C) 2007, 2008, 2009 Juan Pedro Bolívar Puente
 *
 *  This file is part of Psychosynth.
 *   
 *  Psychosynth is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Psychosynth is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef YAGE_CONFBACKENDXML_H
#define YAGE_CONFBACKENDXML_H

#include <string>

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>

#include <yage/base/type_value.hpp>
#include <yage/base/config.hpp>

namespace yage
{
namespace base
{

YAGE_DECLARE_ERROR (config_error, config_xml_error)
YAGE_DECLARE_ERROR (config_xml_error, config_xml_type_error)
YAGE_DECLARE_ERROR (config_xml_error, config_xml_io_error)

/**
 * XML configuration backend that stores the config to an XML file. This
 * is not a live backend so it needs explicit calls on @c save and @c load
 * on the @c conf_node.
 */
class conf_backend_xml : public conf_backend
{
public:
    /**
     * Constructor.
     * @param file The name of the file where to store and load
     * the configuration.
     */
    conf_backend_xml (const std::string& file)
	: m_file(file)
    {}

    /** Constructor */
    ~conf_backend_xml () {}

    /**
     * Changes the name of the file to use.
     * @param file The new file name to use.
     */
    void set_file (const std::string& file)
    {
	m_file = file;
    }

    /**
     * Returns the name of the current filename.
     */
    const std::string& get_file ()
    {
	return m_file;
    }

    /** Called when attached to a node. Does nothing. */
    void attach (conf_node& node) {};

    /** Called when dattached from a node. Does nothing. */
    void datach (conf_node& node) {};

    /**
     * Permanently stores the configuration in the currently set file.
     * @param node The configuration to store.
     */
    void save (conf_node& node);

    /**
     * Loads the conentent of the XML file into a node.
     * @param node The node where to store the config.
     */
    void load (conf_node& node)
    {
	m_overwrite = true;
	do_load (node);
    }

    /**
     * Loads the content of the XML file into a node but preserving the node
     * values that are already set.
     */
    void def_load (conf_node& node)
    {
	m_overwrite = false;
	do_load (node);
    }

private:
    type_value m_current_type;
    
    std::string m_file;
    bool m_overwrite;
    
    conf_node* process_new_element (xmlTextReaderPtr reader, conf_node* node);
    conf_node* process_text (xmlTextReaderPtr reader, conf_node* node);
    conf_node* process_end_element (xmlTextReaderPtr reader, conf_node* node);
    conf_node* process (xmlTextReaderPtr reader, conf_node* node);

    void do_load (conf_node& node);
    
    void expand (xmlTextWriterPtr writer, conf_node& node);
    void expand_childs (xmlTextWriterPtr writer, conf_node& node);
    void expand_value (xmlTextWriterPtr writer, conf_node& node);
};

} /* namespace base */
} /* namespace yage */

#endif /* YAGE_CONFBACKENDXML_H */
