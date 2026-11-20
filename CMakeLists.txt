cmake_minimum_required(VERSION 3.20...4.4)

project(overdose VERSION 0.1.2 LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

# Where the game looks for its textures, models and fonts at run time.
# The default points at the source tree so a fresh build runs without
# installing; packagers set it to the installed location.
set(OVERDOSE_DATA_DIR "${PROJECT_SOURCE_DIR}/data"
  CACHE PATH "Directory the game loads its data files from")

find_package(Boost 1.70 REQUIRED CONFIG)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(LibXml2 2.6 REQUIRED)
find_package(SDL 1.2 REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SIGC REQUIRED IMPORTED_TARGET sigc++-2.0)

add_subdirectory(src)

install(DIRECTORY data/
  DESTINATION ${CMAKE_INSTALL_DATADIR}/overdose
  PATTERN "makefile*" EXCLUDE
  PATTERN "*~" EXCLUDE)

find_program(HELP2MAN help2man)
if(HELP2MAN)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/overdose.6
    COMMAND ${CMAKE_COMMAND} -E env HOME=${CMAKE_CURRENT_BINARY_DIR}
      ${HELP2MAN} --no-info --section=6 --output=overdose.6 $<TARGET_FILE:overdose>
    DEPENDS overdose
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating overdose.6 man page")
  add_custom_target(man ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/overdose.6)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/overdose.6
    DESTINATION ${CMAKE_INSTALL_MANDIR}/man6)
endif()
