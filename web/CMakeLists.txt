# Turns the game into a static website: index.html, the compiled
# overdose.js and overdose.wasm, and overdose.data with the game data
# for Emscripten's virtual file system.

set(_shell ${CMAKE_CURRENT_SOURCE_DIR}/shell.html)

set_target_properties(overdose PROPERTIES SUFFIX ".html")
target_link_options(overdose PRIVATE
  "SHELL:--preload-file ${PROJECT_SOURCE_DIR}/data@${OVERDOSE_DATA_DIR}"
  "SHELL:--shell-file ${_shell}")
set_property(TARGET overdose APPEND PROPERTY LINK_DEPENDS ${_shell})

set(_out $<TARGET_FILE_DIR:overdose>)
install(FILES ${_out}/overdose.html DESTINATION . RENAME index.html)
install(FILES
  ${_out}/overdose.js
  ${_out}/overdose.wasm
  ${_out}/overdose.data
  DESTINATION .)
