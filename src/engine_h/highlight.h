#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include "raylib.h"
#include "src/engine_h/player.h"
#include <stdbool.h>

/* ================================================================
    TIMELINE EVENT
   ================================================================ */

#define MAX_EVENTS 2000
#define MAX_HISTORY 64

typedef enum
{
    EVT_NONE = 0,

    /*
        Event baru (Sprint 6) — dipakai oleh fungsi HL_* di bawah.
        Setiap gol menginisialisasi pemain dari awal menggunakan
        EVT_SPAWN_PLAYER, lalu menggerakkannya dengan EVT_MOVE_PLAYER.
    */
    EVT_SPAWN_PLAYER,   /* Teleport + set identitas + beri tujuan  */
    EVT_MOVE_PLAYER,    /* Ubah tujuan pemain yg sudah ada         */
    EVT_SUB_PLAYER,     /* Ganti nama & nomor (substitusi)         */
    EVT_BALL_MOVE,      /* Gerakkan bola (semua tipe termasuk Bezier)*/
    EVT_BALL_TELEPORT,  /* Teleport bola tanpa animasi             */

    EVT_SHOW_TEXT,
    EVT_HIDE_TEXT,
    EVT_GOAL_FLASH,
    EVT_SCORE_UPDATE,
    EVT_WAIT,
    EVT_LOG_EVENT
} EventType;

typedef struct
{
    EventType type;
    float     triggerTime;

    /* EVT_SPAWN_PLAYER, EVT_MOVE_PLAYER, EVT_SUB_PLAYER */
    int       playerIdx;
    PlayerDef playerDef;    /* dipakai oleh SPAWN dan SUB */

    /* EVT_BALL_MOVE, EVT_BALL_TELEPORT */
    BallDef   ballDef;

    /* EVT_SHOW_TEXT */
    char      text[128];
    int       fontSize;
    Color     textColor;

    /* EVT_SCORE_UPDATE */
    int       score1, score2, minute;
} TimelineEvent;



/* ================================================================
    OVERLAY TEXT
   ================================================================ */

#define MAX_OVERLAY_TEXTS 4

typedef struct
{
    char  text[128];
    int   x, y;
    int   fontSize;
    Color color;
    bool  visible;
} OverlayText;

/* ================================================================
    HIGHLIGHT STATE
   ================================================================ */

typedef struct
{
    char  title[64];
    char  subtitle[128];

    Player players[MAX_PLAYERS];
    int    playerCount;

    Ball   ball;

    TimelineEvent events[MAX_EVENTS];
    int           eventCount;
    int           nextEvent;

    float elapsed;
    bool  running;
    bool  finished;

    /*
        Screen shake saat gol (menggantikan overlay warna).
        shakeTimer > 0 berarti layar sedang bergetar.
    */
    float shakeTimer;
    float shakeIntensity;
    int   shakeOffsetX;
    int   shakeOffsetY;

    OverlayText overlays[MAX_OVERLAY_TEXTS];

    char  team1Name[32];
    char  team2Name[32];
    int   score1, score2;
    int   minute;
    Color team1Color;
    Color team2Color;
    bool  wireframe;   
    float speedMult;

    struct {
        float time;
        char  text[80];
        Color color;
    } history[MAX_HISTORY];
    int  historyCount;
    bool showHistory;
} Highlight;

/* ================================================================
    INIT
   ================================================================ */

void Highlight_Init(
    Highlight *h,
    const char *title, const char *sub,
    const char *t1, const char *t2,
    Color c1, Color c2
);

/* ================================================================
    HL_ API (scene-facing)
    Semua fungsi ini dipanggil dari kode scene untuk membangun
    timeline. Nama pendek agar scene lebih mudah dibaca.

    t     = waktu trigger dalam detik dari awal highlight
    idx   = indeks pemain (0-21: Arsenal 0-10, MU 11-21)
   ================================================================ */

/*
    HL_Spawn
    Inisialisasi satu pemain di waktu t:
    - teleport ke posisi (x,y) dari PlayerDef
    - langsung mulai gerak ke (ex,ey) dengan dur dan moveType
    Dipakai di awal setiap blok gol untuk set posisi awal semua pemain.
*/
void HL_Spawn(Highlight *h, float t, int idx, PlayerDef def);

/*
    HL_Move
    Ubah tujuan pemain yang sudah ada di lapangan.
    x,y dari def DIABAIKAN — pemain bergerak dari posisi saat ini.
    Biasanya pakai P_CONT agar posisi berantai.
*/
void HL_Move(Highlight *h, float t, int idx, PlayerDef def);

/*
    HL_Sub
    Substitusi: ganti nama dan nomor pemain idx.
    Posisi tidak berubah. Warna jersey tetap.
    Gunakan P_SUB(prev_def, "NamaBaru", nomorBaru) untuk membuat def-nya.
*/
void HL_Sub(Highlight *h, float t, int idx, PlayerDef def);

/*
    HL_Ball
    Gerakkan bola sesuai BallDef (lurus atau Bezier).
    Posisi awal bola diambil dari BallDef.x/y.
*/
void HL_Ball(Highlight *h, float t, BallDef def);

/*
    HL_BallAt
    Teleport bola ke koordinat tertentu tanpa animasi.
    Dipakai untuk set posisi awal bola di awal setiap blok gol.
*/
void HL_BallAt(Highlight *h, float t, float x, float y);

/*
    HL_Text
    Tampilkan teks overlay.
*/
void HL_Text(Highlight *h, float t, const char *text, int size, Color col);

/*
    HL_Hide
    Sembunyikan semua teks overlay.
*/
void HL_Hide(Highlight *h, float t);

/*
    HL_Goal
    Shorthand untuk GoalFlash + ScoreUpdate dalam satu panggilan.
*/
void HL_Goal(Highlight *h, float t, int s1, int s2, int minute);

/*
    HL_Wait
    Tunggu sampai waktu t (tidak ada aksi, hanya menandai akhir scene).
*/
void HL_Wait(Highlight *h, float t);

void HL_Log(Highlight *h, float t, const char *text, Color col);

/* ================================================================
    ENGINE (dipanggil oleh main.c dan menu.c, bukan scene)
   ================================================================ */

void Highlight_Update(Highlight *h, float dt);
void Highlight_Draw(const Highlight *h);
void Highlight_DrawHUD(const Highlight *h);

void AddEvent(Highlight *h, TimelineEvent ev);


#endif
