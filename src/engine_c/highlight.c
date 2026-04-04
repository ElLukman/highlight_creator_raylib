#include "src/engine_h/highlight.h"
#include "src/engine_h/field.h"
#include "src/engine_h/screen_size.h"
#include "src/algorithm_h/bresenham.h"
#include "src/algorithm_h/midcircle.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SHAKE_DURATION  5.0f
#define SHAKE_INTENSITY 7.0f

/* ================================================================
    Init
   ================================================================ */

void Highlight_Init(
    Highlight *h,
    const char *title, const char *sub,
    const char *t1, const char *t2,
    Color c1, Color c2)
{
    memset(h, 0, sizeof(Highlight));
    strncpy(h->title,     title, sizeof(h->title) - 1);
    strncpy(h->subtitle,  sub,   sizeof(h->subtitle) - 1);
    strncpy(h->team1Name, t1,    sizeof(h->team1Name) - 1);
    strncpy(h->team2Name, t2,    sizeof(h->team2Name) - 1);
    h->team1Color  = c1;
    h->team2Color  = c2;
    h->playerCount = MAX_PLAYERS;
    h->running     = false;
    h->finished    = false;

    /* Bola di tengah lapangan, tidak bergerak */
    Ball_InitFromDef(&h->ball, &(BallDef){
        FIELD_X + FIELD_W / 2.0f, FIELD_Y + FIELD_H / 2.0f,
        FIELD_X + FIELD_W / 2.0f, FIELD_Y + FIELD_H / 2.0f,
        0, 0, 0.0f, LINEAR
    });
    h->ball.moving = false;

    /* Semua pemain nonaktif sampai di-spawn */
    for (int i = 0; i < MAX_PLAYERS; i++)
        h->players[i].active = false;
}

/* ================================================================
    HL_ API — builder functions (scene-facing)
   ================================================================ */

void AddEvent(Highlight *h, TimelineEvent ev)
{
    if (h->eventCount >= MAX_EVENTS)
        return;
    h->events[h->eventCount++] = ev;
}

void HL_Spawn(Highlight *h, float t, int idx, PlayerDef def)
{
    if (idx < 0 || idx >= MAX_PLAYERS)
        return;
    TimelineEvent ev;
    memset(&ev, 0, sizeof(ev));
    ev.type        = EVT_SPAWN_PLAYER;
    ev.triggerTime = t;
    ev.playerIdx   = idx;
    ev.playerDef   = def;
    AddEvent(h, ev);
}

void HL_Move(Highlight *h, float t, int idx, PlayerDef def)
{
    if (idx < 0 || idx >= MAX_PLAYERS)
        return;
    TimelineEvent ev;
    memset(&ev, 0, sizeof(ev));
    ev.type        = EVT_MOVE_PLAYER;
    ev.triggerTime = t;
    ev.playerIdx   = idx;
    ev.playerDef   = def;
    AddEvent(h, ev);
}

void HL_Sub(Highlight *h, float t, int idx, PlayerDef def)
{
    if (idx < 0 || idx >= MAX_PLAYERS)
        return;
    TimelineEvent ev;
    memset(&ev, 0, sizeof(ev));
    ev.type        = EVT_SUB_PLAYER;
    ev.triggerTime = t;
    ev.playerIdx   = idx;
    ev.playerDef   = def;
    AddEvent(h, ev);
}

void HL_Ball(Highlight *h, float t, BallDef def)
{
    TimelineEvent ev;
    memset(&ev, 0, sizeof(ev));
    ev.type        = EVT_BALL_MOVE;
    ev.triggerTime = t;
    ev.ballDef     = def;
    AddEvent(h, ev);
}

void HL_BallAt(Highlight *h, float t, float x, float y)
{
    TimelineEvent ev;
    memset(&ev, 0, sizeof(ev));
    ev.type        = EVT_BALL_TELEPORT;
    ev.triggerTime = t;
    ev.ballDef     = B(x, y, x, y, 0.0f, LINEAR);
    AddEvent(h, ev);
}

void HL_Text(Highlight *h, float t, const char *text, int size, Color col)
{
    TimelineEvent ev;
    memset(&ev, 0, sizeof(ev));
    ev.type        = EVT_SHOW_TEXT;
    ev.triggerTime = t;
    strncpy(ev.text, text, 127);
    ev.fontSize    = size;
    ev.textColor   = col;
    AddEvent(h, ev);
}

void HL_Hide(Highlight *h, float t)
{
    TimelineEvent ev;
    memset(&ev, 0, sizeof(ev));
    ev.type        = EVT_HIDE_TEXT;
    ev.triggerTime = t;
    AddEvent(h, ev);
}

void HL_Goal(Highlight *h, float t, int s1, int s2, int minute)
{
    /* GoalFlash */
    TimelineEvent ef;
    memset(&ef, 0, sizeof(ef));
    ef.type        = EVT_GOAL_FLASH;
    ef.triggerTime = t;
    AddEvent(h, ef);

    /* ScoreUpdate */
    TimelineEvent es;
    memset(&es, 0, sizeof(es));
    es.type        = EVT_SCORE_UPDATE;
    es.triggerTime = t;
    es.score1      = s1;
    es.score2      = s2;
    es.minute      = minute;
    AddEvent(h, es);
}

void HL_Wait(Highlight *h, float t)
{
    TimelineEvent ev;
    memset(&ev, 0, sizeof(ev));
    ev.type        = EVT_WAIT;
    ev.triggerTime = t;
    AddEvent(h, ev);
}

/* ================================================================
    Update
   ================================================================ */

void Highlight_Update(Highlight *h, float dt)
{
    if (!h->running || h->finished)
        return;

    h->elapsed += dt;

    /* Fire events */
    while (h->nextEvent < h->eventCount &&
           h->events[h->nextEvent].triggerTime <= h->elapsed)
    {
        TimelineEvent *ev = &h->events[h->nextEvent];

        switch (ev->type)
        {
        case EVT_SPAWN_PLAYER:
        {
            /* Inisialisasi penuh: posisi, identitas, tujuan */
            Player *p = &h->players[ev->playerIdx];
            Player_InitFromDef(p, &ev->playerDef);
            p->active = true;
            break;
        }

        case EVT_MOVE_PLAYER:
        {
            /* Hanya ubah tujuan pemain yang sudah ada */
            Player *p = &h->players[ev->playerIdx];
            if (p->active)
                Player_SetTarget(p,
                    ev->playerDef.ex, ev->playerDef.ey,
                    ev->playerDef.dur, ev->playerDef.moveType);
            break;
        }

        case EVT_SUB_PLAYER:
        {
            /* Ganti nama dan nomor, posisi tidak berubah */
            Player *p = &h->players[ev->playerIdx];
            p->num    = ev->playerDef.num;
            strncpy(p->name, ev->playerDef.name, 23);
            p->name[23] = '\0';
            break;
        }

        case EVT_BALL_MOVE:
        {
            Ball_InitFromDef(&h->ball, &ev->ballDef);
            break;
        }

        case EVT_BALL_TELEPORT:
        {
            h->ball.x      = ev->ballDef.x;
            h->ball.y      = ev->ballDef.y;
            h->ball.sx     = ev->ballDef.x;
            h->ball.sy     = ev->ballDef.y;
            h->ball.moving = false;
            break;
        }

        case EVT_SHOW_TEXT:
        {
            for (int i = 0; i < MAX_OVERLAY_TEXTS; i++)
            {
                if (!h->overlays[i].visible)
                {
                    strncpy(h->overlays[i].text, ev->text, 127);
                    h->overlays[i].fontSize = ev->fontSize;
                    h->overlays[i].color    = ev->textColor;
                    h->overlays[i].x = SCREEN_W / 2
                        - (int)(strlen(ev->text) * ev->fontSize * 0.3f);
                    h->overlays[i].y = SCREEN_H - 80;
                    h->overlays[i].visible = true;
                    break;
                }
            }
            break;
        }

        case EVT_HIDE_TEXT:
            for (int i = 0; i < MAX_OVERLAY_TEXTS; i++)
                h->overlays[i].visible = false;
            break;

        case EVT_GOAL_FLASH:
            h->shakeTimer     = SHAKE_DURATION;
            h->shakeIntensity = SHAKE_INTENSITY;
            break;

        case EVT_SCORE_UPDATE:
            h->score1  = ev->score1;
            h->score2  = ev->score2;
            h->minute  = ev->minute;
            break;

        case EVT_WAIT:
            /* Tandai selesai ketika event wait diproses */
            h->finished = true;
            break;

        default:
            break;
        }

        h->nextEvent++;
    }

    /* Update semua pemain */
    Ball_Update(&h->ball, dt);
    for (int i = 0; i < MAX_PLAYERS; i++)
        Player_Update(&h->players[i], dt);

    /* Update screen shake */
    if (h->shakeTimer > 0.0f)
    {
        h->shakeTimer -= dt;
        if (h->shakeTimer <= 0.0f)
        {
            h->shakeTimer = 0.0f;
            h->shakeOffsetX = 0;
            h->shakeOffsetY = 0;
        }
        else
        {
            float progress = h->shakeTimer / SHAKE_DURATION;
            float intensity = h->shakeIntensity * progress;
            h->shakeOffsetX = (int)(
                (((float)(rand() % 200) / 100.0f) - 1.0f) * intensity);
            h->shakeOffsetY = (int)(
                (((float)(rand() % 200) / 100.0f) - 1.0f) * intensity);
        }
    }
}

/* ================================================================
    Draw
   ================================================================ */

void Highlight_Draw(const Highlight *h)
{
    int ox = h->shakeOffsetX;
    int oy = h->shakeOffsetY;

    /* Gambar semua pemain dengan shake offset */
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (!h->players[i].active)
            continue;
        Player shaken = h->players[i];
        shaken.x += ox;
        shaken.y += oy;
        Player_Draw(&shaken);
    }

    /* Bola dengan shake offset */
    Ball shakenBall = h->ball;
    shakenBall.x += ox;
    shakenBall.y += oy;
    Ball_Draw(&shakenBall);

    /* Overlay teks (tidak ikut shake agar tetap terbaca) */
    for (int i = 0; i < MAX_OVERLAY_TEXTS; i++)
    {
        if (!h->overlays[i].visible)
            continue;
        DrawText(
            h->overlays[i].text,
            h->overlays[i].x + 2, h->overlays[i].y + 2,
            h->overlays[i].fontSize, (Color){0, 0, 0, 180});
        DrawText(
            h->overlays[i].text,
            h->overlays[i].x, h->overlays[i].y,
            h->overlays[i].fontSize, h->overlays[i].color);
    }
}

/* ================================================================
    HUD
   ================================================================ */

void Highlight_DrawHUD(const Highlight *h)
{
    /* Bar atas */
    for (int row = 0; row < 38; row++)
        BresenhamLine(0, row, SCREEN_W, row, (Color){10, 10, 10, 220});

    for (int row = 2; row < 36; row++)
        BresenhamLine(4, row, 200, row, h->team1Color);
    for (int row = 2; row < 36; row++)
        BresenhamLine(SCREEN_W - 200, row, SCREEN_W - 4, row, h->team2Color);

    DrawText(h->team1Name, 10, 10, 20, WHITE);
    DrawText(h->team2Name, SCREEN_W - 195, 10, 20, WHITE);

    char score[16];
    snprintf(score, sizeof(score), "%d  -  %d", h->score1, h->score2);
    int sw = MeasureText(score, 28);
    DrawText(score, SCREEN_W / 2 - sw / 2, 5, 28, YELLOW);

    char min[16];
    snprintf(min, sizeof(min), "%d'", h->minute);
    int mw = MeasureText(min, 13);
    DrawText(min, SCREEN_W / 2 - mw / 2, 36, 13, (Color){200, 200, 200, 255});

    /* Bar bawah */
    for (int row = SCREEN_H - 32; row < SCREEN_H; row++)
        BresenhamLine(0, row, SCREEN_W, row, (Color){10, 10, 10, 210});
    int tw = MeasureText(h->title, 18);
    DrawText(h->title, SCREEN_W / 2 - tw / 2, SCREEN_H - 28, 18, YELLOW);
    int sw2 = MeasureText(h->subtitle, 14);
    DrawText(h->subtitle, SCREEN_W / 2 - sw2 / 2, SCREEN_H - 14, 12, WHITE);
}

TimelineEvent Evt_ScoreUpdate(float t, int s1, int s2, int minute) {
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type       = EVT_SCORE_UPDATE;
    ev.triggerTime = t;
    ev.score1     = s1; ev.score2 = s2; ev.minute = minute;
    return ev;
}
