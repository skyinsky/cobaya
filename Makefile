include /home/s/share/topmk/topmk.def

# If this is a directory with subdirectories to build, set SUBDIRS
SUBDIRS = libiniparser libtoolkit librcfproto src

# Do not add any build rules until *after* the include of topmk.all
include /home/s/share/topmk/topmk.all
# Do not place any rules or targets above this line

