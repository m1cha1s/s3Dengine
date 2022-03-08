#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <SDL2/SDL.h>

#include "s3Dengine.h"

#define WIDTH 680
#define HEIGHT 480

#define WALKING_SPEED 0.05f
#define ROTATION_SPEED 0.01f

SDL_Window *window;
SDL_Renderer *renderer;

int init();

int main(int argc, char* argv[]) {
    
    init(); // Initialize SDL2


    Map map = ReadMapFile("map.map");
    
    Player player = {{0, 0}, 0, M_PI/6.0, 100};
    
    player.pos.x = map.spawn.x;
    player.pos.y = map.spawn.y;

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
        if(keystates[SDL_SCANCODE_W]) MovePlayer(&player, FOREWARD, WALKING_SPEED);
        if(keystates[SDL_SCANCODE_S]) MovePlayer(&player, BACKWARD, WALKING_SPEED);
        if(keystates[SDL_SCANCODE_A]) MovePlayer(&player, RIGHT, WALKING_SPEED);
        if(keystates[SDL_SCANCODE_D]) MovePlayer(&player, LEFT, WALKING_SPEED);

        // Rotation
        if(keystates[SDL_SCANCODE_J]) RotatePlayer(&player, -ROTATION_SPEED);
        if(keystates[SDL_SCANCODE_K]) RotatePlayer(&player, ROTATION_SPEED);

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set color to draw lines
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        RenderPlayer(renderer, player, map);

        // for(int wall = 0; wall < map.wallCount; wall ++) {
        //     SDL_RenderDrawLineF(renderer, walls[wall].p1.x, walls[wall].p1.y, walls[wall].p2.x, walls[wall].p2.y);
        // }

        // SDL_RenderDrawLineF(renderer, player.pos.x, player.pos.y, 20 * cosf(player.angle) + player.pos.x, 20 * sinf(player.angle) + player.pos.y);


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