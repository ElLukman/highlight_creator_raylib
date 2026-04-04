/*
speed.h — Konstanta kecepatan bola & pemain yang intuitif

CARA PAKAI:
    Ganti angka durasi hardcode dengan konstanta ini + fungsi BallDur/DribbleDur.
    
    PILIHAN KECEPATAN:

    BOLA (tendangan / umpan):
    - KICK_POWER   1200 px/s  - tembakan bertenaga penuh
    - KICK_HARD     900 px/s  - tendangan keras standar
    - FREEKICK      800 px/s  - tendangan bebas
    - PASS_LONG     700 px/s  - umpan panjang diagonal
    - KICK_NORMAL   600 px/s  - tendangan/umpan biasa
    - CORNER        550 px/s  - tendangan sudut
    - PASS_SHORT    500 px/s  - umpan pendek satu dua
    - KICK_SOFT     400 px/s  - tendangan pelan/lemah
    - HEADER        350 px/s  - sundulan

    DRIBBLE (pemain + bola bersama):
    - SPRINT_DRIBBLE 220 px/s - dribble lari cepat
    - DRIBBLE        150 px/s - dribble normal
    - DRIBBLE_SLOW   100 px/s - dribble lambat, skillful
*/

#ifndef SPEED_H
#define SPEED_H

#include <math.h>

// Kecepatan bola (pixel per detik) 
#define KICK_POWER     1200.0f
#define KICK_HARD       900.0f
#define FREEKICK        800.0f
#define PASS_LONG       700.0f
#define KICK_NORMAL     600.0f
#define CORNER          550.0f
#define PASS_SHORT      500.0f
#define KICK_SOFT       400.0f
#define HEADER          350.0f

// Kecepatan dribble (pixel per detik) 
#define SPRINT_DRIBBLE  220.0f
#define DRIBBLE         150.0f
#define DRIBBLE_SLOW    100.0f

/*
    BallDur() — hitung durasi (detik) otomatis dari jarak & kecepatan
    Contoh:
    float dur = BallDur(FX(0.74f), FY(0.22f),
                        GOAL_R_X,  GOAL_R_Y,
                        KICK_HARD);
    Evt_BallBezier(t, GOAL_R_X, GOAL_R_Y, ctrl_x, ctrl_y, dur);
*/
static inline float BallDur(float x1, float y1,
                            float x2, float y2,
                            float speed_px_per_sec) 
{
    float dx = x2 - x1, dy = y2 - y1;
    float dist = sqrtf(dx*dx + dy*dy);
    if (dist < 1.0f) return 0.05f;
    float dur = dist / speed_px_per_sec;
    // Clamp: minimum 0.08s (tidak terlalu instan), maksimum 3.0s 
    if (dur < 0.08f) dur = 0.08f;
    if (dur > 3.0f)  dur = 3.0f;
    return dur;
}

/*
    DribbleDur() — sama seperti BallDur tapi untuk Evt_Dribble
    
    Contoh:
    Evt_Dribble(t, 15, FX(0.40f), FY(0.70f),
                DribbleDur(FX(0.58f), FY(0.74f), FX(0.40f), FY(0.70f), SPRINT_DRIBBLE)
                );
 */
static inline float DribbleDur(
float x1, float y1, float x2, float y2, float speed_px_per_sec) 
{
    return BallDur(x1, y1, x2, y2, speed_px_per_sec);
}

#endif 
