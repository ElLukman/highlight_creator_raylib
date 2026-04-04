#include "src/engine_h/highlight.h"
#include "src/engine_h/field.h"
#include "src/engine_h/screen.h"
#include "src/algorithm_h/bresenham.h"
#include "src/algorithm_h/midcircle.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

/*
    Init
*/
void Highlight_Init(
    Highlight *h, const char *title, const char *sub,
    const char *t1, const char *t2, Color c1, Color c2)
{
    memset(h, 0, sizeof(Highlight));
    strncpy(h->title, title, sizeof(h->title)-1);
    strncpy(h->subtitle, sub, sizeof(h->subtitle)-1);
    strncpy(h->team1Name, t1, sizeof(h->team1Name)-1);
    strncpy(h->team2Name, t2, sizeof(h->team2Name));
    h->team1Color = c1;
    h->team2Color = c2;

    h->score1 = 0; 
    h->score2 = 0;
    h->minute = 1;
    
    h->running = false;
    h->finished = false; 
    h->elapsed = 0;
    
    h->nextEvent = 0;
    h->eventCount = 0;
    h->playerCount = 0;
    Ball_Init(&h->ball, FIELD_X + FIELD_W/2.0f, FIELD_Y + FIELD_H/2.0f);
}

void Highlight_AddPlayer(
    Highlight *h, float x, float y, int num,
    Color col, Color numCol)
{
    if(h->playerCount >= MAX_PLAYERS) return;
    Player_Init(&h->players[h->playerCount], x, y, num, col, numCol);
    h->playerCount++;
}

void Highlight_AddEvent(Highlight *h, TimelineEvent ev) 
{
    if (h->eventCount >= MAX_EVENTS) return;
    h->events[h->eventCount++] = ev;
}

/*
    Event Builders
*/
TimelineEvent Evt_BallStraight(float t, float ex, float ey, float dur) 
{
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type = EVT_BALL_STRAIGHT; ev.triggerTime = t;
    ev.bx = ex; ev.by = ey; ev.duration = dur; return ev;
}
TimelineEvent Evt_BallBezier(
    float t, float ex, float ey,
    float cx, float cy, float dur) 
{
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type = EVT_BALL_BEZIER; ev.triggerTime = t;
    ev.bx = ex; ev.by = ey; ev.cx = cx; ev.cy = cy;
    ev.duration = dur; return ev;
}
TimelineEvent Evt_BallHeader(float t, float ex, float ey, float dur) {
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type = EVT_BALL_HEADER; ev.triggerTime = t;
    ev.bx = ex; ev.by = ey; ev.duration = dur; return ev;
}
TimelineEvent Evt_BallTeleport(float t, float bx, float by) {
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type = EVT_BALL_TELEPORT; ev.triggerTime = t;
    ev.bx = bx; ev.by = by; return ev;
}
TimelineEvent Evt_MoveAllPlayers(
    float t, float formX[], float formY[],
    int count, float speed) 
{
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type = EVT_MOVE_PLAYERS; ev.triggerTime = t;
    ev.playerIdx = -1; ev.speed = speed; ev.formCount = count;
    for (int i = 0; i < count && i < MAX_PLAYERS; i++) {
        ev.formX[i] = formX[i]; ev.formY[i] = formY[i];
    }
    return ev;
}
TimelineEvent Evt_MoveSinglePlayer(
    float t, int idx,
    float px, float py, float speed) 
{
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type = EVT_SET_PLAYER_TARGET; ev.triggerTime = t;
    ev.playerIdx = idx; ev.px = px; ev.py = py; ev.speed = speed; return ev;
}

TimelineEvent Evt_ShowText(float t, const char *text, int fontSize, Color col) 
{
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type = EVT_SHOW_TEXT; ev.triggerTime = t;
    strncpy(ev.text, text, 127); ev.fontSize = fontSize;
    ev.textColor = col; return ev;
}

TimelineEvent Evt_HideText(float t) 
{
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type = EVT_HIDE_TEXT; ev.triggerTime = t; return ev;
}

TimelineEvent Evt_ResetFormation(float t, float formX[], float formY[], int count) 
{
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type = EVT_RESET_FORMATION; ev.triggerTime = t; ev.formCount = count;
    for (int i = 0; i < count && i < MAX_PLAYERS; i++) {
        ev.formX[i] = formX[i]; ev.formY[i] = formY[i];
    }
    return ev;
}

TimelineEvent Evt_GoalFlash(float t, Color flashCol) 
{
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type = EVT_GOAL_FLASH; ev.triggerTime = t; ev.textColor = flashCol; return ev;
}

TimelineEvent Evt_Wait(float t) 
{
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type = EVT_WAIT; ev.triggerTime = t; return ev;
}

TimelineEvent Evt_Dribble(
    float t, int playerIdx,
    float ex, float ey, float dur) 
{    
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type       = EVT_DRIBBLE;
    ev.triggerTime = t;
    ev.playerIdx  = playerIdx;
    ev.px = ex; ev.py = ey;   
    ev.bx = ex; ev.by = ey;   
    ev.duration   = dur;
    ev.speed      = 3.5f;
    return ev;
}

TimelineEvent Evt_ScoreUpdate(float t, int s1, int s2, int minute) {
    TimelineEvent ev; memset(&ev, 0, sizeof(ev));
    ev.type       = EVT_SCORE_UPDATE;
    ev.triggerTime = t;
    ev.score1     = s1; ev.score2 = s2; ev.minute = minute;
    return ev;
}

/* 
    Update
*/

void Highlight_Update(Highlight *h, float dt) 
{
    if (!h->running || h->finished) return;
    h->elapsed += dt;

    while (
        h->nextEvent < h->eventCount && 
        h->events[h->nextEvent].triggerTime <= h->elapsed) 
    {
        TimelineEvent *ev = &h->events[h->nextEvent];
        switch (ev->type) 
        {
        case EVT_BALL_STRAIGHT:
            Ball_MoveStraight(&h->ball, ev->bx, ev->by, ev->duration);
            break;
        case EVT_BALL_BEZIER:
            Ball_MoveBezier(&h->ball, ev->bx, ev->by,
                            ev->cx, ev->cy, ev->duration);
            break;
        case EVT_BALL_HEADER:
            Ball_MoveHeader(&h->ball, ev->bx, ev->by, ev->duration);
            break;
        case EVT_BALL_TELEPORT:
            h->ball.x = ev->bx; h->ball.y = ev->by;
            h->ball.sx = ev->bx; h->ball.sy = ev->by;
            h->ball.moving = false;
            break;
        case EVT_MOVE_PLAYERS:
            for (int i = 0; i < ev->formCount && i < h->playerCount; i++)
                Player_SetTarget(
                    &h->players[i], ev->formX[i], ev->formY[i], ev->speed);
            break;

        case EVT_SET_PLAYER_TARGET:
            if (ev->playerIdx >= 0 && ev->playerIdx < h->playerCount)
                Player_SetTarget(&h->players[ev->playerIdx], ev->px, ev->py, ev->speed);
            break;

        case EVT_DRIBBLE: {
            if (ev->playerIdx >= 0 && ev->playerIdx < h->playerCount) 
            {
                Player *p = &h->players[ev->playerIdx];
                float dx = ev->px - p->x;
                float dy = ev->py - p->y;
                float dist = sqrtf(dx*dx + dy*dy);

                float bstart_x = p->x, bstart_y = p->y;
                if (dist > 1.0f) {
                    bstart_x = p->x + (dx/dist) * 25.0f;
                    bstart_y = p->y + (dy/dist) * 25.0f;
                }

                h->ball.x = bstart_x; h->ball.y = bstart_y;
                h->ball.sx = bstart_x; h->ball.sy = bstart_y;
                Ball_MoveStraight(&h->ball, ev->bx, ev->by, ev->duration);

                float spd = (ev->duration > 0.01f)
                            ? (dist / (ev->duration * 60.0f))
                            : 3.5f;
                Player_SetTarget(p, ev->px, ev->py, spd);
            }
            break;
        }

        case EVT_SHOW_TEXT:
            for (int i = 0; i < MAX_OVERLAY_TEXTS; i++) {
                if (!h->overlays[i].visible) {
                    strncpy(h->overlays[i].text, ev->text, 127);
                    h->overlays[i].fontSize  = ev->fontSize;
                    h->overlays[i].color     = ev->textColor;
                    h->overlays[i].x = SCREEN_W/2 - (int)(strlen(ev->text)*ev->fontSize*0.3f);
                    h->overlays[i].y = SCREEN_H - 80;
                    h->overlays[i].alpha   = 1.0f;
                    h->overlays[i].visible = true;
                    break;
                }
            }
            break;

        case EVT_HIDE_TEXT:
            for (int i = 0; i < MAX_OVERLAY_TEXTS; i++)
                h->overlays[i].visible = false;
            break;

        case EVT_RESET_FORMATION:
            for (int i = 0; i < ev->formCount && i < h->playerCount; i++) {
                h->players[i].x  = ev->formX[i];
                h->players[i].y  = ev->formY[i];
                h->players[i].tx = ev->formX[i];
                h->players[i].ty = ev->formY[i];
            }
            break;

        case EVT_GOAL_FLASH:
            h->goalFlash      = true;
            h->goalFlashTimer = 1.5f;
            h->goalFlashColor = ev->textColor;
            break;

        case EVT_SCORE_UPDATE:
            h->score1  = ev->score1;
            h->score2  = ev->score2;
            h->minute  = ev->minute;
            break;

        default: break;
        }
        h->nextEvent++;
    }

    Ball_Update(&h->ball, dt);
    for (int i = 0; i < h->playerCount; i++)
        Player_Update(&h->players[i], dt);

    if (h->goalFlash) {
        h->goalFlashTimer -= dt;
        if (h->goalFlashTimer <= 0) h->goalFlash = false;
    }
}

/* 
    Draw
*/
void Highlight_Draw(const Highlight *h) {
    // Goal Flash Overlay
    if (h->goalFlash) {
        float a = (h->goalFlashTimer / 1.5f) * 0.45f;
        Color fc = h->goalFlashColor;
        fc.a = (unsigned char)(a * 255);
        for (int row = 0; row < SCREEN_H; row += 2)
            BresenhamLine(0, row, SCREEN_W, row, fc);
    }

    for (int i = 0; i < h->playerCount; i++)
        Player_Draw(&h->players[i]);

    Ball_Draw(&h->ball);

    // Overlay texts 
    for (int i = 0; i < MAX_OVERLAY_TEXTS; i++) {
        if (!h->overlays[i].visible) continue;
        DrawText(h->overlays[i].text,
                h->overlays[i].x + 2, h->overlays[i].y + 2,
                h->overlays[i].fontSize, (Color){0,0,0,180});
        DrawText(h->overlays[i].text,
                h->overlays[i].x, h->overlays[i].y,
                h->overlays[i].fontSize, h->overlays[i].color);
    }
}

/*
    HUD
*/
void Highlight_DrawHUD(const Highlight *h) {
    for (int row = 0; row < 38; row++)
        BresenhamLine(0, row, SCREEN_W, row, (Color){10,10,10,220});

    for (int row = 2; row < 36; row++)
        BresenhamLine(4, row, 200, row, h->team1Color);
    for (int row = 2; row < 36; row++)
        BresenhamLine(SCREEN_W-200, row, SCREEN_W-4, row, h->team2Color);

    DrawText(h->team1Name, 10, 10, 20, WHITE);
    DrawText(h->team2Name, SCREEN_W-195, 10, 20, WHITE);

    char score[16];
    snprintf(score, sizeof(score), "%d  -  %d", h->score1, h->score2);
    int sw = MeasureText(score, 28);
    DrawText(score, SCREEN_W/2 - sw/2, 5, 28, YELLOW);

    char min[16];
    snprintf(min, sizeof(min), "%d'", h->minute);
    int mw = MeasureText(min, 13);
    DrawText(min, SCREEN_W/2 - mw/2, 36, 13, (Color){200,200,200,255});

    for (int row = SCREEN_H-32; row < SCREEN_H; row++)
        BresenhamLine(0, row, SCREEN_W, row, (Color){10,10,10,210});
    int tw = MeasureText(h->title, 18);
    DrawText(h->title, SCREEN_W/2 - tw/2, SCREEN_H-28, 18, YELLOW);
    int sw2 = MeasureText(h->subtitle, 14);
    DrawText(h->subtitle, SCREEN_W/2 - sw2/2, SCREEN_H-14, 12, WHITE);
}
