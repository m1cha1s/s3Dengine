#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <SDL2/SDL.h>

#include "s3Dengine.h"

#define WIDTH 680
#define HEIGHT 480

SDL_Window *window;
SDL_Renderer *renderer;

int init();

int main(int argc, char* argv[]) {
    
    init(); // Initialize SDL2

    S3D_Wall wall = {100, 100, 200, 100};
    S3D_Camera camera = {200, 150, WIDTH/2, HEIGHT/2, 0, 90, 100};

    bool keep_window_open = true;
    while (keep_window_open) {

        // Event loop
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0) {
            switch(e.type) {
                case SDL_QUIT:
                    keep_window_open = false;
                    break;
            }
        }

        // Read keyboard (It works grate now that I moved it out from event loop ;))
        const unsigned char* keystates = SDL_GetKeyboardState(NULL); // Poll the keyboard

        // Movement
        if(keystates[SDL_SCANCODE_W]) S3D_MoveCamera(&camera, FOREWARD, 1.0f);
        if(keystates[SDL_SCANCODE_S]) S3D_MoveCamera(&camera, BACKWARD, 1.0f);
        if(keystates[SDL_SCANCODE_A]) S3D_MoveCamera(&camera, RIGHT, 1.0f);
        if(keystates[SDL_SCANCODE_D]) S3D_MoveCamera(&camera, LEFT, 1.0f);

        // Rotation
        if(keystates[SDL_SCANCODE_J]) S3D_RotateCamera(&camera, -M_PI / 48.0f);
        if(keystates[SDL_SCANCODE_K]) S3D_RotateCamera(&camera, M_PI / 48.0f);

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set color to draw lines
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        S3D_DrawWall(renderer, camera, wall);

        SDL_FRect rect = S3D_RectCamera(camera);
        SDL_RenderDrawRectF(renderer, &rect);
        // SDL_RenderDrawLineF(renderer, camera.cx, camera.cy, camera.cx + 10*cosf(camera.angle), camera.cy + 10*sinf(camera.angle));

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }
    
    printf("Closing window\n");

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error\n");
        return 0;
    }

    printf("SDL init success\n");

    window = SDL_CreateWindow("SDL2 window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    return 0;
}