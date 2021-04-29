src_ver := -D'GIT_COMMIT="$(shell git rev-parse --short HEAD)"'
bindir = $(top_srcdir)/output

AM_CXX_FLAGS = -I$(top_srcdir)/lib/orca
AM_C_FLAGS = -I$(top_srcdir)/lib/orca
AM_LD_ADD = $(top_srcdir)/lib/orca/lib
