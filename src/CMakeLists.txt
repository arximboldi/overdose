configure_file(config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

add_library(yage
  yage/base/arg_parser.cpp
  yage/base/misc.cpp
  yage/base/logger.cpp
  yage/base/config.cpp
  yage/base/conf_backend_xml.cpp
  yage/base/file_finder.cpp
  yage/base/file_manager.cpp
  yage/base/exception.cpp
  yage/base/tree.cpp
  yage/base/singleton.cpp
  yage/base/handle_allocator.cpp
  yage/base/factory_manager.cpp
  yage/core/system.cpp
  yage/core/timer.cpp
  yage/core/graphic_system.cpp
  yage/core/sound_system.cpp
  yage/core/input_system.cpp
  yage/core/key_observer.cpp
  yage/core/mouse_observer.cpp
  yage/core/video_observer.cpp
  yage/core/task.cpp
  yage/core/task_manager.cpp
  yage/core/state_task.cpp
  yage/core/resource_manager.cpp
  yage/core/file_resource_manager.cpp
  yage/core/font_manager.cpp
  yage/gra/scene.cpp
  yage/gra/scene_node.cpp
  yage/gra/camera.cpp
  yage/gra/texture.cpp
  yage/gra/material.cpp
  yage/gra/static_drawable.cpp
  yage/gra/light.cpp
  yage/gra/animation_task.cpp
  yage/gra/font.cpp
  yage/gra/text.cpp
  yage/gra/fog.cpp
  yage/gra/geometry_proxy.cpp
  yage/geo/mesh.cpp
  yage/geo/multi_mesh.cpp
  yage/geo/cube.cpp
  yage/geo/cone.cpp
  yage/geo/cylinder.cpp
  yage/geo/sphere.cpp
  yage/geo/hemisphere.cpp
  yage/geo/ply_model.cpp
  yage/geo/md2_model.cpp
  yage/geo/md2_model_impl.cpp
  yage/geo/textured_plane.cpp
  yage/geo/textured_plane_2d.cpp
  yage/geo/textured_hemisphere.cpp
  yage/geo/multi_textured_cube.cpp
  yage/game/entity.cpp
  yage/game/entity_manager.cpp
  yage/game/entity_observer.cpp
  yage/game/static_collision.cpp
  yage/game/dynamic_collision.cpp
  yage/game/collision_util.cpp
  yage/game/collidable.cpp
  yage/game/state.cpp
  yage/game/state_manager.cpp
  yage/app/yage_app.cpp
  yage/app/game_app.cpp
  yage/app/graphic_controller.cpp
  lib/file_ply_stl.cc
)
if(EMSCRIPTEN)
  target_sources(yage PRIVATE yage/core/sdl_emscripten.cpp)
endif()
target_include_directories(yage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(yage
  PRIVATE YAGE_DATA_DIR="${OVERDOSE_DATA_DIR}"
  # The engine does not use GLU; keep SDL_opengl.h from requiring it.
  PUBLIC NO_SDL_GLU)
target_link_libraries(yage PUBLIC
  overdose_platform
  Boost::headers
  LibXml2::LibXml2
  PkgConfig::SIGC)
set_target_properties(yage PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR})

add_executable(overdose
  dose/st/tester.cpp
  dose/st/level.cpp
  dose/st/level_one.cpp
  dose/st/hell.cpp
  dose/ent/building.cpp
  dose/ent/person.cpp
  dose/ent/pedestrian.cpp
  dose/ent/dealer.cpp
  dose/ent/policeman.cpp
  dose/ent/invisible.cpp
  dose/ent/player.cpp
  dose/ent/player_controller.cpp
  dose/ent/player_hud.cpp
  dose/tool/fly_camera_controller.cpp
  dose/tool/follow_camera_controller.cpp
  dose/drug/dope.cpp
  dose/drug/dope_effect.cpp
  dose/drug/dope_factory.cpp
  dose/drug/bubbly_camera.cpp
  dose/drug/marihuana.cpp
  dose/drug/cocaine.cpp
  dose/drug/lsd.cpp
  dose/drug/alcohol.cpp
  dose/drug/adrenaline.cpp
  dose/overdose.cpp
  dose/main.cpp
)
# Keep the generated config.h ahead of any stale autotools copy in src/.
target_include_directories(overdose BEFORE PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(overdose PRIVATE yage)

if(NOT EMSCRIPTEN)
  install(TARGETS overdose)
endif()
