{ nixpkgs ? (import <nixpkgs> {}).fetchFromGitHub {
    owner  = "NixOS";
    repo   = "nixpkgs";
    rev    = "05f0934825c2a0750d4888c4735f9420c906b388";
    sha256 = "1g8c2w0661qn89ajp44znmwfmghbbiygvdzq0rzlvlpdiz28v6gy";
  }}:

with import nixpkgs {};

let

  libsigcxx_oldie = stdenv.mkDerivation rec {
    pname = "libsigc++";
    version = "2.0.18";
    src = fetchurl {
      url = "mirror://gnome/sources/${pname}/${stdenv.lib.versions.majorMinor version}/${pname}-${version}.tar.bz2";
      sha256 = "1syc3v1a826y7kzahipdhvkz63c8yx1cnsn2h4bs659qnwqd1rsk";
    };
    preConfigure = ''
      export AM_CXXFLAGS="$CXXFLAGS -fpermissive"
    '';
    nativeBuildInputs = [ pkgconfig gnum4 ];
    doCheck = true;
    passthru = {
      updateScript = gnome3.updateScript {
        packageName = pname;
        attrPath = "libsigcxx";
      };
    };
    meta = with stdenv.lib; {
      homepage = https://libsigcplusplus.github.io/libsigcplusplus/;
      description = "A typesafe callback system for standard C++";
      license = licenses.lgpl21;
      platforms = platforms.all;
    };
  };

in

stdenv.mkDerivation rec {
  name = "overdose-dev";
  buildInputs = [
    autoconf-archive
    autoreconfHook
    pkgconfig
    ccache
    boost
    libxml2
    boost
    libsigcxx_oldie
    SDL
    SDL_image
    SDL_ttf
    SDL_mixer
  ];
  hardeningDisable = [ "fortify" ];
}
