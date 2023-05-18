# -*- Makefile -*-

SDL_LIBS = -l/usr/x86_64-w64-mingw32/lib/libmingw32.a

SDL_LIBS_2 = -l/usr/x86_64-w64-mingw32
#$(SDL_LIBS)

SDL_LIBS_3 := -L/usr/x86_64-w64-mingw32/lib -lmingw32 -lSDL2

old_path = -lmingw32

Verbose = -v

all:
	g++ -o pendulum pendulum.cpp -I SDL2\x86_64-w64-mingw32\include -L SDL2\x86_64-w64-mingw32\lib -lSDL2main -lSDL2

run: all
	DISPLAY=:0 gvim && ./pendulum:

