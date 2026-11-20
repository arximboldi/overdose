{ pkgs, ... }:
pkgs.mkShell {
  packages = with pkgs; [
    cmake
    ninja
    pkg-config
    help2man
    boost
    libsigcxx_2_0
    libxml2
    SDL
    SDL_image
    SDL_ttf
    SDL_mixer
    libGL
    libGLU
  ];
}
