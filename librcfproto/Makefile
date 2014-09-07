CPPFLAGS	= -O3
OPTIONS		= -DRCF_USE_ZLIB -DRCF_USE_OPENSSL -DRCF_USE_IPV6
LIBS		= -lpthread -lprotobuf -ldl

#CPPFLAGS	+= $(OPTIONS)

all: librcfproto.so

RCF.o:
	g++ $(CPPFLAGS) -fPIC -c ./RCF/src/RCF/RCF.cpp -DRCF_BUILD_DLL -I./RCF/include

RCFProto.o: 
	g++ $(CPPFLAGS) -fPIC -c ./RCFProto.cpp -DRCF_BUILD_DLL -I./RCF/include

librcfproto.so: RCF.o RCFProto.o
	g++ -shared -o librcfproto.so RCFProto.o RCF.o $(LIBS) 

clean:
		rm -f librcfproto.so *.o
