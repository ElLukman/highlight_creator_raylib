#include "raylib.h"
#include "src/engine_h/field.h"
#include "src/engine_h/screen_size.h"
#include "src/engine_h/menu.h"
#include "src/engine_h/highlight.h"
#include "src/engine_h/audio.h"
#include "src/algorithm_h/bresenham.h"
#include "src/algorithm_h/midcircle.h"
#include "src/scene/scene_arsenal_vs_mu.h"
#include <stdbool.h>
#include <stdio.h>

/*
    App State
*/
typedef enum
{
    APP_LOADING,  /* layar loading pertama kali program dibuka */
    APP_MENU,
    APP_PLAY
} AppState;

/*
    Metrics overlay (toggle F3)
*/
static bool showMetrics = false;

static void DrawMetrics(const Highlight *h)
{
    if (!showMetrics)
        return;

    int fps     = GetFPS();
    float ft    = GetFrameTime() * 1000.0f;  /* ms */

    char buf[128];
    int  y = 50, fs = 16, pad = 4;
    int  bw = 220, bh = 110;
    int  bx = SCREEN_W - bw - 10;

    // Background panel
    for (int row = y; row < y + bh; row++)
        BresenhamLine(bx, row, bx + bw, row, (Color){0, 0, 0, 200});
    Bres_ThickLine(bx, y, bx + bw, y, 1, (Color){255, 210, 0, 255});

    // FPS
    Color fpsCol = (fps >= 55) ? GREEN : (fps >= 30) ? YELLOW : RED;
    snprintf(buf, sizeof(buf), "FPS:        %d", fps);
    DrawText(buf, bx + pad, y + pad,      fs, fpsCol);

    // Frame time
    snprintf(buf, sizeof(buf), "Frame:    %.2f ms", ft);
    DrawText(buf, bx + pad, y + pad + 20, fs, WHITE);

    // Event progress
    if (h)
    {
        snprintf(buf, sizeof(buf), "Event:    %d / %d",
            h->nextEvent, h->eventCount);
        DrawText(buf, bx + pad, y + pad + 40, fs, WHITE);

        snprintf(buf, sizeof(buf), "Players:  %d", h->playerCount);
        DrawText(buf, bx + pad, y + pad + 60, fs, WHITE);

        snprintf(buf, sizeof(buf), "Shake:    %.2f", h->shakeTimer);
        DrawText(buf, bx + pad, y + pad + 80, fs, WHITE);
    }

    DrawText("[F3] tutup", bx + pad, y + bh - 16, 12,
        (Color){120, 120, 120, 255});
}

/*
    Loading Screen
    Ditampilkan sekali di awal untuk warm-up render cache.
    Selama loading, Field_DrawStadium() dan Field_Draw() dipanggil
    sehingga RenderTexture2D sudah siap sebelum pemain mulai main.
*/
static void DrawLoadingScreen(int step, int total)
{
    ClearBackground((Color){8, 4, 4, 255});

    int  cx = SCREEN_W / 2, cy = SCREEN_H / 2;
    int  bw = 500, bh = 24;
    int  bx = cx - bw / 2, by = cy + 30;

    // Judul
    const char *title = "Football Highlight Creator";
    DrawText(title, cx - MeasureText(title, 30) / 2, cy - 60, 30, YELLOW);

    // Sub-judul
    const char *sub = "Arsenal  vs  Manchester United";
    DrawText(sub, cx - MeasureText(sub, 18) / 2, cy - 20, 18, WHITE);

    // Status
    const char *statuses[] = {
        "Memuat tribun stadion...",
        "Merender lapangan...",
        "Siap!"
    };
    const char *status = (step < total) ? statuses[step] : statuses[2];
    DrawText(status, cx - MeasureText(status, 16) / 2, by - 24, 16,
        (Color){180, 180, 180, 255});

    // Progress bar background
    for (int row = by; row < by + bh; row++)
        BresenhamLine(bx, row, bx + bw, row, (Color){40, 40, 40, 255});
    Bres_ThickLine(bx, by, bx + bw, by, 1, (Color){80, 80, 80, 255});
    Bres_ThickLine(bx, by + bh, bx + bw, by + bh, 1, (Color){80, 80, 80, 255});

    // Progress bar isi
    int fillW = (bw * step) / total;
    if (fillW > 0)
    {
        for (int row = by + 2; row < by + bh - 2; row++)
            BresenhamLine(bx + 2, row, bx + 2 + fillW, row,
                (Color){220, 30, 30, 255});
    }

    // Persen
    char pct[16];
    snprintf(pct, sizeof(pct), "%d%%", (step * 100) / total);
    DrawText(pct, cx - MeasureText(pct, 16) / 2, by + bh + 8, 16,
        (Color){200, 200, 200, 255});
}

/*
    Preload
    Paksa render cache dibangun sebelum game loop.
    Setiap langkah di-render ke layar sambil progress bar bergerak.
*/
static void Preload(void)
{
    int totalSteps = 2;

    // Step 1: stadium cache
    BeginDrawing();
    DrawLoadingScreen(0, totalSteps);
    EndDrawing();

    // Paksa Field_DrawStadium() berjalan (membangun stadiumCache)
    BeginDrawing();
    Field_DrawStadium();
    EndDrawing();

    // Step 2: field cache
    BeginDrawing();
    DrawLoadingScreen(1, totalSteps);
    EndDrawing();

    // Paksa Field_Draw() berjalan (membangun fieldCache)
    BeginDrawing();
    Field_Draw();
    EndDrawing();

    // Selesai
    BeginDrawing();
    DrawLoadingScreen(totalSteps, totalSteps);
    EndDrawing();

    // Jeda singkat agar loading bar sempat terlihat
    WaitTime(0.4);
}

/*
    UI Helpers
*/
static void FillBar(int x, int y, int w, int h, Color col)
{
    for (int row = y; row < y + h; row++)
        BresenhamLine(x, row, x + w - 1, row, col);
}

static void DrawControls(void)
{
    FillBar(0, SCREEN_H - 24, SCREEN_W, 24, (Color){0, 0, 0, 200});
    const char *hint = "[SPACE] Pause   [R] Ulang   [F3] Metrik   [Z] Bagi Lapangan jadi 18 Zona    [ESC] Menu";
    DrawText(
        hint,
        SCREEN_W / 2 - MeasureText(hint, 12) / 2,
        SCREEN_H - 18, 12,
        (Color){130, 130, 130, 255});
}

static void DrawPauseOverlay(void)
{
    for (int row = 0; row < SCREEN_H; row += 2)
        BresenhamLine(0, row, SCREEN_W - 1, row, (Color){0, 0, 0, 100});

    FillBar(SCREEN_W / 2 - 180, SCREEN_H / 2 - 44, 360, 88,
        (Color){0, 0, 0, 230});
    Bres_ThickLine(
        SCREEN_W / 2 - 180, SCREEN_H / 2 - 44,
        SCREEN_W / 2 + 180, SCREEN_H / 2 - 44, 2, YELLOW);
    Bres_ThickLine(
        SCREEN_W / 2 - 180, SCREEN_H / 2 + 44,
        SCREEN_W / 2 + 180, SCREEN_H / 2 + 44, 2, YELLOW);

    int pw = MeasureText("[ PAUSED ]", 32);
    DrawText("[ PAUSED ]",
        SCREEN_W / 2 - pw / 2, SCREEN_H / 2 - 28, 32, YELLOW);

    const char *hint = "[SPACE] Lanjutkan    [R] Ulang";
    DrawText(hint,
        SCREEN_W / 2 - MeasureText(hint, 13) / 2,
        SCREEN_H / 2 + 14, 13, WHITE);
}

static void DrawFinishedOverlay(void)
{
    FillBar(SCREEN_W / 2 - 240, SCREEN_H / 2 - 44, 480, 88,
        (Color){0, 0, 0, 220});
    Bres_ThickLine(
        SCREEN_W / 2 - 240, SCREEN_H / 2 - 44,
        SCREEN_W / 2 + 240, SCREEN_H / 2 - 44, 2, YELLOW);
    Bres_ThickLine(
        SCREEN_W / 2 - 240, SCREEN_H / 2 + 44,
        SCREEN_W / 2 + 240, SCREEN_H / 2 + 44, 2, YELLOW);

    int bw = MeasureText("Highlight Selesai!", 26);
    DrawText("Highlight Selesai!",
        SCREEN_W / 2 - bw / 2, SCREEN_H / 2 - 28, 26, YELLOW);

    const char *hint = "[R] Ulang    [ESC] Menu";
    DrawText(hint,
        SCREEN_W / 2 - MeasureText(hint, 14) / 2,
        SCREEN_H / 2 + 12, 14, WHITE);
}

/*
    Main
*/
int main(void)
{
    InitWindow(SCREEN_W, SCREEN_H,
        "Football Highlight Creator - Arsenal vs Man Utd");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    Audio_Init();

    // Preload: bangun semua render cache sebelum masuk menu
    Preload();

    Audio_StartMenu();

    AppState  state  = APP_LOADING;
    state = APP_MENU;  /* langsung ke menu setelah preload selesai */

    bool      paused = false;
    Menu      menu;
    Highlight hl;

    Menu_Init(&menu);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        if (dt > 0.05f)
            dt = 0.05f;

        Audio_Update();

        // Input
        if (state == APP_MENU)
        {
            Menu_Update(&menu);

            if (Menu_HasChosen(&menu))
            {
                if (menu.chosen == MENU_PLAY)
                {
                    hl = Scene_ARS_MUN_Build();
                    paused = false;
                    state = APP_PLAY;
                    Audio_StartPlay();
                }
                else
                {
                    break;
                }
            }
            if (IsKeyPressed(KEY_ESCAPE))
                break;
        }
        else if (state == APP_PLAY)
        {
            if (IsKeyPressed(KEY_ESCAPE))
            {
                state = APP_MENU;
                Menu_Init(&menu);
                Audio_StartMenu();
            }
            if (IsKeyPressed(KEY_SPACE))
                paused = !paused;
            if (IsKeyPressed(KEY_R))
            {
                hl = Scene_ARS_MUN_Build();
                paused = false;
            }
            if (IsKeyPressed(KEY_Z))
                g_fieldMode = (g_fieldMode == 0) ? 1 : 0;   

                // Toggle metrics overlay
            if (IsKeyPressed(KEY_F3))
                showMetrics = !showMetrics;
        }

        // Update
        if (state == APP_PLAY && !paused)
            Highlight_Update(&hl, dt);

        // Draw
        BeginDrawing();

        if (state == APP_MENU)
        {
            Menu_Draw(&menu);
        }
        else if (state == APP_PLAY)
        {
            // Layer 1: tribun stadion (dari cache)
            Field_DrawStadium();

            // Layer 2: lapangan + garis + gawang (dari cache)
            Field_Draw();

            // Layer 3: pemain + bola + teks (dirender ulang tiap frame)
            Highlight_Draw(&hl);

            // Layer 4: HUD skor
            Highlight_DrawHUD(&hl);

            // Layer 5: kontrol bar bawah
            DrawControls();

            // Layer 6: overlay (pause / selesai / metrics)
            if (paused)
                DrawPauseOverlay();
            if (hl.finished)
                DrawFinishedOverlay();
            DrawMetrics(state == APP_PLAY ? &hl : NULL);
        }

        EndDrawing();
    }

    Audio_Cleanup();
    CloseWindow();
    return 0;
}
