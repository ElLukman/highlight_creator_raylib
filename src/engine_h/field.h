#ifndef FIELD_HEADER_H
#define FIELD_HEADER_H

#include "raylib.h"

// Ukuran lapangan bola
#define FIELD_X 120 
#define FIELD_Y 80 
#define FIELD_W 1680
#define FIELD_H 920

#define STRIPE_COUNT 14
#define GOAL_W 18
#define GOAL_H 140

// Stadium Color
#define c_seat_red  (Color){ 175, 22, 28, 255 }
#define c_seat_dark (Color){ 130, 14, 18, 255 }
#define c_seat_wht  (Color){ 210, 206, 198, 255 }
#define c_concrete  (Color){ 75, 68, 62, 255 }
#define c_board_bg  (Color){ 10, 10, 60, 255 }
#define c_board_txt (Color){ 160, 160, 255, 255 }
#define c_floodlit  (Color){ 255, 245, 185, 255 }
#define c_sky       (Color){ 32, 38, 50, 255 }


// Function atau API 
void Field_Draw(void);
void Field_DrawZones(void);

// Mode Lapangan
extern int g_fieldMode;

void Field_DrawGoals(void);
void Field_DrawStadium(void);

#endif