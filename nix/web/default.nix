# The game built with Emscripten, as a static website.
{ callPackage }:
let
  emscriptenCacheHook = callPackage ./emscripten-cache-hook.nix { };
  freetype = callPackage ./freetype.nix { inherit emscriptenCacheHook; };
in
callPackage ./overdose.nix {
  inherit emscriptenCacheHook;
  gl4es = callPackage ./gl4es.nix { inherit emscriptenCacheHook; };
  libsigcxx = callPackage ./libsigcxx.nix { inherit emscriptenCacheHook; };
  libxml2 = callPackage ./libxml2.nix { inherit emscriptenCacheHook; };
  sdl-ttf = callPackage ./sdl-ttf.nix { inherit emscriptenCacheHook freetype; };
  inherit freetype;
}
