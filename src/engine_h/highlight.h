#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include "raylib.h"
#include "src/engine_h/player.h"
#include <stdbool.h>

/*
    TIMELINE EVENT
*/

#define MAX_EVENTS 128

typedef enum {
    EVT_NONE = 0,
    EVT_BALL_STRAIGHT,      // Ball moves straight (easing)
    EVT_BALL_BEZIER,        // Ball moves on bezier arc
    EVT_BALL_HEADER,        // Ball header arc           
    EVT_MOVE_PLAYERS,       // Move all/subset of players
    EVT_SET_PLAYER_TARGET,  // Move single player
    EVT_SHOW_TEXT,          // Show overlay text                    
    EVT_HIDE_TEXT,          // Hide overlay text          
    EVT_RESET_FORMATION,    // Teleport all players to pos          
    EVT_BALL_TELEPORT,      // Teleport ball                  
    EVT_WAIT,               // Just wait N seconds               
    EVT_GOAL_FLASH,         // Goal celebration flash        
    EVT_DRIBBLE,            // Player dribbles ball together        
    EVT_SCORE_UPDATE,       // Update scoreboard
} EventType;


typedef struct {
    EventType type;
    float     triggerTime;   /* seconds from highlight start */

    /* Ball moves */
    float bx, by;
    float cx, cy;
    float duration;

    /* Player moves */
    int   playerIdx;         /* -1 = all players */
    float px, py;
    float speed;

    /* Text */
    char  text[128];
    int   fontSize;
    Color textColor;

    /* Formation reset */
    float formX[MAX_PLAYERS];
    float formY[MAX_PLAYERS];
    int   formCount;

    /* Score update */
    int   score1, score2;
    int   minute;
} TimelineEvent;

/* 
    HIGHLIGHT STATE
*/

#define MAX_OVERLAY_TEXTS 4


typedef struct {
    char  text[128];
    int   x, y;
    int   fontSize;
    Color color;
    float alpha;
    bool  visible;
} OverlayText;

typedef struct {
    char  title[64];
    char  subtitle[128];

    Player players[MAX_PLAYERS];
    int    playerCount;

    Ball   ball;

    TimelineEvent events[MAX_EVENTS];
    int           eventCount;
    int           nextEvent;

    float  elapsed;
    bool   running;
    bool   finished;

    bool   goalFlash;
    float  goalFlashTimer;
    Color  goalFlashColor;

    OverlayText overlays[MAX_OVERLAY_TEXTS];

    char  team1Name[32];
    char  team2Name[32];
    int   score1, score2;
    int   minute;
    Color team1Color;
    Color team2Color;
} Highlight;

/*
    API
*/
void Highlight_Init(Highlight *h, const char *title, const char *sub,
                    const char *t1, const char *t2,
                    Color c1, Color c2);
void Highlight_AddPlayer(Highlight *h, float x, float y, int num,
                         Color col, Color numCol);
void Highlight_AddEvent(Highlight *h, TimelineEvent ev);

// Event Builders
TimelineEvent Evt_BallStraight(float t, float ex, float ey, float dur);
TimelineEvent Evt_BallBezier(float t, float ex, float ey,
                              float cx, float cy, float dur);
TimelineEvent Evt_BallHeader(float t, float ex, float ey, float dur);
TimelineEvent Evt_BallTeleport(float t, float bx, float by);
TimelineEvent Evt_MoveAllPlayers(float t, float formX[], float formY[],
                                  int count, float speed);
TimelineEvent Evt_MoveSinglePlayer(float t, int idx,
                                   float px, float py, float speed);
TimelineEvent Evt_ShowText(float t, const char *text, int fontSize, Color col);
TimelineEvent Evt_HideText(float t);
TimelineEvent Evt_ResetFormation(float t, float formX[], float formY[], int count);
TimelineEvent Evt_GoalFlash(float t, Color flashCol);
TimelineEvent Evt_Wait(float t);

/*
    Event_Dribble - pemain dan bola bergerak bersama ke (ex, ey)
    Bola selalu offset +25px di depan pemain (arah gerakan)
    playerIdx: index pemain yang dribble
    ex, ey   : tujuan akhir pemain (bola ikut)
    dur      : durasi dribble
*/
TimelineEvent Evt_Dribble(float t, int playerIdx,
                           float ex, float ey, float dur);

/* 
    Evt_ScoreUpdate
*/
TimelineEvent Evt_ScoreUpdate(float t, int s1, int s2, int minute);

void Highlight_Update(Highlight *h, float dt);
void Highlight_Draw(const Highlight *h);
void Highlight_DrawHUD(const Highlight *h);

#endif