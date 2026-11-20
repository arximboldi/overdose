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
# Natively, the default points at the source tree so a fresh build runs
# without installing, and packagers set it to the installed location.
# In the browser, the data is packaged into Emscripten's virtual file
# system at this path.
if(EMSCRIPTEN)
  set(_default_data_dir "/data")
else()
  set(_default_data_dir "${PROJECT_SOURCE_DIR}/data")
endif()
set(OVERDOSE_DATA_DIR "${_default_data_dir}"
  CACHE PATH "Directory the game loads its data files from")

find_package(Boost 1.70 REQUIRED CONFIG)
find_package(LibXml2 2.6 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SIGC REQUIRED IMPORTED_TARGET sigc++-2.0)

# SDL 1.2 and OpenGL, through which the engine draws, plays sound and
# reads input.
add_library(overdose_platform INTERFACE)
if(EMSCRIPTEN)
  # Emscripten implements the SDL 1.2 API itself. gl4es provides the
  # fixed-function OpenGL the engine is written in on top of WebGL.
  find_path(GL4ES_INCLUDE_DIR gl4esinit.h REQUIRED)
  find_library(GL4ES_LIBRARY gl4es REQUIRED)
  target_include_directories(overdose_platform INTERFACE
    ${GL4ES_INCLUDE_DIR}
    ${EMSCRIPTEN_SYSROOT}/include/SDL)
  target_link_libraries(overdose_platform INTERFACE ${GL4ES_LIBRARY})
  # JavaScript-based exceptions: unlike native Wasm exceptions, they let
  # the browser's main loop unwind through the engine's catch (...).
  target_compile_options(overdose_platform INTERFACE -fexceptions)
  target_link_options(overdose_platform INTERFACE
    -fexceptions
    -sUSE_SDL=1
    -sFULL_ES2=1           # client-side vertex arrays, used by gl4es
    -sSTB_IMAGE=1          # decode TGA textures, which browsers cannot
    -sALLOW_MEMORY_GROWTH=1)
else()
  find_package(OpenGL REQUIRED COMPONENTS OpenGL)
  find_package(SDL 1.2 REQUIRED)
  find_package(SDL_image REQUIRED)
  find_package(SDL_ttf REQUIRED)
  find_package(SDL_mixer REQUIRED)
  target_include_directories(overdose_platform INTERFACE
    ${SDL_IMAGE_INCLUDE_DIRS}
    ${SDL_TTF_INCLUDE_DIRS}
    ${SDL_MIXER_INCLUDE_DIRS})
  target_link_libraries(overdose_platform INTERFACE
    OpenGL::GL
    SDL::SDL
    ${SDL_IMAGE_LIBRARIES}
    ${SDL_TTF_LIBRARIES}
    ${SDL_MIXER_LIBRARIES})
endif()

add_subdirectory(src)

if(EMSCRIPTEN)
  add_subdirectory(web)
  return()
endif()

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
