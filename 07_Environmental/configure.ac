AC_INIT([rhasher], [1.0], [dmitry.astrakhantsev@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

# rhash
AC_CHECK_LIB([rhash], [rhash_init],, [AC_MSG_ERROR([librhash not found])])
AC_CHECK_HEADERS([rhash.h],, [AC_MSG_ERROR([rhash.h not found])])

# readline
AC_ARG_WITH([readline],
  [AS_HELP_STRING([--without-readline], [disable readline support])],
  [use_readline=$withval],
  [use_readline=yes])

AS_IF([test "x$use_readline" != "xno"], [
  AC_CHECK_LIB([readline], [readline],
    [
      AC_DEFINE([USE_READLINE], [1], [Define to 1 if you have readline.])
      LIBS="$LIBS -lreadline"
      AC_MSG_NOTICE([readline support enabled])
    ],
    [
      AS_IF([test "x$use_readline" = "xyes"], [
        AC_MSG_NOTICE([readline library not found, disabling readline support])
      ])
    ]
  )
])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
