# Shell for working on the browser build:
#
#   emcmake cmake -S . -B build-web -G Ninja $cmakeFlags
#   cmake --build build-web
{ mkShell, overdose-web }:
let
  inherit (overdose-web) emscripten;
in
mkShell {
  inputsFrom = [ overdose-web ];
  inherit (overdose-web) cmakeFlags;
  env.PKG_CONFIG_PATH = overdose-web.pkgConfigPath;

  # Emscripten needs a writable cache for the system libraries it
  # compiles on demand; seed one from the read-only copy in the store.
  shellHook = ''
    export EM_CACHE="''${XDG_CACHE_HOME:-$HOME/.cache}/overdose/emscripten-${emscripten.version}"
    if [ ! -d "$EM_CACHE" ]; then
      mkdir -p "$(dirname "$EM_CACHE")"
      cp -r --no-preserve=mode ${emscripten}/share/emscripten/cache "$EM_CACHE"
    fi
  '';
}
