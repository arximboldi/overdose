
dnl  SETUP
dnl -----------------------------------------------------------------------------

AC_INIT([overdose], [0.1.2], [raskolnikov@es.gnu.org])

AM_INIT_AUTOMAKE
AM_CONFIG_HEADER(src/config.h)

AC_LANG(C++)
AC_PROG_CXX
AC_PROG_LIBTOOL

AC_CONFIG_MACRO_DIR([m4])

dnl  Test for Boost
dnl -----------------------------------------------------------------------------

AX_BOOST_BASE([1.35])
AX_BOOST_THREAD
AX_BOOST_FILESYSTEM

if test "x${ax_cv_boost_thread}" != xyes ; then
AC_MSG_ERROR([
***
*** You need Boost.Thread library to compile the program.
*** Install it and run this script again.
***
])
fi

if test "x${ax_cv_boost_filesystem}" != xyes ; then
AC_MSG_ERROR([
***
*** You need Boost.Filsystem library to compile the program.
*** Install it and run this script again.
***
])
fi


dnl  Test for Sigc
dnl -----------------------------------------------------------------------------

PKG_CHECK_MODULES(SIGC, [ sigc++-2.0 ], [],
[
AC_MSG_ERROR([
***
*** You need Sigc++ library to compile the program.
*** Install it and run this script again.
***
])
])

dnl  Test for LibXML
dnl -----------------------------------------------------------------------------

PKG_CHECK_MODULES(LIBXML, [ libxml-2.0 >= 2.6 ], [],
[
AC_MSG_ERROR([
***
*** You need LibXML library to compile the program.
*** Install it and run this script again.
***
])
])


dnl  Test for SDL
dnl -----------------------------------------------------------------------------

PKG_CHECK_MODULES(SDL, [ sdl >= 1.2 ], [],
[
AC_MSG_ERROR([
***
*** You need SDL library to compile the program.
*** Install it and run this script again.
***
])
])


dnl  Test for SDL Image
dnl -----------------------------------------------------------------------------

PKG_CHECK_MODULES(SDL_IMAGE, [ SDL_image ], [],
[
AC_MSG_ERROR([
***
*** You need SDL_image library to compile the program.
*** Install it and run this script again.
***
])
])


dnl  Test for SDL TTF
dnl -----------------------------------------------------------------------------

PKG_CHECK_MODULES(SDL_TTF, [ SDL_ttf ], [],
[
AC_MSG_ERROR([
***
*** You need SDL_ttf library to compile the program.
*** Install it and run this script again.
***
])
])


dnl  Test for SDL mixer
dnl -----------------------------------------------------------------------------

PKG_CHECK_MODULES(SDL_MIXER, [ SDL_mixer], [],
[
AC_MSG_ERROR([
***
*** You need SDL_mixer library to compile the program.
*** Install it and run this script again.
***
])
])


dnl  Test for OpenGl
dnl -----------------------------------------------------------------------------

AX_CHECK_GL
AX_CHECK_GLU

dnl  Paths
dnl -----------------------------------------------------------------------------

PACKAGE_DATA_DIR="$datarootdir/overdose"
PACKAGE_INCLUDE_DIR="$includedir/yage"
PACKAGE_BIN_DIR=$bindir
PACKAGE_LIB_DIR=$libdir

dnl Uncomment only for development purposes
PACKAGE_DATA_DIR="./data"

AC_SUBST(PACKAGE_DATA_DIR)
AC_SUBST(PACKAGE_BIN_DIR)
AC_SUBST(PACKAGE_INCLUDE_DIR)
AC_SUBST(PACKAGE_LIB_DIR)

dnl  OUTPUT
dnl -----------------------------------------------------------------------------

AC_OUTPUT(makefile
	  src/makefile
	  doc/makefile
	  data/makefile)
