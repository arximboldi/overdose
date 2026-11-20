{
  stdenvNoCC,
  cmake,
  ninja,
  libxml2,
  emscriptenCacheHook,
}:
stdenvNoCC.mkDerivation {
  pname = "libxml2-emscripten";
  inherit (libxml2) version src;
  meta = { inherit (libxml2.meta) description homepage license; };

  nativeBuildInputs = [
    cmake
    ninja
    emscriptenCacheHook
  ];

  # The game only reads and writes its own small XML config file.
  configurePhase = ''
    runHook preConfigure
    emcmake cmake -S . -B build -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=$out \
      -DBUILD_SHARED_LIBS=OFF \
      -DLIBXML2_WITH_ICONV=OFF \
      -DLIBXML2_WITH_ICU=OFF \
      -DLIBXML2_WITH_LZMA=OFF \
      -DLIBXML2_WITH_ZLIB=OFF \
      -DLIBXML2_WITH_PYTHON=OFF \
      -DLIBXML2_WITH_PROGRAMS=OFF \
      -DLIBXML2_WITH_TESTS=OFF \
      -DLIBXML2_WITH_THREADS=OFF \
      -DLIBXML2_WITH_HTTP=OFF \
      -DLIBXML2_WITH_MODULES=OFF \
      -DLIBXML2_WITH_DOCS=OFF
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
