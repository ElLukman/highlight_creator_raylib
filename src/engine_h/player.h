#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <stdbool.h>

// Player
#define MAX_PLAYERS 22 
#define PLAYER_RADIUS 14

typedef struct {
    float x, y;         /* current position (pixels) */
    float tx, ty;       /* target position (pixels) */
    float speed;        /* movement speed px/frame */
    int   number;       /* jersey number */
    Color color;        /* team color */
    Color numColor;     /* number text color */
    bool  active;
} Player;

// Ball
typedef enum {
    BALL_STRAIGHT,   /* easing-out linear move */
    BALL_BEZIER,     /* quadratic bezier arc   */
    BALL_HEADER      /* short parabola header  */
} BallMoveType;

typedef struct {
    float x, y;
    float sx, sy;         /* start position */
    float ex, ey;         /* end position */
    float cx, cy;         /* bezier control point */
    float t;              /* normalised time [0,1] */
    float duration;       /* seconds for this move */
    float elapsed;
    BallMoveType moveType;
    bool  moving;
    int   radius;
    bool  inGoal;
} Ball;

/*
API 
*/

// Player helpers
void Player_Init(
    Player *p, float x, float y, int number, 
    Color col, Color numCol
);
void Player_SetTarget(Player *p, float tx, float ty, float speed);
void Player_Update(Player *p, float dt);
void Player_Draw(const Player *p);

// Move All Player
void Players_MoveAll(
    Player players[], int count,
    float baseX[], float baseY[], float speed
);

/* Ball helpers */
void Ball_Init(Ball *b, float x, float y);
void Ball_MoveStraight(Ball *b, float ex, float ey, float duration);
void Ball_MoveBezier(Ball *b, float ex, float ey, float cx, float cy, float duration);
void Ball_MoveHeader(Ball *b, float ex, float ey, float duration);
void Ball_Update(Ball *b, float dt);
void Ball_Draw(const Ball *b);

#endif