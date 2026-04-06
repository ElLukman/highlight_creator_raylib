#include "src/engine_h/player.h"
#include "src/engine_h/field.h"
#include "src/algorithm_h/bresenham.h"
#include "src/algorithm_h/midcircle.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

/*
    Easing Functions
    Semua menerima t dalam [0,1] dan mengembalikan nilai [0,1].
*/

static float Ease_Linear(float t)
{
    return t;
}

static float Ease_Out(float t)
{
    float f = 1.0f - t;
    return 1.0f - f * f * f;
}

static float Ease_In(float t)
{
    return t * t * t;
}

static float Ease_InOut(float t)
{
    if (t < 0.5f)
        return 4.0f * t * t * t;
    float f = -2.0f * t + 2.0f;
    return 1.0f - f * f * f / 2.0f;
}

static float ApplyEasing(float t, MoveType mt)
{
    switch (mt)
    {
    case LINEAR:      return Ease_Linear(t);
    case EASE_OUT:    return Ease_Out(t);
    case EASE_IN:     return Ease_In(t);
    case EASE_IN_OUT: return Ease_InOut(t);
    default:          return Ease_Out(t);
    }
}

/*
    Player
*/

void Player_InitFromDef(Player *p, const PlayerDef *def)
{
    p->x          = def->x;
    p->y          = def->y;
    p->tx         = def->ex;
    p->ty         = def->ey;
    p->speed      = 0.0f;
    p->moveType   = def->moveType;
    p->moveElapsed = 0.0f;
    p->moveDur    = def->dur;
    p->startX     = def->x;
    p->startY     = def->y;
    p->num        = def->num;
    p->color      = def->color;
    p->numColor   = def->numColor;
    p->active     = true;
    strncpy(p->name, def->name, 23);
    p->name[23] = '\0';
}

void Player_SetTarget(Player *p, float tx, float ty,
                      float dur, MoveType mt)
{
    p->startX     = p->x;
    p->startY     = p->y;
    p->tx         = tx;
    p->ty         = ty;
    p->moveDur    = dur;
    p->moveType   = mt;
    p->moveElapsed = 0.0f;
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

    if (p->moveDur <= 0.0f)
    {
        /* Tidak ada durasi: langsung teleport */
        p->x = p->tx;
        p->y = p->ty;
        return;
    }

    p->moveElapsed += dt;
    float rawT = p->moveElapsed / p->moveDur;
    if (rawT >= 1.0f)
    {
        rawT = 1.0f;
        p->x = p->tx;
        p->y = p->ty;
        return;
    }

    float et = ApplyEasing(rawT, p->moveType);
    p->x = p->startX + (p->tx - p->startX) * et;
    p->y = p->startY + (p->ty - p->startY) * et;
}

void Player_Draw(const Player *p)
{
    if (!p->active)
        return;

    int cx = (int)p->x, cy = (int)p->y;
    Vector2 cpos = { (float)cx, (float)cy };

    /* Shadow — satu GPU call */
    DrawCircleV((Vector2){(float)(cx+2),(float)(cy+3)},
                (float)PLAYER_RADIUS, (Color){0,0,0,60});

    /* Body — satu GPU call */
    DrawCircleV(cpos, (float)PLAYER_RADIUS, p->color);

    /* Outline putih — satu GPU call */
    DrawCircleLines(cx, cy, (float)PLAYER_RADIUS, WHITE);

    /* Nomor punggung */
    char buf[4];
    snprintf(buf, sizeof(buf), "%d", p->num);
    int tw = MeasureText(buf, 10);
    DrawText(buf, cx - tw / 2, cy - 5, 10, p->numColor);
}

/*
    Ball
*/

static float BezierPoint(float p0, float p1, float p2, float t)
{
    float inv = 1.0f - t;
    return inv * inv * p0 + 2.0f * inv * t * p1 + t * t * p2;
}

void Ball_InitFromDef(Ball *b, const BallDef *def)
{
    b->x        = def->x;
    b->y        = def->y;
    b->sx       = def->x;
    b->sy       = def->y;
    b->ex       = def->ex;
    b->ey       = def->ey;
    b->cx       = def->cx;
    b->cy       = def->cy;
    b->duration = def->dur;
    b->elapsed  = 0.0f;
    b->t        = 0.0f;
    b->moveType = def->moveType;
    b->moving   = (def->dur > 0.0f);
    b->radius   = 8;
    b->inGoal   = false;
}

void Ball_Update(Ball *b, float dt)
{
    if (!b->moving)
        return;

    b->elapsed += dt;
    float rawT = b->elapsed / b->duration;
    if (rawT >= 1.0f)
    {
        rawT = 1.0f;
        b->moving = false;
    }

    b->t = rawT;

    if (b->moveType == BEZIER)
    {
        /* Quadratic Bezier dengan EASE_IN_OUT */
        float et = Ease_InOut(rawT);
        b->x = BezierPoint(b->sx, b->cx, b->ex, et);
        b->y = BezierPoint(b->sy, b->cy, b->ey, et);
    }
    else
    {
        float et = ApplyEasing(rawT, b->moveType);
        b->x = b->sx + (b->ex - b->sx) * et;
        b->y = b->sy + (b->ey - b->sy) * et;
    }
}

// SESUDAH:
void Ball_Draw(const Ball *b)
{
    int bx = (int)b->x, by = (int)b->y;

    // Shadow
    MidcircleFilled(bx + 4, by + 2, 7, (Color){0, 0, 0, 60});

    // Glow luar 
    MidcircleFilled(bx, by, 12, (Color){255, 255, 200, 40});

    // Badan bola
    MidcircleFilled(bx, by, 6, (Color){255, 255, 255, 255});

    // Outline hitam kontras
    Midcircle(bx, by, 8, (Color){0, 0, 0, 220});

    // Outline putih tipis di luar hitam (double-ring)
    Midcircle(bx, by, 10, (Color){255, 255, 255, 100});
}