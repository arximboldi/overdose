{
  lib,
  stdenv,
  cmake,
  ninja,
  pkg-config,
  help2man,
  boost,
  libsigcxx_2_0,
  libxml2,
  SDL,
  SDL_image,
  SDL_ttf,
  SDL_mixer,
  libGL,
}:
stdenv.mkDerivation {
  pname = "overdose";
  version = "0.1.2";

  src = lib.fileset.toSource {
    root = ../.;
    fileset = lib.fileset.unions [
      ../CMakeLists.txt
      ../src
      ../data
    ];
  };

  nativeBuildInputs = [
    cmake
    ninja
    pkg-config
    help2man
  ];

  buildInputs = [
    boost
    libsigcxx_2_0
    libxml2
    SDL
    SDL_image
    SDL_ttf
    SDL_mixer
    libGL
  ];

  cmakeFlags = [
    (lib.cmakeFeature "OVERDOSE_DATA_DIR" "${placeholder "out"}/share/overdose")
  ];

  meta = {
    description = "Small 3D game about experiencing the effects of drugs";
    license = lib.licenses.gpl3Plus;
    mainProgram = "overdose";
    platforms = lib.platforms.linux;
  };
}
