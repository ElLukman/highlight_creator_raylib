#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include <stdbool.h>

typedef enum {
    MENU_NONE = -1,
    MENU_PLAY = 0,
    MENU_EXIT = 1
} MenuChoice;

typedef struct {
    int selected; 
    float animTime;
    MenuChoice chosen;
} Menu;

void Menu_Init(Menu *m);
void Menu_Update(Menu *m);
void Menu_Draw(const Menu *m);
bool Menu_HasChosen(const Menu *m);

#endif