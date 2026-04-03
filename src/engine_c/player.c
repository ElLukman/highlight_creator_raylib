#include "src/engine_h/player.h"
#include "src/engine_h/field.h"
#include "src/algorithm_h/bresenham.h"
#include "src/algorithm_h/midcircle.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

/*
    Easing Function (Opsi untuk animasi)
*/



// Ease-out cubic: mulai cepat, lambat di akhir
static float EaseOutCubic(float t)
{
    float f = 1.0f - t;
    return 1.0f - f * f * f;
}

// Ease-in-out cubic: lambat-cepat-lambat (untuk lemparan/sundulan)
static float EaseInOutCubic(float t)
{
    if (t < 0.5f)
        return 4.0f * t * t * t;
    float f = -2.0f * t + 2.0f;
    return 1.0f - f * f * f / 2.0f;
}

/*
    Player Movement
*/

void Player_Init(
    Player *p, float x, float y, int number,
    Color col, Color numCol)
{
    p->x = x;
    p->y = y;
    p->tx = x;
    p->ty = y;
    p->speed = 2.0f;
    p->number = number;
    p->color = col;
    p->numColor = numCol;
    p->active = true;
}

void Player_SetTarget(Player *p, float tx, float ty, float speed)
{
    p->tx = tx;
    p->ty = ty;
    p->speed = speed;
}

void Player_Update(Player *p, float dt)
{
    if (!p->active)
        return;
    float dx = p->tx - p->x;
    float dy = p->ty - p->y;
    float dist = sqrtf(dx * dx + dy * dy);
    if (dist < 0.5f)
    {
        p->x = p->tx;
        p->y = p->ty;
        return;
    }

    float max_step = p->speed * 60.0f * dt;
    float ease_factor = dist / (dist + 40.0f);
    float step = max_step * (0.4f + 0.6f * ease_factor);
    if (step > dist)
        step = dist;

    p->x += (dx / dist) * step;
    p->y += (dy / dist) * step;
}

void Player_Draw(const Player *p)
{
    if (!p->active)
        return;
    int cx = (int)p->x, cy = (int)p->y;

    // Shadow
    MidcircleFilled(cx + 3, cy + 4, PLAYER_RADIUS, (Color){0, 0, 0, 55});

    // Body
    MidcircleFilled(cx, cy, PLAYER_RADIUS, p->color);

    // White outline
    Midcircle(cx, cy, PLAYER_RADIUS, WHITE);

    // Jersey number
    char buf[4];
    snprintf(buf, sizeof(buf), "%d", p->number);
    int tw = MeasureText(buf, 10);
    DrawText(buf, cx - tw / 2, cy - 5, 10, p->numColor);
}

void Players_MoveAll(Player players[], int count,
                     float baseX[], float baseY[], float speed)
{
    for (int i = 0; i < count; i++)
        Player_SetTarget(&players[i], baseX[i], baseY[i], speed);
}

/*
    Ball Movement
*/

void Ball_Init(Ball *b, float x, float y)
{
    b->x = x;
    b->y = y;
    b->sx = x;
    b->sy = y;
    b->ex = x;
    b->ey = y;
    b->cx = x;
    b->cy = y;
    b->t = 0;
    b->duration = 1.0f;
    b->elapsed = 0;
    b->moveType = BALL_STRAIGHT;
    b->moving = false;
    b->radius = 8;
    b->inGoal = false;
}

void Ball_MoveStraight(Ball *b, float ex, float ey, float duration)
{
    b->sx = b->x;
    b->sy = b->y;
    b->ex = ex;
    b->ey = ey;
    b->duration = duration;
    b->elapsed = 0;
    b->t = 0;
    b->moveType = BALL_STRAIGHT;
    b->moving = true;
}

void Ball_MoveBezier(Ball *b, float ex, float ey, float cx, float cy, float duration)
{
    b->sx = b->x;
    b->sy = b->y;
    b->ex = ex;
    b->ey = ey;
    b->cx = cx;
    b->cy = cy;
    b->duration = duration;
    b->elapsed = 0;
    b->t = 0;
    b->moveType = BALL_BEZIER;
    b->moving = true;
}

void Ball_MoveHeader(Ball *b, float ex, float ey, float duration)
{
    float mx = (b->x + ex) * 0.5f;
    float my = (b->y + ey) * 0.5f - 90.0f;
    Ball_MoveBezier(b, ex, ey, mx, my, duration);
}

void Ball_Update(Ball *b, float dt)
{
    if (!b->moving)
        return;
    b->elapsed += dt;
    float raw_t = b->elapsed / b->duration;
    if (raw_t >= 1.0f)
    {
        raw_t = 1.0f;
        b->moving = false;
    }

    if (b->moveType == BALL_STRAIGHT)
    {
        /*
         * FIX animasi bola kaku:
         * Dulu: raw_t langsung dipakai → constant velocity
         * Sekarang: ease-out cubic → melambat saat mendekati tujuan
         */
        float et = EaseOutCubic(raw_t);
        b->x = b->sx + (b->ex - b->sx) * et;
        b->y = b->sy + (b->ey - b->sy) * et;
    }
    else
    {
        // Quadratic Bezier: B(t) = (1-t)^2*P0 + 2(1-t)t*P1 + t^2*P2
        float et = EaseInOutCubic(raw_t);
        float inv = 1.0f - et;
        b->x = inv * inv * b->sx + 2.0f * inv * et * b->cx + et * et * b->ex;
        b->y = inv * inv * b->sy + 2.0f * inv * et * b->cy + et * et * b->ey;
    }
    b->t = raw_t;
}

void Ball_Draw(const Ball *b)
{
    int bx = (int)b->x, by = (int)b->y;
    MidcircleFilled(bx, by, 6, (Color){255, 255, 255, 255});
    Midcircle(bx, by, 6, (Color){0, 0, 0, 255});
    DrawPixel(bx, by, (Color){0, 0, 0, 255});
}
