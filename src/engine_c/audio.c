#include "src/engine_h/audio.h"
#include "raylib.h"

/*
    State internal audio (tidak diekspos keluar)
*/
static Music musicMenu  = {0};
static Music musicCrowd = {0};

static bool audioOk       = false;
static bool menuMusicOk   = false;
static bool crowdMusicOk  = false;

/*
    Audio_Init
    Inisialisasi perangkat audio dan muat semua file musik.
    Panggil sekali di awal program sebelum loop utama.
*/
void Audio_Init(void)
{
    InitAudioDevice();
    audioOk = IsAudioDeviceReady();

    if (!audioOk)
        return;

    if (FileExists("assets/menu_music.ogg"))
    {
        musicMenu = LoadMusicStream("assets/menu_music.ogg");
        SetMusicVolume(musicMenu, 0.5f);
        menuMusicOk = true;
    }

    if (FileExists("assets/crowd_ambi.ogg"))
    {
        musicCrowd = LoadMusicStream("assets/crowd_ambi.ogg");
        SetMusicVolume(musicCrowd, 0.4f);
        crowdMusicOk = true;
    }
}

/*
    Audio_Cleanup
    Bersihkan semua resource audio.
    Panggil sebelum CloseWindow().
*/
void Audio_Cleanup(void)
{
    if (!audioOk)
        return;

    if (menuMusicOk)
        UnloadMusicStream(musicMenu);

    if (crowdMusicOk)
        UnloadMusicStream(musicCrowd);

    CloseAudioDevice();
}

/*
    Audio_StartMenu
    Hentikan musik crowd, mulai musik menu.
*/
void Audio_StartMenu(void)
{
    if (!audioOk)
        return;

    if (crowdMusicOk && IsMusicStreamPlaying(musicCrowd))
        StopMusicStream(musicCrowd);

    if (menuMusicOk)
        PlayMusicStream(musicMenu);
}

/*
    Audio_StartPlay
    Hentikan musik menu, mulai ambien crowd.
*/
void Audio_StartPlay(void)
{
    if (!audioOk)
        return;

    if (menuMusicOk && IsMusicStreamPlaying(musicMenu))
        StopMusicStream(musicMenu);

    if (crowdMusicOk)
        PlayMusicStream(musicCrowd);
}

/*
    Audio_Update
    Panggil setiap frame di dalam loop utama agar stream music terus berjalan.
*/
void Audio_Update(void)
{
    if (!audioOk)
        return;

    if (menuMusicOk && IsMusicStreamPlaying(musicMenu))
        UpdateMusicStream(musicMenu);

    if (crowdMusicOk && IsMusicStreamPlaying(musicCrowd))
        UpdateMusicStream(musicCrowd);
}

/*
    Audio_SetMenuVolume
    Atur volume musik menu. Range: 0.0f (mati) hingga 1.0f (penuh).
*/
void Audio_SetMenuVolume(float volume)
{
    if (!audioOk || !menuMusicOk)
        return;
    SetMusicVolume(musicMenu, volume);
}

/*
    Audio_SetCrowdVolume
    Atur volume ambien penonton. Range: 0.0f hingga 1.0f.
*/
void Audio_SetCrowdVolume(float volume)
{
    if (!audioOk || !crowdMusicOk)
        return;
    SetMusicVolume(musicCrowd, volume);
}
