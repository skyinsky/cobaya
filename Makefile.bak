CXX_FLAGS = -g -O3 -Wall

all: librcfproto.so

RCF.o:
	g++ -fPIC -c ./RCF/src/RCF/RCF.cpp -DRCF_BUILD_DLL -DRCF_USE_ZLIB -DRCF_USE_OPENSSL -I./RCF/include

RCFProto.o: 
	g++ -fPIC -c ./RCFProto.cpp -DRCF_BUILD_DLL -DRCF_USE_ZLIB -DRCF_USE_OPENSSL -I./RCF/include

librcfproto.so: RCF.o RCFProto.o
	g++ -shared -o librcfproto.so RCFProto.o RCF.o -lpthread -lprotobuf -ldl 

clean:
		rm -f librcfproto.so *.o ./RCF/src/RCF/*.o 
