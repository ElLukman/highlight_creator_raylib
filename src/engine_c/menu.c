#include "src/engine_h/menu.h"
#include "src/engine_h/field.h"
#include "src/engine_h/screen_size.h"
#include "src/algorithm_h/bresenham.h"
#include "src/algorithm_h/midcircle.h"
#include <math.h>
#include <string.h>

// Color Pallete
#define C_SKY_TOP \
    (Color) { 80, 140, 205, 255 }
#define C_SKY_BOT \
    (Color) { 50, 90, 155, 255 }
#define C_CLOUD \
    (Color) { 220, 230, 245, 200 }
#define C_STAND_DARK \
    (Color) { 18, 10, 10, 255 }
#define C_STAND_MID \
    (Color) { 28, 16, 16, 255 }
#define C_CONCRETE \
    (Color) { 90, 82, 78, 255 }
#define C_SEAT_RED \
    (Color) { 185, 28, 32, 255 }
#define C_SEAT_DARK \
    (Color) { 140, 18, 22, 255 }
#define C_SEAT_WHITE \
    (Color) { 230, 228, 222, 255 }
#define C_GRASS_D \
    (Color) { 38, 100, 28, 255 }
#define C_GRASS_L \
    (Color) { 52, 128, 36, 255 }
#define C_GOLD \
    (Color) { 255, 210, 0, 255 }
#define C_WHITE \
    (Color) { 255, 255, 255, 255 }
#define C_BLACK \
    (Color) { 0, 0, 0, 255 }
#define C_FLOODLIGHT \
    (Color) { 255, 248, 200, 255 }
#define C_PANEL_BG \
    (Color) { 8, 4, 4, 210 }

// Helpers
static void HLine(int x1, int x2, int y, Color c) { BresenhamLine(x1, y, x2, y, c); }

static void FillRect(int x, int y, int w, int h, Color c)
{
    for (int row = y; row < y + h; row++)
        HLine(x, x + w - 1, row, c);
}

static void OutlineRect(int x, int y, int w, int h, int thick, Color col)
{
    Bres_ThickLine(x, y, x + w, y, thick, col);
    Bres_ThickLine(x + w, y, x + w, y + h, thick, col);
    Bres_ThickLine(x + w, y + h, x, y + h, thick, col);
    Bres_ThickLine(x, y + h, x, y, thick, col);
}

static unsigned char LerpByte(unsigned char a, unsigned char b, float t) { return (unsigned char)(a + (b - a) * t); }

static Color LerpColor(Color a, Color b, float t)
{
    return (Color){LerpByte(a.r, b.r, t), LerpByte(a.g, b.g, t), LerpByte(a.b, b.b, t), 255};
}

// Sky Drawing
static void DrawSky(void)
{
    int skyH = (int)(SCREEN_H * 0.25f);
    for (int y = 0; y < skyH; y++)
    {
        float t = (float)y / skyH;
        HLine(0, SCREEN_W - 1, y, LerpColor(C_SKY_TOP, C_SKY_BOT, t));
    }
    // Awan dinamis
    MidcircleFilled((int)(SCREEN_W * 0.15f), (int)(skyH * 0.3f), (int)(SCREEN_W * 0.02f), C_CLOUD);
    MidcircleFilled((int)(SCREEN_W * 0.19f), (int)(skyH * 0.23f), (int)(SCREEN_W * 0.015f), C_CLOUD);
    MidcircleFilled((int)(SCREEN_W * 0.21f), (int)(skyH * 0.28f), (int)(SCREEN_W * 0.018f), C_CLOUD);

    MidcircleFilled((int)(SCREEN_W * 0.70f), (int)(skyH * 0.26f), (int)(SCREEN_W * 0.017f), C_CLOUD);
    MidcircleFilled((int)(SCREEN_W * 0.75f), (int)(skyH * 0.25f), (int)(SCREEN_W * 0.015f), C_CLOUD);
}

// Tribun
static void DrawStand(void)
{
    int skyH = (int)(SCREEN_H * 0.25f);
    int standH = (int)(SCREEN_H * 0.40f);
    int baseY = skyH;

    // Atap Tribun
    FillRect(0, baseY, SCREEN_W, (int)(standH * 0.1f), C_STAND_DARK);
    HLine(0, SCREEN_W - 1, baseY + (int)(standH * 0.15f), C_CONCRETE);

    // Banner Sir Alex
    int bannerW = (int)(SCREEN_W * 0.5f), bannerH = (int)(standH * 0.08f);
    FillRect(SCREEN_W / 2 - bannerW / 2, baseY + (int)(standH * 0.12f), bannerW, bannerH, (Color){200, 200, 200, 255});
    int tw = MeasureText("SIR ALEX FERGUSON STAND", 14);
    DrawText("SIR ALEX FERGUSON STAND", SCREEN_W / 2 - tw / 2, baseY + (int)(standH * 0.12f) + bannerH / 2 - 7, 14, (Color){40, 40, 40, 255});

    // Tiang Lampu
    int ltx[] = {(int)(SCREEN_W * 0.05f), (int)(SCREEN_W * 0.25f), (int)(SCREEN_W * 0.75f), (int)(SCREEN_W * 0.95f)};
    for (int i = 0; i < 4; i++)
    {
        FillRect(ltx[i] - 4, baseY - (int)(skyH * 0.3f), 8, (int)(skyH * 0.3f + standH * 0.1f), C_CONCRETE);
        FillRect(ltx[i] - 14, baseY - (int)(skyH * 0.3f) - 8, 28, 14, (Color){60, 55, 50, 255});
        MidcircleFilled(ltx[i], baseY - (int)(skyH * 0.3f) - 2, 10, C_FLOODLIGHT);
        MidcircleThick(ltx[i], baseY - (int)(skyH * 0.3f) - 2, 14, 2, (Color){255, 248, 200, 120});
    }

    // Kursi Bagian Atas
    int seatUpperY = baseY + (int)(standH * 0.2f);
    int rowHeightUpper = (int)(standH * 0.3f) / 14;
    for (int row = 0; row < 14; row++)
    {
        int y = seatUpperY + row * rowHeightUpper;
        Color c = (row % 2 == 0) ? C_SEAT_RED : C_SEAT_DARK;
        int margin = (14 - row) * (int)(SCREEN_W * 0.005f);
        FillRect(margin, y, SCREEN_W - margin * 2, rowHeightUpper + 1, c);
    }

    // Teks MANCHESTER di Kursi
    int textBandY = baseY + (int)(standH * 0.5f);
    FillRect((int)(SCREEN_W * 0.08f), textBandY, (int)(SCREEN_W * 0.84f), (int)(standH * 0.1f), C_SEAT_WHITE);
    int mw = MeasureText("MANCHESTER UNITED", 28);
    DrawText("MANCHESTER UNITED", SCREEN_W / 2 - mw / 2, textBandY + (int)(standH * 0.02f), 28, C_SEAT_RED);

    // Kursi Bagian Bawah
    int seatLowerY = baseY + (int)(standH * 0.6f);
    int rowHeightLower = (int)(standH * 0.25f) / 10;
    for (int row = 0; row < 10; row++)
    {
        int y = seatLowerY + row * rowHeightLower;
        Color c = (row % 2 == 0) ? C_SEAT_RED : C_SEAT_DARK;
        int margin = (10 - row) * (int)(SCREEN_W * 0.003f);
        FillRect(margin, y, SCREEN_W - margin * 2, rowHeightLower + 1, c);
    }

    // Papan Iklan Bawah
    int adY = baseY + (int)(standH * 0.85f);
    FillRect(0, adY, SCREEN_W, (int)(standH * 0.1f), (Color){20, 20, 80, 255});
    for (int i = 0; i < SCREEN_W / 220; i++)
        DrawText("MANUTD.COM/SEE", 30 + i * 220, adY + 4, 14, (Color){180, 180, 255, 255});

    // Pembatas Bawah
    FillRect(0, baseY + (int)(standH * 0.95f), SCREEN_W, (int)(standH * 0.05f), (Color){60, 55, 50, 255});
}

// Lapangan
static void DrawPitch(void)
{
    int pitch_y = (int)(SCREEN_H * 0.65f), pitch_h = SCREEN_H - pitch_y;
    int stripe_w = SCREEN_W / 10;

    for (int s = 0; s < 10; s++)
    {
        Color c = (s % 2 == 0) ? C_GRASS_D : C_GRASS_L;
        FillRect(s * stripe_w, pitch_y, stripe_w, pitch_h, c);
    }
    FillRect(10 * stripe_w, pitch_y, SCREEN_W - 10 * stripe_w, pitch_h, C_GRASS_D);
    HLine(0, SCREEN_W - 1, pitch_y, C_WHITE);

    int midX = SCREEN_W / 2, arcWidth = (int)(SCREEN_W * 0.4f);
    for (int x = midX - arcWidth / 2; x <= midX + arcWidth / 2; x++)
    {
        float t = (float)(x - (midX - arcWidth / 2)) / arcWidth;
        int y = pitch_y + 15 + (int)((SCREEN_H * 0.06f) * sinf(t * 3.14159f));
        DrawPixel(x, y, C_WHITE);
        DrawPixel(x, y + 1, C_WHITE);
    }
}

// Panel Interaktif
static void DrawMenuPanel(const Menu *m)
{
    float pulse = 0.5f + 0.5f * sinf(m->animTime * 2.0f);
    int midY = SCREEN_H / 2;

    int panelW = (int)(SCREEN_W * 0.45f), panelH = (int)(SCREEN_H * 0.45f);
    int px = (int)(SCREEN_W * 0.02f);           /* justify left */
    int py = midY - panelH / 2;
    int panelMidX = px + panelW / 2;

    FillRect(px, py, panelW, panelH, C_PANEL_BG);
    OutlineRect(px, py, panelW, panelH, 2, C_GOLD);

    // Logo di tengah panel
    int cx = panelMidX, cy = py + (int)(panelH * 0.15f);
    MidcircleFilled(cx, cy, 32, (Color){185, 28, 32, 255});
    Midcircle(cx, cy, 32, C_GOLD);
    MidcircleFilled(cx, cy, 18, (Color){140, 18, 22, 255});
    Bres_ThickLine(cx - 28, cy, cx + 28, cy, 2, C_GOLD);
    Bres_ThickLine(cx, cy - 28, cx, cy + 28, 2, C_GOLD);

    const char *title = "FOOTBALL HIGHLIGHTS";
    int tw = MeasureText(title, 26);
    DrawText(title, panelMidX - tw / 2 + 1, cy + 41, 26, (Color){0, 0, 0, 160});
    DrawText(title, panelMidX - tw / 2, cy + 40, 26, C_GOLD);

    const char *sub = "Arsenal  vs  Manchester United";
    int sw = MeasureText(sub, 15);
    DrawText(sub, panelMidX - sw / 2, cy + 72, 15, (Color){200, 200, 200, 255});

    // Tombol Interaktif
    int btn_w = (int)(panelW * 0.7f), btn_h = (int)(panelH * 0.15f);
    int btn_x = panelMidX - btn_w / 2;
    int btn_ys[2] = {cy + (int)(panelH * 0.35f), cy + (int)(panelH * 0.55f)};
    const char *labels[2] = {"TONTON HIGHLIGHT", "KELUAR"};
    Color btn_colors[2] = {(Color){185, 28, 32, 255}, (Color){50, 50, 50, 255}};

    for (int i = 0; i < 2; i++)
    {
        bool hov = (m->selected == i);
        Color bg = btn_colors[i];
        if (hov)
        {
            bg.r = (unsigned char)(bg.r + (255 - bg.r) * 0.3f * pulse);
            bg.g = (unsigned char)(bg.g + (255 - bg.g) * 0.2f * pulse);
            bg.b = (unsigned char)(bg.b + (255 - bg.b) * 0.2f * pulse);
        }
        FillRect(btn_x, btn_ys[i], btn_w, btn_h, bg);

        Color border = hov ? C_GOLD : (Color){120, 120, 120, 255};
        OutlineRect(btn_x, btn_ys[i], btn_w, btn_h, hov ? 2 : 1, border);

        Color tcol = hov ? C_GOLD : C_WHITE;
        int fs = 18;
        DrawText(labels[i], panelMidX - MeasureText(labels[i], fs) / 2, btn_ys[i] + btn_h / 2 - fs / 2, fs, tcol);
    }

    const char *hint = "[UP/DOWN] Pilih   [ENTER] Konfirmasi   [ESC] Keluar";
    DrawText(hint, panelMidX - MeasureText(hint, 12) / 2, py + panelH - 24, 12, (Color){120, 120, 120, 255});
    DrawText("v2.0  |  Raylib + Bresenham + Midcircle", 10, SCREEN_H - 20, 11, (Color){60, 60, 60, 255});
}

/*
    API
*/
static RenderTexture2D menuCache;
static bool menuCached = false;

void Menu_Init(Menu *m)
{
    m->selected = 0;
    m->animTime = 0.0f;
    m->chosen = MENU_NONE;
}

void Menu_Update(Menu *m)
{
    m->animTime += GetFrameTime();

    /* Kontrol Keyboard */
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        m->selected = (m->selected + 1) % 2;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        m->selected = (m->selected + 1) % 2;
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER))
        m->chosen = (MenuChoice)m->selected;
    if (IsKeyPressed(KEY_ESCAPE))
        m->chosen = MENU_EXIT;
    if (IsKeyPressed(KEY_ONE))
        m->chosen = MENU_PLAY;
    if (IsKeyPressed(KEY_TWO))
        m->chosen = MENU_EXIT;

    // Kontrol Mouse
    Vector2 mouse = GetMousePosition();
    int mx = (int)mouse.x, my = (int)mouse.y;

    int panelW = (int)(SCREEN_W * 0.45f), panelH = (int)(SCREEN_H * 0.45f);
    int px = (int)(SCREEN_W * 0.02f), py = SCREEN_H / 2 - panelH / 2;
    int panelMidX = px + panelW / 2;
    int btn_w = (int)(panelW * 0.7f), btn_h = (int)(panelH * 0.15f);
    int btn_x = panelMidX - btn_w / 2;
    int cy = py + (int)(panelH * 0.15f);
    int btn_ys[2] = {cy + (int)(panelH * 0.35f), cy + (int)(panelH * 0.55f)};

    for (int i = 0; i < 2; i++)
    {
        if (mx >= btn_x && mx <= btn_x + btn_w && my >= btn_ys[i] && my <= btn_ys[i] + btn_h)
        {
            m->selected = i;
            if (IsMouseButtonPressed(0))
                m->chosen = (MenuChoice)i;
        }
    }
}

void Menu_Draw(const Menu *m)
{
    // Texture Caching untuk Menu Background
    if (!menuCached)
    {
        menuCache = LoadRenderTexture(SCREEN_W, SCREEN_H);
        BeginTextureMode(menuCache);
        ClearBackground((Color){8, 4, 4, 255});
        DrawSky();
        DrawStand();
        DrawPitch();
        EndTextureMode();
        menuCached = true;
    }

    // Gambar background statis yang sudah di-cache
    DrawTextureRec(
        menuCache.texture,
        (Rectangle){0, 0, (float)menuCache.texture.width,
                    (float)-menuCache.texture.height},
        (Vector2){0, 0}, WHITE);

    // Draw Panel & Tombol Interaktif
    DrawMenuPanel(m);
}

bool Menu_HasChosen(const Menu *m)
{
    return m->chosen != MENU_NONE;
}