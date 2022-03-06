# Set it to your SDL2 library location
SDL_DIR = C:/Users/msule/sync/frameworks/SDL2/SDL2-2.0.20/x86_64-w64-mingw32

SDL_INCLUDE_ARGS = -I $(SDL_DIR)/include
SDL_LIBRARY_ARGS = -L $(SDL_DIR)/lib -lmingw32 -lSDL2main -lSDL2

CXX = gcc
CXX_ARGS = -c -std=c99 -g -Wall -I ./include



all: main s3Dengine
	$(CXX) build/main build/s3Dengine -o s3Dengine $(SDL_LIBRARY_ARGS)

dev: all
	s3Dengine

main:
	$(CXX) $(CXX_ARGS) src/main.c -o build/main $(SDL_INCLUDE_ARGS)

s3Dengine:
	$(CXX) $(CXX_ARGS) src/s3Dengine.c -o build/s3Dengine $(SDL_INCLUDE_ARGS)