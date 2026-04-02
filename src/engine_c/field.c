#include "src/engine_h/field.h"
#include "src/engine_h/screen.h"
#include "src/algorithm_h/bresenham.h"
#include "src/algorithm_h/midcircle.h"
#include <math.h> 

// Helper 
static void FillRect(
    int x, int y, int w, 
    int h, Color col)
{
    for (int row = y; row < y+h; row++)
    {
        BresenhamLine(x, row, x+w-1, row, col);
    }
}

static void OutlineRect(int x, int y, int w, int h, 
                        int thick, Color col)
{
    Bres_ThickLine(x, y, x+w, y, thick, col);
    Bres_ThickLine(x+w, y, x+w, y+h, thick, col);
    Bres_ThickLine(x+w, y+h, x, y+h, thick, col);
    Bres_ThickLine(x, y+h, x, y, thick, col);
}

// Penalty Arc 
static void DrawPenaltyArc(
    int spotX, int spotY, int radius,
    int boxBoundX, int side, Color col  )
{
    int steps = radius * 8;
    for (int i = 0; i <= steps; i++) {
        float angle = (float)i / (float)steps * 6.28318f;
        int px = spotX + (int)(radius * cosf(angle) + 0.5f);
        int py = spotY + (int)(radius * sinf(angle) + 0.5f);
        int outside = (side == 0) ? (px > boxBoundX) : (px < boxBoundX);
        if (outside) DrawPixel(px, py, col);
    }   
}

// Corner Arc
static void DrawCornerArc(
    int cx, int cy, int radius, int dirX,
    int dirY, Color col     )
{
    int steps = radius * 8;
    for(int i = 0; i<= steps; i++)
    {
        float angle = (float)i / (float)steps * 6.281318f;
        float ca = cosf(angle), sa = sinf(angle);
        if (ca * dirX >=0.0f && sa * dirY >= 0.0f)
        {
            DrawPixel(cx + (int)(radius*ca+0.5f), cy + (int)(radius*sa+0.5f), col);
        }
    }
}

// Field_DrawStadium 
void Field_DrawStadium(void)
{

    FillRect(0, 0, SCREEN_W, SCREEN_H, c_sky);

    // Top Stand
    int topRows = FIELD_Y / 8;
    for (int row = 0; row < topRows; row++) {
        Color c = (row % 2 == 0) ? c_seat_red : c_seat_dark;
        FillRect(0, row * 8, SCREEN_W, 8, c);
    }
    FillRect(SCREEN_W/2 - 200, FIELD_Y/2 - 4, 400, 9, c_seat_wht);
    int tw = MeasureText("ARSENAL FC", 10);
    DrawText("ARSENAL FC", SCREEN_W/2 - tw/2, FIELD_Y/2 - 4, 10, c_seat_red);

    // Bottom Stand  
    int botY = FIELD_Y + FIELD_H;
    int botRows = (SCREEN_H - botY) / 8;
    for (int row = 0; row < botRows; row++) {
        Color c = (row % 2 == 0) ? c_seat_red : c_seat_dark;
        FillRect(0, botY + row * 8, SCREEN_W, 8, c);
    }
    FillRect(0, botY, SCREEN_W, 6, c_board_bg);
    for (int i = 0; i < SCREEN_W/180; i++)
        DrawText("MAN UTD", 20 + i*180, botY+1, 6, c_board_txt);

    // Left Stand 
    int leftCols = FIELD_X / 8;
    for (int col = 0; col < leftCols; col++) {
        Color c = (col % 2 == 0) ? c_seat_red : c_seat_dark;
        FillRect(col * 8, FIELD_Y, 8, FIELD_H, c);
    }
    FillRect(FIELD_X - 6, FIELD_Y, 6, FIELD_H, c_concrete);

    // Right Stand
    int rightX = FIELD_X + FIELD_W;
    int rightCols = (SCREEN_W - rightX) / 8;
    for (int col = 0; col < rightCols; col++) {
        Color c = (col % 2 == 0) ? c_seat_dark : c_seat_red;
        FillRect(rightX + col * 8, FIELD_Y, 8, FIELD_H, c);
    }
    FillRect(rightX, FIELD_Y, 6, FIELD_H, c_concrete);

    // Corner Blocks 
    FillRect(0, 0, FIELD_X, FIELD_Y, c_seat_dark);
    FillRect(rightX, 0, SCREEN_W-rightX, FIELD_Y, c_seat_dark);
    FillRect(0, botY, FIELD_X, SCREEN_H-botY, c_seat_dark);
    FillRect(rightX, botY, SCREEN_W-rightX, SCREEN_H-botY, c_seat_dark);

    // Corner Highlights 
    MidcircleFilled(FIELD_X/2, FIELD_Y/2, 8, c_floodlit);
    MidcircleThick(FIELD_X/2, FIELD_Y/2, 12, 2, (Color){255,245,185,80});

    MidcircleFilled(rightX + (SCREEN_W-rightX)/2, FIELD_Y/2, 8, c_floodlit);
    MidcircleThick(rightX + (SCREEN_W-rightX)/2, FIELD_Y/2, 12, 2, (Color){255,245,185,80});

    MidcircleFilled(FIELD_X/2, botY + (SCREEN_H-botY)/2, 8, c_floodlit);
    MidcircleThick(FIELD_X/2, botY + (SCREEN_H-botY)/2, 12, 2, (Color){255,245,185,80});

    MidcircleFilled(rightX + (SCREEN_W-rightX)/2, botY + (SCREEN_H-botY)/2, 8, c_floodlit);
    MidcircleThick(rightX + (SCREEN_W-rightX)/2, botY + (SCREEN_H-botY)/2, 12, 2, (Color){255,245,185,80});
}

// Field_Draw 
void Field_Draw(void)
{
    int sw = FIELD_W / STRIPE_COUNT;
    // Generate Stripe
    for (int s = 0; s < STRIPE_COUNT; s++)
    {
        Color col = (s%2==0) ? DARKGREEN : GREEN;
        FillRect(FIELD_X + s*sw, FIELD_Y, sw, FIELD_H, col);
    }
        int filled = sw * STRIPE_COUNT;
    if (filled < FIELD_W)
        FillRect(FIELD_X+filled, FIELD_Y, FIELD_W-filled, FIELD_H, DARKGREEN);

    OutlineRect(FIELD_X, FIELD_Y, FIELD_W, FIELD_H, 2, WHITE);

    int mid_x = FIELD_X + FIELD_W/2;
    int mid_y = FIELD_Y + FIELD_H/2;
    Bres_ThickLine(mid_x, FIELD_Y, mid_x, FIELD_Y+FIELD_H, 2, WHITE);

    int circle_r = (int)(FIELD_H * 0.125f);
    MidcircleThick(mid_x, mid_y, circle_r, 2, WHITE);
    MidcircleFilled(mid_x, mid_y, 4, WHITE);

    int pb_w = (int)(FIELD_W * 0.14f), pb_h = (int)(FIELD_H * 0.44f);
    int pb_y = mid_y - pb_h/2;
    OutlineRect(FIELD_X, pb_y, pb_w, pb_h, 2, WHITE);
    OutlineRect(FIELD_X+FIELD_W-pb_w, pb_y, pb_w, pb_h, 2, WHITE);

    int gb_w = (int)(FIELD_W * 0.05f), gb_h = (int)(FIELD_H * 0.22f);
    int gb_y = mid_y - gb_h/2;
    OutlineRect(FIELD_X, gb_y, gb_w, gb_h, 2, WHITE);
    OutlineRect(FIELD_X+FIELD_W-gb_w, gb_y, gb_w, gb_h, 2, WHITE);

    int spot_dist = (int)(FIELD_W * 0.10f);
    int lsx = FIELD_X + spot_dist, rsx = FIELD_X + FIELD_W - spot_dist;
    MidcircleFilled(lsx, mid_y, 4, WHITE);
    MidcircleFilled(rsx, mid_y, 4, WHITE);

    int arc_r = (int)(FIELD_H * 0.11f);
    DrawPenaltyArc(lsx, mid_y, arc_r, FIELD_X+pb_w, 0, WHITE);
    DrawPenaltyArc(rsx, mid_y, arc_r, FIELD_X+FIELD_W-pb_w, 1, WHITE);

    int corn_r = (int)(FIELD_H * 0.03f);
    DrawCornerArc(FIELD_X, FIELD_Y, corn_r, +1, +1, WHITE);
    DrawCornerArc(FIELD_X+FIELD_W, FIELD_Y, corn_r, -1, +1, WHITE);
    DrawCornerArc(FIELD_X, FIELD_Y+FIELD_H, corn_r, +1, -1, WHITE);
    DrawCornerArc(FIELD_X+FIELD_W, FIELD_Y+FIELD_H, corn_r, -1, -1, WHITE);
}

void Field_DrawGoals(void) 
{
    int cy = FIELD_Y + FIELD_H/2, hg = GOAL_H/2;
    Color net = {200,200,200,100};

    int lx = FIELD_X - GOAL_W, ly = cy - hg;
    Bres_ThickLine(lx, ly, lx, ly+GOAL_H, 3, WHITE);
    Bres_ThickLine(lx, ly, FIELD_X, ly, 3, WHITE);
    Bres_ThickLine(lx, ly+GOAL_H, FIELD_X, ly+GOAL_H, 3, WHITE);
    for (int r = ly+8; r < ly+GOAL_H; r += 8) BresenhamLine(lx+1, r, FIELD_X-1, r, net);
    for (int c = lx+6; c < FIELD_X; c += 6) BresenhamLine(c, ly+1, c, ly+GOAL_H-1, net);

    int rx = FIELD_X + FIELD_W, ry = cy - hg;
    Bres_ThickLine(rx+GOAL_W, ry, rx+GOAL_W, ry+GOAL_H, 3, WHITE);
    Bres_ThickLine(rx, ry, rx+GOAL_W, ry, 3, WHITE);
    Bres_ThickLine(rx, ry+GOAL_H, rx+GOAL_W, ry+GOAL_H, 3, WHITE);
    for (int r = ry+8; r < ry+GOAL_H; r += 8) BresenhamLine(rx+1, r, rx+GOAL_W-1, r, net);
    for (int c = rx+6; c < rx+GOAL_W; c += 6) BresenhamLine(c, ry+1, c, ry+GOAL_H-1, net);
}
