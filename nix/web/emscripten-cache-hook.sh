# Emscripten compiles its system libraries on demand into a cache
# directory. The one shipped with the emscripten package lives in the
# read-only Nix store, so start every build from a writable copy.
emscriptenCacheHook() {
    export HOME="$TMPDIR"
    export EM_CACHE="$TMPDIR/emscripten-cache"
    cp -r --no-preserve=mode "@cache@" "$EM_CACHE"
}

preConfigureHooks+=(emscriptenCacheHook)
