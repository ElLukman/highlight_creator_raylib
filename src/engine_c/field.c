#include "src/engine_h/field.h"
#include "src/engine_h/screen_size.h"
#include "src/algorithm_h/bresenham.h"
#include "src/algorithm_h/midcircle.h"
#include <math.h>

int g_fieldMode = 0;

void Field_DrawZones(void)
{
    int cols = 6, rows = 3;
    int cw   = FIELD_W / cols;
    int rh   = FIELD_H / rows;

    // garis kolom 
    for (int c = 1; c < cols; c++)
    {
        int x = FIELD_X + c * cw;
        // kolom 1 dan 5 = batas kotak penalti → sedikit lebih terang 
        Color col = (c == 1 || c == 5)
                    ? (Color){255, 255, 255, 60}
                    : (Color){255, 255, 255, 28};
        Bres_ThickLine(x, FIELD_Y, x, FIELD_Y + FIELD_H, 1, col);
    }

    // garis baris 
    for (int r = 1; r < rows; r++)
    {
        int y = FIELD_Y + r * rh;
        Bres_ThickLine(FIELD_X, y, FIELD_X + FIELD_W, y, 1,
                       (Color){255, 255, 255, 28});
    }

    // label zona A1–F3 di pojok kiri atas setiap sel 
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            char lbl[3] = { 'A' + c, '1' + r, '\0' };
            int lx = FIELD_X + c * cw + 4;
            int ly = FIELD_Y + r * rh + 4;
            DrawText(lbl, lx + 1, ly + 1, 10, (Color){0,   0,   0,   90});
            DrawText(lbl, lx,     ly,     10, (Color){255, 255, 255, 65});
        }
    }
}


/*
    Render Cache
*/
static RenderTexture2D fieldCache;
static RenderTexture2D stadiumCache;
static bool fieldCached   = false;
static bool stadiumCached = false;

// Helper
static void FillRect(int x, int y, int w, int h, Color col)
{
    for (int row = y; row < y + h; row++)
        BresenhamLine(x, row, x + w - 1, row, col);
}

static void OutlineRect(int x, int y, int w, int h, int thick, Color col)
{
    Bres_ThickLine(x,     y,     x + w, y,     thick, col);
    Bres_ThickLine(x + w, y,     x + w, y + h, thick, col);
    Bres_ThickLine(x + w, y + h, x,     y + h, thick, col);
    Bres_ThickLine(x,     y + h, x,     y,     thick, col);
}

// Penalty Arc
static void DrawPenaltyArc(
    int spotX, int spotY, int radius,
    int boxBoundX, int side, Color col)
{
    int steps = radius * 8;
    for (int i = 0; i <= steps; i++)
    {
        float angle = (float)i / (float)steps * 6.28318f;
        int px = spotX + (int)(radius * cosf(angle) + 0.5f);
        int py = spotY + (int)(radius * sinf(angle) + 0.5f);
        int outside = (side == 0) ? (px > boxBoundX) : (px < boxBoundX);
        if (outside)
            DrawPixel(px, py, col);
    }
}

// Corner Arc
static void DrawCornerArc(
    int cx, int cy, int radius, int dirX,
    int dirY, Color col)
{
    int steps = radius * 8;
    for (int i = 0; i <= steps; i++)
    {
        float angle = (float)i / (float)steps * 6.28318f;
        float ca = cosf(angle), sa = sinf(angle);
        if (ca * dirX >= 0.0f && sa * dirY >= 0.0f)
            DrawPixel(
                cx + (int)(radius * ca + 0.5f),
                cy + (int)(radius * sa + 0.5f), col);
    }
}

/*
    Field_DrawStadium_Internal
*/
static void Field_DrawStadium_Internal(void)
{
    FillRect(0, 0, SCREEN_W, SCREEN_H, c_sky);

    // Top Stand
    int topRows = FIELD_Y / 8;
    for (int row = 0; row < topRows; row++)
    {
        Color c = (row % 2 == 0) ? c_seat_red : c_seat_dark;
        FillRect(0, row * 8, SCREEN_W, 8, c);
    }
    FillRect(SCREEN_W / 2 - 200, FIELD_Y / 2 - 4, 400, 9, c_seat_wht);
    int tw = MeasureText("ARSENAL FC", 10);
    DrawText("ARSENAL FC", SCREEN_W / 2 - tw / 2, FIELD_Y / 2 - 4, 10, c_seat_red);

    // Bottom Stand
    int botY = FIELD_Y + FIELD_H;
    int botRows = (SCREEN_H - botY) / 8;
    for (int row = 0; row < botRows; row++)
    {
        Color c = (row % 2 == 0) ? c_seat_red : c_seat_dark;
        FillRect(0, botY + row * 8, SCREEN_W, 8, c);
    }
    FillRect(0, botY, SCREEN_W, 6, c_board_bg);
    for (int i = 0; i < SCREEN_W / 180; i++)
        DrawText("MAN UTD", 20 + i * 180, botY + 1, 6, c_board_txt);

    // Left Stand
    int leftCols = FIELD_X / 8;
    for (int col = 0; col < leftCols; col++)
    {
        Color c = (col % 2 == 0) ? c_seat_red : c_seat_dark;
        FillRect(col * 8, FIELD_Y, 8, FIELD_H, c);
    }
    FillRect(FIELD_X - 6, FIELD_Y, 6, FIELD_H, c_concrete);

    // Right Stand
    int rightX = FIELD_X + FIELD_W;
    int rightCols = (SCREEN_W - rightX) / 8;
    for (int col = 0; col < rightCols; col++)
    {
        Color c = (col % 2 == 0) ? c_seat_dark : c_seat_red;
        FillRect(rightX + col * 8, FIELD_Y, 8, FIELD_H, c);
    }
    FillRect(rightX, FIELD_Y, 6, FIELD_H, c_concrete);

    // Corner Blocks
    FillRect(0,      0,    FIELD_X,          FIELD_Y,          c_seat_dark);
    FillRect(rightX, 0,    SCREEN_W - rightX, FIELD_Y,          c_seat_dark);
    FillRect(0,      botY, FIELD_X,          SCREEN_H - botY,  c_seat_dark);
    FillRect(rightX, botY, SCREEN_W - rightX, SCREEN_H - botY, c_seat_dark);

    // Corner Highlights (floodlights)
    MidcircleFilled(FIELD_X / 2, FIELD_Y / 2, 8, c_floodlit);
    MidcircleThick(FIELD_X / 2, FIELD_Y / 2, 12, 2, (Color){255, 245, 185, 80});

    MidcircleFilled(rightX + (SCREEN_W - rightX) / 2, FIELD_Y / 2, 8, c_floodlit);
    MidcircleThick(rightX + (SCREEN_W - rightX) / 2, FIELD_Y / 2, 12, 2, (Color){255, 245, 185, 80});

    MidcircleFilled(FIELD_X / 2, botY + (SCREEN_H - botY) / 2, 8, c_floodlit);
    MidcircleThick(FIELD_X / 2, botY + (SCREEN_H - botY) / 2, 12, 2, (Color){255, 245, 185, 80});

    MidcircleFilled(rightX + (SCREEN_W - rightX) / 2, botY + (SCREEN_H - botY) / 2, 8, c_floodlit);
    MidcircleThick(rightX + (SCREEN_W - rightX) / 2, botY + (SCREEN_H - botY) / 2, 12, 2, (Color){255, 245, 185, 80});
}

/*
    Field_Draw_Internal
    Isi sesungguhnya dari Field_Draw + Field_DrawGoals.
*/
static void Field_Draw_Internal(void)
{
    Color darkGreen  = {34,  100, 34,  255};
    Color lightGreen = {56,  130, 56,  255};

    /*
        FIX stripe alignment:
        Setiap stripe dihitung dari batas eksak (integer) berbasis indeks,
        bukan dari lebar tetap yang bisa menimbulkan piksel kosong di tepi.
        stripe ke-i: mulai dari FIELD_X + FIELD_W*i/STRIPE_COUNT
                     selesai di  FIELD_X + FIELD_W*(i+1)/STRIPE_COUNT
        Dengan cara ini semua stripe selalu pas dengan garis tepi lapangan.
    */
    for (int s = 0; s < STRIPE_COUNT; s++)
    {
        int xStart = FIELD_X + FIELD_W * s / STRIPE_COUNT;
        int xEnd   = FIELD_X + FIELD_W * (s + 1) / STRIPE_COUNT;
        Color col  = (s % 2 == 0) ? darkGreen : lightGreen;
        FillRect(xStart, FIELD_Y, xEnd - xStart, FIELD_H, col);
    }

    // Garis tepi lapangan digambar SESUDAH stripes agar menutupi celah piksel
    OutlineRect(FIELD_X, FIELD_Y, FIELD_W, FIELD_H, 2, WHITE);

    int midX = FIELD_X + FIELD_W / 2;
    int midY = FIELD_Y + FIELD_H / 2;
    Bres_ThickLine(midX, FIELD_Y, midX, FIELD_Y + FIELD_H, 2, WHITE);

    int circleR = (int)(FIELD_H * 0.125f);
    MidcircleThick(midX, midY, circleR, 2, WHITE);
    MidcircleFilled(midX, midY, 4, WHITE);

    int pbW = (int)(FIELD_W * 0.14f), pbH = (int)(FIELD_H * 0.44f);
    int pbY = midY - pbH / 2;
    OutlineRect(FIELD_X, pbY, pbW, pbH, 2, WHITE);
    OutlineRect(FIELD_X + FIELD_W - pbW, pbY, pbW, pbH, 2, WHITE);

    int gbW = (int)(FIELD_W * 0.05f), gbH = (int)(FIELD_H * 0.22f);
    int gbY = midY - gbH / 2;
    OutlineRect(FIELD_X, gbY, gbW, gbH, 2, WHITE);
    OutlineRect(FIELD_X + FIELD_W - gbW, gbY, gbW, gbH, 2, WHITE);

    int spotDist = (int)(FIELD_W * 0.10f);
    int lsx = FIELD_X + spotDist, rsx = FIELD_X + FIELD_W - spotDist;
    MidcircleFilled(lsx, midY, 4, WHITE);
    MidcircleFilled(rsx, midY, 4, WHITE);

    int arcR = (int)(FIELD_H * 0.11f);
    DrawPenaltyArc(lsx, midY, arcR, FIELD_X + pbW, 0, WHITE);
    DrawPenaltyArc(rsx, midY, arcR, FIELD_X + FIELD_W - pbW, 1, WHITE);

    int cornR = (int)(FIELD_H * 0.03f);
    DrawCornerArc(FIELD_X,           FIELD_Y,           cornR, +1, +1, WHITE);
    DrawCornerArc(FIELD_X + FIELD_W, FIELD_Y,           cornR, -1, +1, WHITE);
    DrawCornerArc(FIELD_X,           FIELD_Y + FIELD_H, cornR, +1, -1, WHITE);
    DrawCornerArc(FIELD_X + FIELD_W, FIELD_Y + FIELD_H, cornR, -1, -1, WHITE);

    // Goals
    {
        int cy = FIELD_Y + FIELD_H / 2, hg = GOAL_H / 2;
        Color net = {200, 200, 200, 100};

        int lx = FIELD_X - GOAL_W, ly = cy - hg;
        Bres_ThickLine(lx, ly,          lx,      ly + GOAL_H, 3, WHITE);
        Bres_ThickLine(lx, ly,          FIELD_X, ly,          3, WHITE);
        Bres_ThickLine(lx, ly + GOAL_H, FIELD_X, ly + GOAL_H, 3, WHITE);
        for (int r = ly + 8; r < ly + GOAL_H; r += 8)
            BresenhamLine(lx + 1, r, FIELD_X - 1, r, net);
        for (int c = lx + 6; c < FIELD_X; c += 6)
            BresenhamLine(c, ly + 1, c, ly + GOAL_H - 1, net);

        int rx = FIELD_X + FIELD_W, ry = cy - hg;
        Bres_ThickLine(rx + GOAL_W, ry,          rx + GOAL_W, ry + GOAL_H, 3, WHITE);
        Bres_ThickLine(rx,          ry,          rx + GOAL_W, ry,          3, WHITE);
        Bres_ThickLine(rx,          ry + GOAL_H, rx + GOAL_W, ry + GOAL_H, 3, WHITE);
        for (int r = ry + 8; r < ry + GOAL_H; r += 8)
            BresenhamLine(rx + 1, r, rx + GOAL_W - 1, r, net);
        for (int c = rx + 6; c < rx + GOAL_W; c += 6)
            BresenhamLine(c, ry + 1, c, ry + GOAL_H - 1, net);
    }
}

/*
    API 
    Field_DrawStadium, Field_Draw, Field_DrawGoals:
    semua menggunakan cache.
    Cukup panggil ketiganya seperti biasa - caching terjadi otomatis.
*/

void Field_DrawStadium(void)
{
    if (!stadiumCached)
    {
        stadiumCache = LoadRenderTexture(SCREEN_W, SCREEN_H);
        BeginTextureMode(stadiumCache);
        ClearBackground((Color){8, 4, 4, 255});
        Field_DrawStadium_Internal();
        EndTextureMode();
        stadiumCached = true;
    }

    // Flip Y karena RenderTexture Raylib terbalik secara vertikal
    DrawTextureRec(
        stadiumCache.texture,
        (Rectangle){0, 0, (float)SCREEN_W, (float)-SCREEN_H},
        (Vector2){0, 0}, WHITE);
}

void Field_Draw(void)
{
    if (!fieldCached)
    {
        fieldCache = LoadRenderTexture(SCREEN_W, SCREEN_H);
        BeginTextureMode(fieldCache);
        ClearBackground(BLANK);
        Field_Draw_Internal();
        EndTextureMode();
        fieldCached = true;
    }

    DrawTextureRec(
        fieldCache.texture,
        (Rectangle){0, 0, (float)SCREEN_W, (float)-SCREEN_H},
        (Vector2){0, 0}, WHITE);

    if (g_fieldMode == 1) Field_DrawZones();
}

void Field_DrawGoals(void)
{

}
