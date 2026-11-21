# The same SDL_ttf the native build uses, instead of the one Emscripten
# ships, which draws text with the browser's canvas: that ignores the
# font style and only estimates the font's metrics, so text looks and
# lays out differently from the desktop.
{
  stdenvNoCC,
  SDL_ttf,
  freetype,
  emscriptenCacheHook,
}:
stdenvNoCC.mkDerivation {
  pname = "SDL_ttf-emscripten";
  inherit (SDL_ttf) version src;
  meta = { inherit (SDL_ttf.meta) description homepage license; };

  nativeBuildInputs = [ emscriptenCacheHook ];
  dontConfigure = true;

  # SDL_ttf.c is the whole library. Emscripten's SDL_RWFromFile returns
  # a handle that only its own JavaScript functions understand, so
  # TTF_OpenFont gets a real SDL_RWops from sdl-ttf-rwops.c. Emscripten's
  # surfaces don't start cleared, and SDL_FillRect doesn't touch their
  # pixels, so sdl-ttf-surface.c provides versions that do.
  buildPhase = ''
    runHook preBuild
    flags="-O2 -sUSE_SDL=1 -I${freetype}/include/freetype2"
    emcc $flags -c SDL_ttf.c -o SDL_ttf.o \
      -DSDL_RWFromFile=sdl_ttf_rw_from_file \
      -DSDL_CreateRGBSurface=sdl_ttf_create_surface \
      -DSDL_FillRect=sdl_ttf_fill_rect
    emcc $flags -c ${./sdl-ttf-rwops.c} -o sdl-ttf-rwops.o
    emcc $flags -c ${./sdl-ttf-surface.c} -o sdl-ttf-surface.o
    emar rcs libSDL_ttf.a SDL_ttf.o sdl-ttf-rwops.o sdl-ttf-surface.o
    runHook postBuild
  '';

  installPhase = ''
    runHook preInstall
    install -Dm644 libSDL_ttf.a -t $out/lib
    install -Dm644 SDL_ttf.h -t $out/include/SDL
    runHook postInstall
  '';
}
