#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.6])
AC_INIT([mod_auth_env], [0.1], [rnoc@gatech.edu])
AC_CONFIG_SRCDIR([src/mod_auth_env.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

#### Locate APXS
## First, check --with-apxs
AC_MSG_NOTICE([Locating apxs])
AC_MSG_CHECKING([for --with-apxs])
AC_ARG_WITH(
	[apxs],
	[AS_HELP_STRING([--with-apxs],[/absolute/path/to/apxs])],
	[WITH_APXS=$with_apxs],
	[WITH_APXS=no]
)
AC_MSG_RESULT([$WITH_APXS])

if test -f "$WITH_APXS" && test -x "$WITH_APXS"
then
	APXS=$WITH_APXS
else
	AC_PATH_PROGS([APXS],[apxs apxs2])
fi

if test "$APXS"
then
	AC_MSG_NOTICE([apxs found at $APXS])
	AC_SUBST([APXS])
else
	AC_MSG_FAILURE([apxs not found])
fi

#### Done locating APXS

# Checks for header files.
AC_CHECK_HEADERS([stddef.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp strchr strncasecmp strstr])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
