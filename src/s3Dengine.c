#include "s3Dengine.h"

#include <math.h>

void S3D_MoveCamera(S3D_Camera *camera, S3D_Direction direction, float distance) {
    switch (direction) {
    case FOREWARD:
        camera->x += distance * cosf(camera->angle);
        camera->y += distance * sinf(camera->angle);
        break;
    
    case BACKWARD:
        camera->x += distance * cosf(camera->angle + M_PI);
        camera->y += distance * sinf(camera->angle + M_PI);
        break;

    case LEFT:
        camera->x += distance * cosf(camera->angle + M_PI/2.0f);
        camera->y += distance * sinf(camera->angle + M_PI/2.0f);
        break;

    case RIGHT:
        camera->x += distance * cosf(camera->angle - M_PI/2.0f);
        camera->y += distance * sinf(camera->angle - M_PI/2.0f);
        break;

    default:
        break;
    }
}

void S3D_RotateCamera(S3D_Camera *camera, float angle) {
    camera->angle += angle;
}

SDL_FRect S3D_RectCamera(S3D_Camera camera) {
    SDL_FRect rect = {
        camera.x - 5, camera.y - 5, 10, 10
    };

    return rect;
}

void S3D_DrawWall(SDL_Renderer *renderer, S3D_Camera camera, S3D_Wall wall) {
    SDL_RenderDrawLineF(renderer, wall.x1, wall.y1, wall.x2, wall.y2);
}