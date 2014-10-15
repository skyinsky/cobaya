include /home/s/share/topmk/topmk.def
# List of target files to be build
TARGETS = memcpy

# Target specific variables
memcpy_SOURCES = t_memcpy.cc
memcpy_CXXFLAGS= -I../include -Wno-pointer-arith -fpermissive
memcpy_LDFLAGS = -L../
memcpy_LDLIBS  = -ltoolkit
memcpy_RPATHS  =  ../

# Variables affecting global compiler flags
DEBUGING = -g # Comment this line for non-debugging code
OPTIMIZE = -O0 # Comment this line for optimized(-O3) code
WARNINGS= #-Werror # Comment this line if warning is a problem

CPPFLAGS += -Wno-pointer-arith -fpermissive \
	    -Wno-invalid-offsetof

# Optional local files to be removed when making 'clean'
# Objects and libraries are taken care of, they do *not* need to be set here
CLEAN = 

# If this is a directory with subdirectories to build, set SUBDIRS
SUBDIRS = 

# Do not add any build rules until *after* the include of topmk.all
include /home/s/share/topmk/topmk.all
# Do not place any rules or targets above this line
