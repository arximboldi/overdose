# The game built with Emscripten, as a static website.
{ callPackage }:
let
  emscriptenCacheHook = callPackage ./emscripten-cache-hook.nix { };
in
callPackage ./overdose.nix {
  inherit emscriptenCacheHook;
  gl4es = callPackage ./gl4es.nix { inherit emscriptenCacheHook; };
  libsigcxx = callPackage ./libsigcxx.nix { inherit emscriptenCacheHook; };
  libxml2 = callPackage ./libxml2.nix { inherit emscriptenCacheHook; };
}
