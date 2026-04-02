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
Color c_seat_red = {175, 22, 28, 255};
Color c_seat_dark = {130, 14, 18, 255};
Color c_seat_wht  = {210, 206, 198, 255};
Color c_concrete  = { 75, 68, 62, 255};
Color c_board_bg  = { 10, 10, 60, 255};
Color c_board_txt = {160,160,255,255};
Color c_floodlit  = {255,245,185,255};
Color c_sky       = { 32, 38, 50, 255};

// Function atau API 
void Field_Draw(void);
void Field_DrawGoals(void);
void Field_DrawStadium(void);

#endif