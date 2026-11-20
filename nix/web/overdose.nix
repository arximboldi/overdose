{
  lib,
  stdenvNoCC,
  cmake,
  ninja,
  pkg-config,
  boost,
  emscripten,
  emscriptenCacheHook,
  gl4es,
  libsigcxx,
  libxml2,
}:
stdenvNoCC.mkDerivation {
  pname = "overdose-web";
  version = "0.1.2";

  src = lib.fileset.toSource {
    root = ../..;
    fileset = lib.fileset.unions [
      ../../CMakeLists.txt
      ../../src
      ../../data
      ../../web
    ];
  };

  nativeBuildInputs = [
    cmake
    ninja
    pkg-config
    emscriptenCacheHook
  ];

  # Emscripten's CMake toolchain only searches its own sysroot. The
  # WebAssembly dependencies live in the Nix store instead, and the
  # sandbox has no host libraries that could be picked up by mistake,
  # so let CMake search the prefixes given to it as well. Boost is only
  # used for its headers, which are the same on every platform.
  cmakeFlags = [
    "-DCMAKE_PREFIX_PATH=${gl4es};${libxml2};${boost.dev}"
    "-DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=BOTH"
    "-DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=BOTH"
    "-DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=BOTH"
  ];
  env.PKG_CONFIG_PATH = "${libsigcxx}/lib/pkgconfig";

  configurePhase = ''
    runHook preConfigure
    emcmake cmake -S . -B build -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=$out \
      $cmakeFlags
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

  passthru = {
    inherit emscripten;
    pkgConfigPath = "${libsigcxx}/lib/pkgconfig";
  };

  meta = {
    description = "Overdose built with Emscripten, as a static website";
    license = lib.licenses.gpl3Plus;
    platforms = lib.platforms.all;
  };
}
