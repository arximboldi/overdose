{
  stdenvNoCC,
  emscripten,
  meson,
  ninja,
  libsigcxx_2_0,
  emscriptenCacheHook,
}:
stdenvNoCC.mkDerivation {
  pname = "libsigc++-emscripten";
  inherit (libsigcxx_2_0) version src meta;

  nativeBuildInputs = [
    meson
    ninja
    emscriptenCacheHook
  ];

  configurePhase = ''
    runHook preConfigure
    meson setup build \
      --cross-file ${emscripten}/share/emscripten/tools/meson/wasm32-emscripten.ini \
      --prefix=$out --buildtype=release --default-library=static \
      -Dbuild-examples=false -Dbuild-tests=false -Dbuild-documentation=false
    runHook postConfigure
  '';

  buildPhase = ''
    runHook preBuild
    meson compile -C build
    runHook postBuild
  '';

  installPhase = ''
    runHook preInstall
    meson install -C build
    runHook postInstall
  '';
}
