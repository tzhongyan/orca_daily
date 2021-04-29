AC_INIT([daily_crypto],[0.0.1])
AC_CONFIG_SRCDIR([configure.ac])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR(build-aux)

AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([foreign])

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES])

AC_LANG([C])
AC_PROG_CC
AC_PROG_CXX
LT_INIT

AC_SUBST(GITVERSION)
AC_SUBST(GITTAG)
AC_SUBST(GITBRANCH)

# -----------------------------------------------------------------------
# Checks for libraries
# -----------------------------------------------------------------------

dnl Checks for libraries.

AC_CHECK_LIB(pthread, pthread_exit)

# -----------------------------------------------------------------------
# Checks for header files
# -----------------------------------------------------------------------

dnl Checks for header files.

# Autoupdate added the next two lines to ensure that your configure
# script's behavior did not change.  They are probably safe to remove.
AC_CHECK_INCLUDES_DEFAULT
AC_PROG_EGREP

AC_CHECK_HEADERS([stdlib.h string.h strings.h math.h sys/ioctl.h sys/param.h sys/socket.h sys/poll.h sys/time.h sys/types.h pthread.h getopt.h iconv.h syslog.h unistd.h execinfo.h])

# -----------------------------------------------------------------------
# Checks for typedefs, structures, and compiler characteristics.
# -----------------------------------------------------------------------
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_CHECK_HEADERS_ONCE([sys/time.h])

AC_STRUCT_TM

# -----------------------------------------------------------------------
# Checks for library functions.
# -----------------------------------------------------------------------
AC_PROG_GCC_TRADITIONAL
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_SELECT_ARGTYPES
AC_CACHE_CHECK([return type of signal handlers],[ac_cv_type_signal],[AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([#include <sys/types.h>
#include <signal.h>
],
		 [return *(signal (0, 0)) (0) == 1;])],
		   [ac_cv_type_signal=int],
		   [ac_cv_type_signal=void])])
AC_DEFINE_UNQUOTED([RETSIGTYPE],[$ac_cv_type_signal],[Define as the return type of signal handlers
		    (`int' or `void').])

AC_FUNC_VPRINTF
AC_CHECK_FUNCS([gettimeofday inet_ntoa memset select socket strerror strtol strtoul])

# -----------------------------------------------------------------------
# check for operating system specialities.....
# -----------------------------------------------------------------------
CFLAGS="$CFLAGS -D_REENTRANT -D_THREAD_SAFE"
CXXFLAGS="$CXXFLAGS `getconf LFS_CFLAGS` -lgpg-error"

case $host_os in
freebsd*)
        CFLAGS="$CFLAGS -DFreeBSD -Wall -pthread -DHAVE_SIN6_SCOPE_ID"
        CXXFLAGS="$CXXFLAGS -DFreeBSD -Wall -pthread -DHAVE_SIN6_SCOPE_ID"
        thread_LIBS=""
        ;;
linux*)
        case $host_cpu in
        alpha* | hppa* | i*86 | ia64* | m68* | mips* | powerpc* | sparc* | s390* | sh*)
                lt_cv_deplibs_check_method=pass_all ;;
        esac
        CFLAGS="$CFLAGS -Wall -Wextra -DLINUX -DHAVE_SIN6_SCOPE_ID"
	    CXXFLAGS="$CXXFLAGS -DLINUX -DHAVE_SIN6_SCOPE_ID -Wall -Wextra -Wformat=2"
        LDFLAGS="$LDFLAGS -lm"
        thread_LIBS="-lpthread"
        ;;
solaris*)
        CFLAGS="$CFLAGS -D__EXTENSIONS__ -Wall -DSOLARIS -D__sun -DSUN -DSUNOS_5 -D_XPG4_2"
        CXXFLAGS="$CXXFLAGS -D__EXTENSIONS__ -Wall -DSOLARIS -D__sun -DSUN -DSUNOS_5 -D_XPG4_2"
        thread_LIBS="-lpthread"
        LDFLAGS="$LDFLAGS -lsocket -lnsl -lrt -lresolv"
        ;;
darwin*)
        CFLAGS="$CFLAGS -O0 -DDARWIN -Wall -Wformat"
        CXXFLAGS="$CXXFLAGS -O0 -DDARWIN -Wall -Wformat"
        thread_LIBS="-lpthread"
        ;;
esac
AC_SUBST(thread_LIBS)

dnl Check for libcurl required by orca
AH_TEMPLATE(HAVE_LIBCURL, [libcurl library present])
AC_CHECK_LIB(curl, curl_easy_getinfo, [
    AC_DEFINE(HAVE_LIBCURL) HAVE_LIBCURL="true"
    LDFLAGS="$LDFLAGS -lcurl"
], [
    AC_MSG_RESULT(no)
    AC_MSG_ERROR(libcurl not found)
])

dnl Check for crypto ssl required by orca
AH_TEMPLATE(HAVE_LIBCRYPTO, [openssl libcrypto library present])
AC_CHECK_LIB(crypto, RAND_file_name, [
    AC_DEFINE(HAVE_LIBCRYPTO) HAVE_LIBCRYPTO="true"
    LDFLAGS="$LDFLAGS -lcrypto"
], [
    AC_MSG_RESULT(no)
    AC_MSG_ERROR(crypto not found)
])



AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
