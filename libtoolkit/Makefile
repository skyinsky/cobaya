include /home/s/share/topmk/topmk.def

# Root directory
ROOT = .

# List of targets to be build
TARGETS = libtoolkit.so

# Variables affecting global compiler flags
DEBUGING = #-g # Comment this line for non-debugging code
#OPTIMIZE = -O0 # Comment this line for optimized(-O3) code
WARNINGS+= -Werror # Comment this line if warning is a problem

# Variables for specific target
libtoolkit.so_SOURCES = $(wildcard src/*.c)
libtoolkit.so_CFLAGS  = -I./include
#libtoolkit.so_LDFLAGS = -L../util
libtoolkit.so_LDLIBS  = -pthread -lrt -lm
#libtoolkit.so_RPATHS  = ../libtoolkit

# Optional local files to be removed when making 'clean'
# Objects and libraries are taken care of, they do *not* need to be set here
CLEAN = 

# If this is a directory with subdirectories to build, set SUBDIRS
SUBDIRS = 

# Do not add any build rules until *after* the include of topmk.all
include /home/s/share/topmk/topmk.all
# Do not place any rules or targets above this line

