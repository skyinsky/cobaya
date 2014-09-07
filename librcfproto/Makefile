CPPFLAGS = -O3
LIBS = -lpthread -lprotobuf -ldl

all: librcfproto.so

RCF.o:
	g++ $(CPPFLAGS) -fPIC -c ./RCF/src/RCF/RCF.cpp -DRCF_BUILD_DLL -DRCF_USE_ZLIB -DRCF_USE_OPENSSL -I./RCF/include

RCFProto.o: 
	g++ $(CPPFLAGS) -fPIC -c ./RCFProto.cpp -DRCF_BUILD_DLL -DRCF_USE_ZLIB -DRCF_USE_OPENSSL -I./RCF/include

librcfproto.so: RCF.o RCFProto.o
	g++ -shared -o librcfproto.so RCFProto.o RCF.o $(LIBS) 

clean:
		rm -f librcfproto.so *.o ./RCF/src/RCF/*.o 
