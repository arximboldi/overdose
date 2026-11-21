# gl4es translates the fixed-function OpenGL 1.x the game is written in
# to OpenGL ES 2, which Emscripten maps onto WebGL.
{
  lib,
  stdenvNoCC,
  fetchFromGitHub,
  cmake,
  ninja,
  emscriptenCacheHook,
}:
stdenvNoCC.mkDerivation {
  pname = "gl4es-emscripten";
  version = "1.1.6-unstable-2026-11-11";

  src = fetchFromGitHub {
    owner = "ptitSeb";
    repo = "gl4es";
    rev = "8b1a3da5d2331d0f88b70be25963182d46eed857";
    hash = "sha256-QbH2IMCgcpvPDemaVqTnJ6VFJu3BtWve41SVDH8V5ls=";
  };

  nativeBuildInputs = [
    cmake
    ninja
    emscriptenCacheHook
  ];

  configurePhase = ''
    runHook preConfigure
    emcmake cmake -S . -B build -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DNOX11=ON -DNOEGL=ON -DSTATICLIB=ON
    runHook postConfigure
  '';

  buildPhase = ''
    runHook preBuild
    cmake --build build
    runHook postBuild
  '';

  # The upstream install rules only cover the shared library.
  installPhase = ''
    runHook preInstall
    install -Dm644 lib/libGL.a $out/lib/libgl4es.a
    mkdir -p $out/include
    cp -r include/GL include/gl4esinit.h include/gl4eshint.h $out/include/
    runHook postInstall
  '';

  meta = {
    description = "OpenGL 1.x to OpenGL ES 2 translation layer, built for Emscripten";
    homepage = "https://github.com/ptitSeb/gl4es";
    license = lib.licenses.mit;
  };
}
