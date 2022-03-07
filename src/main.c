#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "s3Dengine.h"

int main(int argc, char* argv[]) {
    
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error\n");
        return 0;
    }

    printf("SDL init success\n");

    SDL_Window *window = SDL_CreateWindow("SDL2 window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    bool keep_window_open = true;
    while (keep_window_open) {
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0) {
            switch(e.type) {
                case SDL_QUIT:
                    keep_window_open = false;
                    break;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, 0, 0, 200, 200);

            SDL_RenderPresent(renderer);
        }
    }
    
    printf("Closing window\n");

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}