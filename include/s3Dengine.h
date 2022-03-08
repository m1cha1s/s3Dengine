#ifndef S3DENGINE_H
#define S3DENGINE_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef enum Direction {
    FOREWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
} Direction;

typedef struct xy {
    float x,y;
} xy;

typedef struct Hit {
    bool hit;
    xy pos;
}Hit;

typedef struct Player {
    xy pos;
    float angle;
    float fov;
    float renderDistance;
} Player;

typedef struct Wall {
    xy p1, p2;
} Wall;

typedef struct Map {
    int wallCount;
    Wall *walls;
    xy spawn;
}Map;

typedef struct Ray {
    xy pos;
    float angle;
} Ray;

float mapf(float x, float in_min, float in_max, float out_min, float out_max);

void MovePlayer(Player *player, Direction direction, float distance);
void RotatePlayer(Player *player, float angle);
void RenderPlayer(SDL_Renderer *renderer, Player player, Map map);

Map ReadMapFile(char *filename);

Hit RayCast(Ray ray, Wall wall);


#endif