#include "s3Dengine.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void MovePlayer(Player *player, Direction direction, float distance) {
    switch (direction) {
    case FOREWARD:
        player->pos.x += distance * cosf(player->angle);
        player->pos.y += distance * sinf(player->angle);
        break;
    
    case BACKWARD:
        player->pos.x += distance * cosf(player->angle + M_PI);
        player->pos.y += distance * sinf(player->angle + M_PI);
        break;

    case LEFT:
        player->pos.x += distance * cosf(player->angle + M_PI/2.0f);
        player->pos.y += distance * sinf(player->angle + M_PI/2.0f);
        break;

    case RIGHT:
        player->pos.x += distance * cosf(player->angle - M_PI/2.0f);
        player->pos.y += distance * sinf(player->angle - M_PI/2.0f);
        break;

    default:
        break;
    }
}

void RotatePlayer(Player *player, float angle) {
    player->angle += angle;
}

void RenderPlayer(SDL_Renderer *renderer, Player player, Map map) {
    Ray ray = {player.pos, player.angle - player.fov / 2.0};
    for(float angle = 0; angle < 680.0; angle ++) {
        ray.angle += player.fov / 680.0;
        float dist = INFINITY;
        for(int wall = 0; wall < map.wallCount; wall ++) {
            Hit hit = RayCast(ray, map.walls[wall]);

            if(hit.hit) {
                float xDiffSq = (hit.pos.x - player.pos.x) * (hit.pos.x - player.pos.x);
                float yDiffSq = (hit.pos.y - player.pos.y) * (hit.pos.y - player.pos.y);
                float d = sqrtf(xDiffSq + yDiffSq);

                if(d < dist)
                    dist = d;
            }
        }

        if(dist != INFINITY) {
            uint8_t brightness = 255.0f/(dist);
            float height = 480 * (1 / tanf(M_PI/6)) / dist;

            SDL_SetRenderDrawColor(renderer, brightness, brightness, brightness, 255);

            SDL_RenderDrawLineF(renderer, angle, 240 + height/2, angle, 240 - height/2);
        }
    }
}

Map ReadMapFile(char *filename) {
    FILE *map = fopen(filename, "r");

    char line[160] = {0};

    Map m;

    int wallIdx = 0;

    bool firstLine = true;
    while(fgets(line, 160, map)) {
        int idx = 0;
        for(char* tok = strtok(line, ","); tok != NULL; tok = strtok(NULL, ",")) {
            if(!firstLine) {
                switch (idx) {
                case 0:
                    m.walls[wallIdx].p1.x = atof(tok);
                    break;

                case 1:
                    m.walls[wallIdx].p1.y = atof(tok);
                    break;

                case 2:
                    m.walls[wallIdx].p2.x = atof(tok);
                    break;

                case 3:
                    m.walls[wallIdx].p2.y = atof(tok);
                    break;
                
                default:
                    break;
                }
            } else {
                switch(idx) {
                case 0:
                    m.walls = malloc(sizeof(Wall) * atoi(line));
                    m.wallCount = atoi(tok);
                    break;
                    
                case 1:
                    m.spawn.x = atof(tok);
                    break;

                case 2:
                    m.spawn.y = atof(tok);
                    break;
                }
            }

            idx++;
        }

        firstLine = false;
        wallIdx++;
    }

    fclose(map);

    return m;
}

Hit RayCast(Ray ray, Wall wall) {
    float x1 = wall.p1.x;
    float y1 = wall.p1.y;
    float x2 = wall.p2.x;
    float y2 = wall.p2.y;

    float x3 = ray.pos.x;
    float y3 = ray.pos.y;
    float x4 = ray.pos.x + cosf(ray.angle);
    float y4 = ray.pos.y + sinf(ray.angle);

    float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    Hit hit;

    hit.hit = false;

    // If ray is not parallel
    if(!den) {
        return hit;
    }

    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    float u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) / den;

    // If ray hit
    if(t >= 0 && t <= 1 && u >=0) {
        hit.hit = true;

        hit.pos.x = x1 + t * (x2 - x1);
        hit.pos.y = y1 + t * (y2 - y1);
    }

    return hit;
}