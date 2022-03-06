#include <stdio.h>
#include <SDL2/SDL.h>

#include "s3Dengine.h"

int main(int argc, char* argv[]) {
    
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error\n");
        return 0;
    }

    printf("SDL init success\n");

    SDL_Quit();

    return 0;
}