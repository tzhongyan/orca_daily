include $(top_srcdir)/common.mk

SUBDIRS = src

orca:
	cd lib/orca && make libdiscord && cd ../..

# Build all 3rd party libraries first
lib: orca

# Before building our own code
all-recursive: lib

.PHONY: lib

clean-local:
	cd lib/orca && make clean && cd ../..