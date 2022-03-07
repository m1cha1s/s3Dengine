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
        camera.cx - 5, camera.cy - 5, 10, 10
    };

    return rect;
}

void S3D_DrawWall(SDL_Renderer *renderer, S3D_Camera camera, S3D_Wall wall) {
    float tx1 = wall.x1 - camera.x;
    float ty1 = wall.y1 - camera.y;
    float tx2 = wall.x2 - camera.x;
    float ty2 = wall.y2 - camera.y;

    float tz1 = tx1 * cosf(camera.angle) + ty1 * sinf(camera.angle);
    float tz2 = tx2 * cosf(camera.angle) + ty2 * sinf(camera.angle);
    tx1 = tx1 * sinf(camera.angle) - ty1 * cosf(camera.angle);
    tx2 = tx2 * sinf(camera.angle) - ty2 * cosf(camera.angle);

    SDL_RenderDrawLineF(renderer, camera.cx - tx1, camera.cy - tz1, camera.cx - tx2, camera.cy - tz2);
}