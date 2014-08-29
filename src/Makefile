include /home/s/share/topmk/topmk.def

# Root directory
ROOT = .

# protocol directory
SRC_PROTO_DIR = ../protocol
DST_PROTO_DIR = ./protocol

# List of targets to be build
TARGETS = cobaya

# Variables affecting global compiler flags
DEBUGING = -g # Comment this line for non-debugging code
OPTIMIZE = -O0 # Comment this line for optimized(-O3) code
#WARNINGS+= -Werror # Comment this line if warning is a problem

# Variables for specific target
cobaya_SOURCES = $(wildcard *.cc) $(wildcard $(DST_PROTO_DIR)/*.cc)
cobaya_CXXFLAGS= -I../ -Wno-pointer-arith -fpermissive
#cobaya_LDFLAGS = -L../util
cobaya_LDLIBS  = -lprotobuf
#cobaya_RPATHS  = ../util

# Optional local files to be removed when making 'clean'
# Objects and libraries are taken care of, they do *not* need to be set here
CLEAN = $(DST_PROTO_DIR)

# If this is a directory with subdirectories to build, set SUBDIRS
SUBDIRS =

# Do not add any build rules until *after* the include of topmk.all
include /home/s/share/topmk/topmk.all
# Do not place any rules or targets above this line

# protocol files
PROTOCOL_SRC = $(SRC_PROTO_DIR)/cobaya_client.proto \
	       $(SRC_PROTO_DIR)/cobaya_external.proto

# temporary protocol
$(DST_PROTO_DIR): $(PROTOCOL_SRC)
	mkdir -p $(DST_PROTO_DIR)
	protoc --cpp_out=$(DST_PROTO_DIR) -I$(SRC_PROTO_DIR) $^

$(cobaya_DEPENDS): $(DST_PROTO_DIR)
