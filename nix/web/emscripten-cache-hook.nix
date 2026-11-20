{ makeSetupHook, emscripten }:
makeSetupHook {
  name = "emscripten-cache-hook";
  propagatedBuildInputs = [ emscripten ];
  substitutions.cache = "${emscripten}/share/emscripten/cache";
} ./emscripten-cache-hook.sh
