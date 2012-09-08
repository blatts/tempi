AC_INIT(gpio, 0.1)
AC_PREREQ(2.61)
AC_CONFIG_SRCDIR([src])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

LT_INIT

AC_LANG_CPLUSPLUS
dnl AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_INSTALL

dnl set CPPFLAGS
CPPFLAGS="-W -Wall -std=c++98 $CPPFLAGS"
CXXFLAGS="-W -Wall -std=c++98 $CXXFLAGS"

dnl Determine default prefix
test x$prefix = "xNONE" && prefix="$ac_default_prefix"

dnl Check whether to include debugging code
DEBUG=""
AC_MSG_CHECKING([whether to include verbose debugging code])
AC_ARG_ENABLE(debug,
  [  --enable-debug          include verbose debugging code [default=no]],
  if test x$enableval = "xyes"; then
    AC_MSG_RESULT([yes])
    DEBUG="-DDEBUG -fno-inline"
  else
    AC_MSG_RESULT([no])
  fi,
  AC_MSG_RESULT([no])
)
AC_SUBST(DEBUG)
CXXFLAGS="$CXXFLAGS $DEBUG"

dnl check for GSL. Need static flag to make the check
dnl even work on the cluster.
dnl LDFLAGS="$LDFLAGS -static"
dnl GSL_MIN_VERSION="1.10"
dnl AX_PATH_GSL($GSL_MIN_VERSION,,[AC_MSG_ERROR(Could not find GSL version >=$GSL_MIN_VERSION.)])

dnl PKG_CHECK_MODULES([DEPS], [gsl >= 1.10])

dnl Get GSL library and include locations
dnl AC_ARG_WITH([gsl-prefix],
dnl   [AS_HELP_STRING([--with-gsl-prefix],
dnl     [location of the GSL headers and library.])],
dnl   [GSL_CFLAGS="-I$withval/include" GSL_LIBS="-L$withval/lib -lm -lgslcblas -lgsl"],
dnl   [GSL_CFLAGS='' GSL_LIBS='-lm -lgslcblas -lgsl'])
dnl AC_SUBST([GSL_CFLAGS])
dnl AC_SUBST([GSL_LIBS])

dnl Get HDF5 library and include locations
dnl AC_ARG_WITH([hdf5-prefix],
dnl   [AS_HELP_STRING([--with-hdf5-prefix],
dnl     [location of the HDF5 headers and library.])],
dnl   [HDF5_CFLAGS="-I$withval/include" HDF5_LIBS="-L$withval/lib -lhdf5 -lhdf5_hl"],
dnl   [HDF5_CFLAGS='' HDF5_LIBS='-lhdf5 -lhdf5_hl'])
dnl AC_SUBST([HDF5_CFLAGS])
dnl AC_SUBST([HDF5_LIBS])

dnl check for boost
dnl BOOST_REQUIRE

dnl include curses
dnl AX_WITH_CURSES

dnl Print results
AC_MSG_RESULT([])
AC_MSG_RESULT([ $PACKAGE version $VERSION configured successfully.])
AC_MSG_RESULT([])
AC_MSG_RESULT([Using '$prefix' for installation.])
AC_MSG_RESULT([Using '$CXX' for C++ compiler.])
AC_MSG_RESULT([Building with '$CXXFLAGS' for C++ compiler flags.])
AC_MSG_RESULT([Building with '$LDFLAGS' for linker flags.])
AC_MSG_RESULT([])

AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT
