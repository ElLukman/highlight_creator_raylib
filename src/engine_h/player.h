#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <stdbool.h>

#define MAX_PLAYERS   22
#define PLAYER_RADIUS 14

extern int g_wireframe;

/*
    MoveType
    Tipe animasi gerakan, berlaku untuk pemain maupun bola.

    LINEAR      -- kecepatan konstan, tidak ada easing
    EASE_OUT    -- mulai cepat, melambat di akhir (tendangan, sprint)
    EASE_IN     -- mulai lambat, makin cepat (akselerasi pemain)
    EASE_IN_OUT -- lambat-cepat-lambat, terasa halus dan alami
    BEZIER      -- kurva lengkung (khusus bola: corner, free kick, curl)
*/
typedef enum
{
    LINEAR      = 0,
    EASE_OUT    = 1,
    EASE_IN     = 2,
    EASE_IN_OUT = 3,
    BEZIER      = 4,
} MoveType;

/*
    PlayerDef
    Struct deklarasi scene-time. Dipakai hanya di kode scene untuk
    mendeskripsikan posisi, tujuan, dan gerak satu pemain dalam satu aksi.
    Tidak dipakai oleh engine runtime.

    Cara pakai (lihat macro P dan P_CONT di bawah):

        PlayerDef saliba = P("Saliba", 2, ARS, 422, 650,  800, 540, 1.5f, EASE_OUT);
        PlayerDef saliba = P_CONT(saliba, 1200, 400, 0.8f, EASE_IN);
*/
typedef struct
{
    char  name[24];
    int   num;
    Color color;
    Color numColor;
    float x,  y;       /* posisi spawn / posisi saat ini   */
    float ex, ey;      /* posisi tujuan                    */
    float dur;         /* durasi gerakan (detik)           */
    MoveType moveType;
} PlayerDef;

/*
    BallDef
    Struct deklarasi scene-time untuk bola.
    Macro B dan B_BEZ memudahkan penulisan.

        BallDef bola = B(960, 540,  1809, 540, 0.4f, EASE_OUT);
        BallDef bola = B_BEZ(1800, 80,  1540, 360,  1820, 200, 1.1f);
        BallDef bola = B_CONT(bola_prev, 1809, 540, 0.4f, EASE_OUT);
*/
typedef struct
{
    float x,  y;       /* posisi awal bola                 */
    float ex, ey;      /* posisi tujuan                    */
    float cx, cy;      /* control point (hanya untuk BEZIER)*/
    float dur;
    MoveType moveType;
} BallDef;

/* ================================================================
    FUNGSI PEMBANTU SCENE (static inline)
    Menggantikan macro agar name[24] bisa di-copy dengan benar.
   ================================================================ */

/*
    P  -- deklarasi pemain baru dari posisi awal ke posisi tujuan
    Contoh:
        PlayerDef raya = P("Raya", 1, ARS, 204, 540,  204, 540, 0.0f, LINEAR);
*/
static inline PlayerDef P(
    const char *nm, int no, Color col,
    float sx, float sy, float tex, float tey,
    float d, MoveType mt)
{
    PlayerDef r;
    int i = 0;
    while (nm[i] && i < 23) { r.name[i] = nm[i]; i++; }
    r.name[i] = '\0';
    r.num = no; r.color = col;
    r.numColor = (Color){255,255,255,255};
    r.x = sx; r.y = sy; r.ex = tex; r.ey = tey;
    r.dur = d; r.moveType = mt;
    return r;
}

/*
    P_NUM  -- seperti P tapi dengan warna nomor custom (untuk kiper)
*/
static inline PlayerDef P_NUM(
    const char *nm, int no, Color col, Color numcol,
    float sx, float sy, float tex, float tey,
    float d, MoveType mt)
{
    PlayerDef r = P(nm, no, col, sx, sy, tex, tey, d, mt);
    r.numColor = numcol;
    return r;
}

/*
    P_CONT -- lanjutkan dari posisi terakhir pemain (ex,ey jadi x,y baru)
    Contoh:
        PlayerDef s2 = P_CONT(saliba, 1200, 400, 0.8f, EASE_IN);
*/
static inline PlayerDef P_CONT(
    PlayerDef prev,
    float tex, float tey,
    float d, MoveType mt)
{
    PlayerDef r = prev;
    r.x = prev.ex; r.y = prev.ey;
    r.ex = tex; r.ey = tey;
    r.dur = d; r.moveType = mt;
    return r;
}

/*
    P_SUB -- substitusi: ganti nama dan nomor, posisi tetap dari prev
    Warna jersey tetap (tim yang sama).
    Contoh:
        PlayerDef cunha = P_SUB(mbeumo, "Cunha", 10);
*/
static inline PlayerDef P_SUB(PlayerDef prev, const char *nm, int no)
{
    PlayerDef r = prev;
    int i = 0;
    while (nm[i] && i < 23) { r.name[i] = nm[i]; i++; }
    r.name[i] = '\0';
    r.num = no;
    r.x = prev.ex; r.y = prev.ey;
    r.ex = prev.ex; r.ey = prev.ey;
    r.dur = 0.0f; r.moveType = LINEAR;
    return r;
}

/*
    B  -- deklarasi bola gerak lurus / easing
    Contoh:
        BallDef bola = B(960, 540,  1809, 540, 0.4f, EASE_OUT);
*/
static inline BallDef B(
    float sx, float sy, float tex, float tey,
    float d, MoveType mt)
{
    BallDef r;
    r.x = sx; r.y = sy; r.ex = tex; r.ey = tey;
    r.cx = 0.0f; r.cy = 0.0f; r.dur = d; r.moveType = mt;
    return r;
}

/*
    B_BEZ -- deklarasi bola kurva Bezier (corner, free kick, curl)
    cx, cy = control point yang menentukan bentuk lengkungan
    Contoh:
        BallDef corn = B_BEZ(1800, 80,  1540, 360,  1820, 100, 1.1f);
*/
static inline BallDef B_BEZ(
    float sx, float sy, float tex, float tey,
    float ccx, float ccy, float d)
{
    BallDef r;
    r.x = sx; r.y = sy; r.ex = tex; r.ey = tey;
    r.cx = ccx; r.cy = ccy; r.dur = d; r.moveType = BEZIER;
    return r;
}

/*
    B_CONT -- bola lanjut dari posisi terakhir BallDef sebelumnya
    Contoh:
        BallDef b2 = B_CONT(bola, 1809, 540, 0.4f, EASE_OUT);
*/
static inline BallDef B_CONT(
    BallDef prev,
    float tex, float tey,
    float d, MoveType mt)
{
    BallDef r;
    r.x = prev.ex; r.y = prev.ey;
    r.ex = tex; r.ey = tey;
    r.cx = 0.0f; r.cy = 0.0f; r.dur = d; r.moveType = mt;
    return r;
}

/* ================================================================
    RUNTIME STRUCTS (dipakai engine, bukan scene)
   ================================================================ */

/*
    Player (runtime)
    Menyimpan state aktual pemain selama animasi berjalan.
*/
typedef struct
{
    float x,  y;        /* posisi saat ini (pixel)    */
    float tx, ty;       /* posisi target               */
    float speed;        /* px/frame                    */
    MoveType moveType;  /* tipe easing                 */
    float moveElapsed;  /* waktu berjalan sejak SetTarget */
    float moveDur;      /* durasi total gerakan        */
    float startX, startY; /* posisi saat SetTarget dipanggil */
    int   num;
    char  name[24];
    Color color;
    Color numColor;
    bool  active;
} Player;

/*
    Ball (runtime)
*/
typedef struct
{
    float x,  y;
    float sx, sy;
    float ex, ey;
    float cx, cy;
    float t;
    float duration;
    float elapsed;
    MoveType moveType;
    bool  moving;
    int   radius;
    bool  inGoal;
} Ball;

/* ================================================================
    API RUNTIME (dipanggil oleh engine, bukan scene)
   ================================================================ */

void Player_InitFromDef(Player *p, const PlayerDef *def);
void Player_SetTarget(Player *p, float tx, float ty,
                      float dur, MoveType mt);
void Player_Update(Player *p, float dt);
void Player_Draw(const Player *p);

void Ball_InitFromDef(Ball *b, const BallDef *def);
void Ball_Update(Ball *b, float dt);
void Ball_Draw(const Ball *b);

#endif
