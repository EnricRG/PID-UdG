all: libWindowAddon.so

libWindowAddon.so: 
	g++ -fpic -shared -I/`pwd`/include/ -I/`pwd`/sources/ WindowAddon.cpp sources/*.cpp -o libWindowAddon.so

