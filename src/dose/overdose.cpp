/**
 *  @file        overdose.cpp
 *  @author      Juan Pedro Bolívar Puente <raskolnikov@es.gnu.org>
 *  @date        Mon May 18 19:02:11 2009
 *
 *  Implementación de la clase overdose.
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

#include "st/tester.hpp"
#include "st/level_one.hpp"
#include "st/hell.hpp"

#include "overdose.hpp"
#include "config.h"

using namespace yage;

namespace dose
{

float overdose::s_dope_level = 0.0f;

static const char* OVERDOSE_PROGRAM = "overdose";
static const char* OVERDOSE_VERSION = VERSION;
static const char* OVERDOSE_DESCRIPTION =
    "Overdose is a to safely explore drug abuse and self-destriction.";
static const char* OVERDOSE_COPYRIGHT_DATE = "2009";
static const char* OVERDOSE_AUTHOR = "Juan Pedro Bolívar Puente";

overdose::overdose ()
    : yage::app::game_app (
	OVERDOSE_PROGRAM,
	OVERDOSE_VERSION,
	OVERDOSE_DESCRIPTION,
	OVERDOSE_COPYRIGHT_DATE,
	OVERDOSE_AUTHOR)
    , m_initial_state ("level_one")
{
}

void overdose::print_help (std::ostream& out)
{
    yage::app::game_app::print_help (out);

    out << "\n"
	<< "Advanced options:\n"
	<< "  -i, --init-state <value>   Set the starting state.\n"
	<< "  -l, --dope-level <value>   Set the starting dope level.\n";
}

void overdose::prepare (yage::base::arg_parser& args)
{
    std::srand (std::time (0));

    args.add ('i', "--init-state", &m_initial_state);
    args.add ('l', "--dope-level", &s_dope_level);
}

void overdose::register_states (boost::shared_ptr<yage::game::state_manager> mgr)
{
    mgr->add<st::tester> ("tester");

    mgr->add<st::level_one> ("level_one");
    mgr->add<st::hell> ("hell");
}

std::string overdose::initial_state ()
{
    return m_initial_state;
}

} /* namespace dose */
