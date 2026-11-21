{
  stdenvNoCC,
  cmake,
  ninja,
  freetype,
  emscriptenCacheHook,
}:
stdenvNoCC.mkDerivation {
  pname = "freetype-emscripten";
  inherit (freetype) version src;
  meta = { inherit (freetype.meta) description homepage license; };

  nativeBuildInputs = [
    cmake
    ninja
    emscriptenCacheHook
  ];

  # SDL_ttf only needs to rasterise outlines from a TrueType file.
  configurePhase = ''
    runHook preConfigure
    emcmake cmake -S . -B build -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=$out \
      -DBUILD_SHARED_LIBS=OFF \
      -DFT_DISABLE_ZLIB=ON \
      -DFT_DISABLE_BZIP2=ON \
      -DFT_DISABLE_PNG=ON \
      -DFT_DISABLE_HARFBUZZ=ON \
      -DFT_DISABLE_BROTLI=ON
    runHook postConfigure
  '';

  buildPhase = ''
    runHook preBuild
    cmake --build build
    runHook postBuild
  '';

  installPhase = ''
    runHook preInstall
    cmake --install build
    runHook postInstall
  '';
}
