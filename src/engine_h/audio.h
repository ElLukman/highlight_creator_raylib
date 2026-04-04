#ifndef AUDIO_H
#define AUDIO_H

/*
    File audio yang dibutuhkan (letakkan di folder assets/):
        assets/menu_music.ogg   -- musik loop saat di main menu
        assets/crowd_ambi.ogg   -- ambien penonton saat replay

    Jika file tidak ditemukan, program tetap berjalan tanpa suara.

    Contoh pemakaian di main.c:
        Audio_Init();
        Audio_StartMenu();

        // dalam loop:
        Audio_Update();

        // saat pindah ke scene:
        Audio_StartPlay();

        // saat keluar:
        Audio_Cleanup();
*/

void Audio_Init(void);
void Audio_Cleanup(void);

void Audio_StartMenu(void);
void Audio_StartPlay(void);
void Audio_Update(void);

void Audio_SetMenuVolume(float volume);
void Audio_SetCrowdVolume(float volume);

#endif
