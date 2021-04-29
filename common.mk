src_ver := -D'GIT_COMMIT="$(shell git rev-parse --short HEAD)"'
bindir = $(top_srcdir)/output

AM_CFLAGS = -I$(top_srcdir)/lib -I$(top_srcdir)/lib/orca/common -I$(top_srcdir)/lib/orca/common/third-party ${libcurl_LIBS}