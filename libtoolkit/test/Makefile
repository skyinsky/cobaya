include /home/s/share/topmk/topmk.def
# List of target files to be build
TARGETS = wait

# Target specific variables
wait_SOURCES = $(wildcard *.cc)
wait_CXXFLAGS= -I../include -Wno-pointer-arith -fpermissive
wait_LDFLAGS = -L../src
wait_LDLIBS  = -ltoolkit
wait_RPATHS  = 

# Variables affecting global compiler flags
DEBUGING = -g # Comment this line for non-debugging code
OPTIMIZE = -O0 # Comment this line for optimized(-O3) code
WARNINGS= #-Werror # Comment this line if warning is a problem

# Optional local files to be removed when making 'clean'
# Objects and libraries are taken care of, they do *not* need to be set here
CLEAN = 

# If this is a directory with subdirectories to build, set SUBDIRS
SUBDIRS = 

# Do not add any build rules until *after* the include of topmk.all
include /home/s/share/topmk/topmk.all
# Do not place any rules or targets above this line
