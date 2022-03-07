#ifndef S3DENGINE_H
#define S3DENGINE_H

#include <SDL2/SDL.h>

typedef enum S3D_Direction {
    FOREWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
} S3D_Direction;

typedef struct S3D_Camera {
    float x, y;
    float cx, cy;
    float angle;
    float fov;
    float renderDistance;
} S3D_Camera;

typedef struct S3D_Wall {
    float x1, y1;
    float x2, y2;
} S3D_Wall;

void S3D_MoveCamera(S3D_Camera *camera, S3D_Direction direction, float distance);
void S3D_RotateCamera(S3D_Camera *camera, float angle);

SDL_FRect S3D_RectCamera(S3D_Camera camera);

void S3D_DrawWall(SDL_Renderer *renderer, S3D_Camera camera, S3D_Wall wall);

#endif