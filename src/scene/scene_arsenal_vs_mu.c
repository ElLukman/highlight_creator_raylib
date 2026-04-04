#include "src/scene/scene_arsenal_vs_mu.h"
#include "src/engine_h/highlight.h"
#include "src/engine_h/field.h"
#include "src/engine_h/screen_size.h"
#include <string.h>
#include <math.h>

/* Arsenal 2 - 3 Man Utd | Liga Inggris */

#define ARS      (Color){220,  30,  30, 255}
#define MU       (Color){ 20,  20,  20, 255}
#define ARS_GK   (Color){255, 105, 180, 255}  /* PINK */
#define MU_GK    (Color){  0, 230,  50, 255}  /* LIME */
#define GK_NUM   (Color){ 20,  20,  20, 255}

#define RED_TXT  (Color){255,  80,  80, 255}
#define BLUE_TXT (Color){180, 180, 255, 255}

static void SpawnAll(Highlight *h, float t, PlayerDef defs[], int n)
{
    for (int i = 0; i < n; i++)
        HL_Spawn(h, t, i, defs[i]);
}

Highlight Scene_ARS_MUN_Build(void)
{
    Highlight h;
    Highlight_Init(&h,
        "Arsenal  vs  Man Utd",
        "Liga Inggris  |  Full-time: 2-3",
        "Arsenal", "Man Utd", ARS, MU);
    h.minute = 20;
    h.score1 = 0;
    h.score2 = 0;
    float t = 0.0f;

    /* ============================================================
       GOL 1 - 29' | OG Martinez | 1-0
       ============================================================ */
    PlayerDef g1[22] = {
        P_NUM("Raya      ",  1, ARS_GK, GK_NUM,  204,  540,   204,  540, 0.0f, LINEAR),
        P("Hincapie  ",  5, ARS, 1021,  181,  1021,  181, 0.0f, LINEAR),
        P("Gabriel   ",  6, ARS,  972,  359,   972,  359, 0.0f, LINEAR),
        P("Saliba    ",  2, ARS, 1056,  764,  1056,  764, 0.0f, LINEAR),
        P("Timber    ", 12, ARS, 1465,  492,  1465,  492, 0.0f, LINEAR),
        P("Zubimendi ", 36, ARS,  850,  486,   850,  486, 0.0f, LINEAR),
        P("Rice      ", 41, ARS, 1102,  349,  1102,  349, 0.0f, LINEAR),
        P("Odegaard  ",  8, ARS, 1310,  591,  1310,  591, 0.0f, LINEAR),
        P("Trossard  ", 19, ARS, 1389,  148,  1389,  148, 0.0f, LINEAR),
        P("Jesus     ", 19, ARS, 1312,  343,  1312,  343, 0.0f, LINEAR),
        P("Saka      ",  7, ARS, 1453,  811,  1453,  811, 0.0f, LINEAR),
        P_NUM("Lammens   ",  1,  MU_GK, GK_NUM, 1725,  475,  1725,  475, 0.0f, LINEAR),
        P("Dalot     ",  2,  MU, 1441,  246,  1441,  246, 0.0f, LINEAR),
        P("Maguire   ",  5,  MU, 1412,  354,  1412,  354, 0.0f, LINEAR),
        P("Martinez  ",  6,  MU, 1539,  544,  1539,  544, 0.0f, LINEAR),
        P("Shaw      ", 23,  MU, 1426,  601,  1426,  601, 0.0f, LINEAR),
        P("Casemiro  ", 18,  MU, 1217,  488,  1217,  488, 0.0f, LINEAR),
        P("Mainoo    ", 37,  MU, 1198,  345,  1198,  345, 0.0f, LINEAR),
        P("Fernandes ",  8,  MU, 1145,  683,  1145,  683, 0.0f, LINEAR),
        P("Amad      ", 16,  MU, 1030,  538,  1030,  538, 0.0f, LINEAR),
        P("Mbeumo    ", 19,  MU, 1031,  283,  1031,  283, 0.0f, LINEAR),
        P("Dorgu     ", 13,  MU, 1523,  718,  1523,  718, 0.0f, LINEAR),
    };
    SpawnAll(&h, t, g1, 22);
    HL_BallAt(&h, t, 1074, 183);
    t += 0.3f;

    /* Aksi 1->2 (3s) */
    HL_Move(&h, t,  0, P_CONT(g1[ 0],  262,  532, 2.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g1[ 1], 1339,  256, 2.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g1[ 2], 1134,  419, 2.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g1[ 3], 1184,  707, 2.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g1[ 4], 1535,  544, 2.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g1[ 5],  891,  509, 2.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g1[ 6], 1044,  295, 2.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g1[ 7], 1385,  570, 2.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g1[ 8], 1487,  143, 2.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g1[ 9], 1523,  457, 2.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g1[10], 1569,  757, 2.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g1[12], 1554,  321, 2.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g1[13], 1540,  396, 2.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g1[14], 1600,  541, 2.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g1[15], 1562,  611, 2.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g1[16], 1339,  480, 2.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g1[17], 1375,  345, 2.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g1[18], 1223,  652, 2.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g1[19], 1076,  525, 2.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g1[20], 1213,  296, 2.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g1[21], 1561,  679, 2.0f, LINEAR));
    g1[0].ex=262;g1[0].ey=532;
    HL_Ball(&h, t, B(1074, 183, 1387, 268, 2.0f, LINEAR));
    t += 2.0f;

    /* Aksi 2->3 (2s) */
    HL_Move(&h, t,  0, P_CONT(g1[ 0],  294,  535, 2.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g1[ 1], 1512,  311, 2.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g1[ 2], 1183,  455, 2.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g1[ 3], 1210,  707, 2.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g1[ 4], 1639,  547, 2.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g1[ 5],  926,  501, 2.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g1[ 6], 1206,  318, 2.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g1[ 7], 1541,  622, 2.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g1[ 8], 1461,  192, 2.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g1[ 9], 1691,  462, 2.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g1[10], 1670,  747, 2.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g1[11], 1786,  540, 2.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g1[12], 1670,  347, 2.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g1[13], 1659,  417, 2.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g1[14], 1678,  528, 2.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g1[15], 1643,  577, 2.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g1[16], 1565,  561, 2.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g1[17], 1543,  469, 2.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g1[18], 1272,  652, 2.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g1[19], 1111,  530, 2.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g1[20], 1449,  349, 2.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g1[21], 1688,  625, 2.0f, LINEAR));
    HL_Ball(&h, t, B(1387, 268, 1685, 648, 2.0f, LINEAR));
    t += 2.0f;

    /* Aksi 3->4 (2s) */
    HL_Move(&h, t,  1, P_CONT(g1[ 1], 1631,  384, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g1[ 2], 1195,  455, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g1[ 3], 1430,  640, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g1[ 5],  949,  522, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g1[ 6], 1296,  341, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g1[ 7], 1558,  643, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g1[ 8], 1545,  319, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g1[ 9], 1677,  457, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g1[10], 1638,  713, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g1[12], 1667,  381, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g1[13], 1711,  448, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g1[16], 1608,  621, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g1[17], 1607,  466, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g1[18], 1391,  564, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g1[19], 1123,  533, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g1[20], 1504,  378, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1685, 648, 1639, 697, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 4->5 (1s) */
    HL_Move(&h, t,  0, P_CONT(g1[ 0],  323,  527, 1.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g1[ 1], 1636,  397, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g1[ 2], 1369,  489, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g1[ 3], 1410,  661, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g1[ 4], 1648,  544, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g1[ 5], 1088,  525, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g1[ 6], 1383,  357, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g1[ 7], 1590,  651, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g1[ 8], 1574,  345, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g1[ 9], 1689,  457, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g1[10], 1725,  726, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g1[12], 1707,  394, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g1[13], 1728,  453, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g1[14], 1690,  531, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g1[15], 1715,  595, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g1[16], 1666,  647, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g1[17], 1581,  502, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g1[18], 1513,  647, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g1[19], 1210,  541, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g1[20], 1547,  409, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g1[21], 1729,  664, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1639, 697, 1737, 713, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 5->6 (1s) - bezier */
    HL_Move(&h, t,  0, P_CONT(g1[ 0],  346,  545, 1.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g1[ 1], 1656,  410, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g1[ 2], 1499,  520, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g1[ 3], 1451,  661, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g1[ 4], 1668,  570, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g1[ 5], 1120,  528, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g1[ 6], 1424,  370, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g1[ 8], 1600,  363, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g1[ 9], 1695,  486, 1.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g1[11], 1789,  558, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g1[12], 1710,  415, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g1[13], 1739,  505, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g1[14], 1707,  567, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g1[15], 1660,  642, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g1[16], 1709,  668, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g1[17], 1601,  575, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g1[18], 1542,  663, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g1[19], 1288,  531, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g1[20], 1564,  401, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g1[21], 1758,  656, 1.0f, LINEAR));
    HL_Ball(&h, t, B_BEZ(1737, 713, 1615, 656, 1676, 570, 1.0f));
    t += 1.0f;

    /* Aksi 6->7 (1s) */
    HL_Move(&h, t,  0, P_CONT(g1[ 0],  360,  550, 0.5f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g1[ 1], 1670,  407, 0.5f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g1[ 2], 1516,  515, 0.5f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g1[ 3], 1463,  669, 0.5f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g1[ 4], 1685,  573, 0.5f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g1[ 5], 1126,  531, 0.5f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g1[ 6], 1430,  378, 0.5f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g1[ 7], 1599,  646, 0.5f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g1[ 8], 1612,  366, 0.5f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g1[ 9], 1704,  483, 0.5f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g1[10], 1731,  713, 0.5f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g1[11], 1792,  566, 0.5f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g1[12], 1722,  415, 0.5f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g1[13], 1745,  505, 0.5f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g1[14], 1716,  570, 0.5f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g1[15], 1645,  627, 0.5f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g1[16], 1700,  665, 0.5f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g1[17], 1615,  572, 0.5f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g1[18], 1577,  681, 0.5f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g1[19], 1294,  531, 0.5f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g1[20], 1561,  406, 0.5f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g1[21], 1758,  648, 0.5f, LINEAR));
    HL_Ball(&h, t, B(1615, 656, 1733, 573, 0.5f, LINEAR));
    t += 0.5f;

    /* Aksi 7->8 (bola masuk) */
    HL_Move(&h, t, 11, P_CONT(g1[11], 1801, 553, 0.5f, LINEAR));
    HL_Ball(&h, t, B(1733, 573, 1820, 563, 0.5f, LINEAR));
    t += 0.5f;

    /* ===== GOL 1 - Aksi 7 ===== */
    HL_Goal(&h, t, 1, 0, 29);
    HL_Text(&h, t, "GOOOL!! 1-0  |  29'  OG Martinez", 28, GOLD);

    /* Aksi 8->9 selebrasi (5s) */
    HL_Move(&h, t,  0, P_CONT(g1[ 0],  317,  602, 5.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g1[ 1], 1560,  578, 5.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g1[ 2], 1545,  704, 5.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g1[ 3], 1434,  708, 5.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g1[ 4], 1617,  788, 5.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g1[ 5], 1280,  682, 5.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g1[ 6], 1486,  655, 5.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g1[ 7], 1587,  857, 5.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g1[ 8], 1566,  483, 5.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g1[ 9], 1666,  755, 5.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g1[10], 1673,  842, 5.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g1[11], 1815,  548, 5.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g1[12], 1728,  415, 5.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g1[13], 1757,  510, 5.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g1[14], 1728,  573, 5.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g1[15], 1665,  630, 5.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g1[16], 1712,  673, 5.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g1[17], 1624,  572, 5.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g1[18], 1603,  674, 5.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g1[19], 1320,  550, 5.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g1[20], 1575,  409, 5.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g1[21], 1770,  651, 5.0f, LINEAR));
    t += 5.0f;

    HL_Hide(&h, t);

    /* ============================================================
       GOL 2 - 37' | Mbeumo | 1-1
       ============================================================ */
    PlayerDef g2[22] = {
        P_NUM("Raya      ",  1, ARS_GK, GK_NUM,  184,  527,   184,  527, 0.0f, LINEAR),
        P("Hincapie  ",  5, ARS,  981,  142,   981,  142, 0.0f, LINEAR),
        P("Gabriel   ",  6, ARS,  529,  352,   529,  352, 0.0f, LINEAR),
        P("Saliba    ",  2, ARS,  500,  562,   500,  562, 0.0f, LINEAR),
        P("Timber    ", 12, ARS,  804,  868,   804,  868, 0.0f, LINEAR),
        P("Zubimendi ", 36, ARS,  633,  716,   633,  716, 0.0f, LINEAR),
        P("Rice      ", 41, ARS,  818,  634,   818,  634, 0.0f, LINEAR),
        P("Odegaard  ",  8, ARS,  985,  507,   985,  507, 0.0f, LINEAR),
        P("Trossard  ", 19, ARS, 1259,  137,  1259,  137, 0.0f, LINEAR),
        P("Jesus     ", 19, ARS, 1261,  478,  1261,  478, 0.0f, LINEAR),
        P("Saka      ",  7, ARS, 1294,  904,  1294,  904, 0.0f, LINEAR),
        P_NUM("Lammens   ",  1,  MU_GK, GK_NUM, 1783,  535,  1783,  535, 0.0f, LINEAR),
        P("Dalot     ",  2,  MU, 1328,  298,  1328,  298, 0.0f, LINEAR),
        P("Maguire   ",  5,  MU, 1336,  478,  1336,  478, 0.0f, LINEAR),
        P("Martinez  ",  6,  MU, 1339,  645,  1339,  645, 0.0f, LINEAR),
        P("Shaw      ", 23,  MU, 1348,  842,  1348,  842, 0.0f, LINEAR),
        P("Casemiro  ", 18,  MU,  830,  566,   830,  566, 0.0f, LINEAR),
        P("Mainoo    ", 37,  MU, 1020,  564,  1020,  564, 0.0f, LINEAR),
        P("Fernandes ",  8,  MU,  690,  659,   690,  659, 0.0f, LINEAR),
        P("Amad      ", 16,  MU,  999,  269,   999,  269, 0.0f, LINEAR),
        P("Mbeumo    ", 19,  MU,  625,  454,   625,  454, 0.0f, LINEAR),
        P("Dorgu     ", 13,  MU,  877,  772,   877,  772, 0.0f, LINEAR),
    };
    SpawnAll(&h, t, g2, 22);
    HL_BallAt(&h, t, 581, 647);
    t += 0.3f;

    /* Aksi 1->2 (1s) */
    HL_Move(&h, t,  1, P_CONT(g2[ 1], 1004,  155, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g2[ 2],  584,  295, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g2[ 4],  772,  868, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g2[ 5],  561,  732, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g2[ 6],  972,  665, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g2[ 7],  976,  497, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g2[ 8], 1250,  137, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g2[ 9], 1249,  475, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g2[10], 1271,  914, 1.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g2[11], 1760,  532, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g2[12], 1314,  288, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g2[13], 1330,  483, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g2[14], 1319,  648, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g2[15], 1334,  842, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g2[16],  844,  602, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g2[17],  971,  546, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g2[18],  626,  625, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g2[19],  958,  261, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g2[20],  602,  475, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g2[21],  851,  769, 1.0f, LINEAR));
    HL_Ball(&h, t, B(581, 647, 517, 580, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 2->3 (2s) */
    HL_Move(&h, t,  1, P_CONT(g2[ 1],  987,  158, 2.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g2[ 2],  590,  313, 2.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g2[ 3],  558,  580, 2.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g2[ 4],  763,  871, 2.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g2[ 5],  515,  743, 2.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g2[ 6],  940,  662, 2.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g2[ 7],  878,  461, 2.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g2[ 8], 1233,  140, 2.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g2[ 9], 1214,  467, 2.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g2[10], 1236,  904, 2.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g2[12], 1276,  278, 2.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g2[13], 1298,  478, 2.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g2[15], 1279,  816, 2.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g2[16],  774,  586, 2.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g2[17],  951,  492, 2.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g2[18],  594,  661, 2.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g2[19],  857,  258, 2.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g2[20],  570,  519, 2.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g2[21],  828,  764, 2.0f, LINEAR));
    HL_Ball(&h, t, B(517, 580, 508, 715, 2.0f, LINEAR));
    t += 2.0f;

    /* Aksi 3->4 (2s) */
    HL_Move(&h, t,  0, P_CONT(g2[ 0],  274,  506, 2.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g2[ 1],  961,  166, 2.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g2[ 2],  460,  352, 2.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g2[ 3],  572,  619, 2.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g2[ 4],  734,  861, 2.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g2[ 5],  440,  709, 2.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g2[ 6],  920,  659, 2.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g2[ 7],  811,  458, 2.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g2[ 8], 1175,  153, 2.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g2[ 9], 1147,  483, 2.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g2[10], 1199,  899, 2.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g2[12], 1238,  286, 2.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g2[13], 1266,  486, 2.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g2[14], 1302,  651, 2.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g2[15], 1241,  803, 2.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g2[16],  676,  594, 2.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g2[17],  922,  505, 2.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g2[18],  388,  609, 2.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g2[19],  701,  315, 2.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g2[20],  443,  496, 2.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g2[21],  796,  761, 2.0f, LINEAR));
    HL_Ball(&h, t, B(508, 715, 412, 497, 2.0f, LINEAR));
    t += 2.0f;

    /* Aksi 4->5 (1s) */
    HL_Move(&h, t,  0, P_CONT(g2[ 0],  315,  493, 1.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g2[ 1],  923,  174, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g2[ 2],  347,  406, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g2[ 3],  491,  614, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g2[ 4],  656,  864, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g2[ 5],  327,  662, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g2[ 6],  874,  646, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g2[ 7],  759,  450, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g2[ 8], 1149,  176, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g2[ 9], 1118,  486, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g2[10], 1144,  899, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g2[12], 1209,  291, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g2[13], 1217,  502, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g2[14], 1238,  661, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g2[15], 1189,  806, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g2[16],  647,  597, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g2[17],  893,  505, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g2[18],  301,  599, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g2[19],  556,  349, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g2[20],  397,  483, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g2[21],  738,  779, 1.0f, LINEAR));
    HL_Ball(&h, t, B(412, 497, 371, 469, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 5->6 (2s) - Mbeumo tembak */
    HL_Move(&h, t,  0, P_CONT(g2[ 0],  329,  503, 2.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g2[ 1],  787,  218, 2.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g2[ 2],  231,  484, 2.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g2[ 3],  398,  630, 2.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g2[ 4],  618,  861, 2.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g2[ 5],  211,  626, 2.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g2[ 6],  816,  687, 2.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g2[ 7],  675,  458, 2.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g2[ 8], 1103,  202, 2.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g2[ 9], 1043,  481, 2.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g2[10], 1063,  868, 2.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g2[12], 1171,  291, 2.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g2[13], 1101,  502, 2.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g2[14], 1180,  648, 2.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g2[15], 1131,  788, 2.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g2[16],  566,  582, 2.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g2[17],  861,  505, 2.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g2[18],  208,  570, 2.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g2[19],  400,  424, 2.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g2[20],  313,  426, 2.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g2[21],  692,  784, 2.0f, LINEAR));
    HL_Ball(&h, t, B(371, 469, 103, 495, 2.0f, LINEAR));
    t += 2.0f;

    /* ===== GOL 2 - di bawah Aksi 5->6 ===== */
    HL_Goal(&h, t, 1, 1, 37);
    HL_Text(&h, t, "GOOOL!! 1-1  |  37'  Mbeumo", 28, WHITE);

    /* Aksi 6->7 selebrasi MU (8s) */
    HL_Move(&h, t,  0, P_CONT(g2[ 0],  112,  529, 8.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g2[ 1],  494,  397, 8.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g2[ 2],  219,  494, 8.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g2[ 3],  300,  594, 8.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g2[ 4],  409,  786, 8.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g2[ 5],  205,  608, 8.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g2[ 6],  593,  534, 8.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g2[ 7],  745,  458, 8.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g2[ 8],  678,  350, 8.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g2[ 9],  913,  522, 8.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g2[10],  860,  868, 8.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g2[12],  456,  242, 8.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g2[13],  397,  308, 8.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g2[14], 1010,  335, 8.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g2[15], 1067,  708, 8.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g2[16],  308,  277, 8.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g2[17],  371,  246, 8.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g2[18],  225,  298, 8.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g2[19],  296,  229, 8.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g2[20],  286,  164, 8.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g2[21],  342,  333, 8.0f, LINEAR));
    HL_Ball(&h, t, B(103, 495, 130, 534, 8.0f, LINEAR));
    t += 8.0f;

    HL_Hide(&h, t);
    /* ============================================================
       GOL 3 - 50' | Dorgu | 1-2  (BABAK 2 - sisi bertukar)
       Arsenal GK di kanan, MU GK di kiri
       ============================================================ */
    PlayerDef g3[22] = {
        P_NUM("Raya      ",  1, ARS_GK, GK_NUM, 1783,  530,  1783,  530, 0.0f, LINEAR),
        P("Hincapie  ",  5, ARS, 1528,  718,  1528,  718, 0.0f, LINEAR),
        P("Gabriel   ",  6, ARS, 1541,  592,  1541,  592, 0.0f, LINEAR),
        P("Saliba    ",  2, ARS, 1456,  427,  1456,  427, 0.0f, LINEAR),
        P("Timber    ", 12, ARS, 1500,  311,  1500,  311, 0.0f, LINEAR),
        P("Zubimendi ", 36, ARS, 1210,  490,  1210,  490, 0.0f, LINEAR),
        P("Rice      ", 41, ARS, 1292,  551,  1292,  551, 0.0f, LINEAR),
        P("Odegaard  ",  8, ARS, 1159,  374,  1159,  374, 0.0f, LINEAR),
        P("Trossard  ", 19, ARS, 1160,  764,  1160,  764, 0.0f, LINEAR),
        P("Jesus     ", 19, ARS, 1027,  563,  1027,  563, 0.0f, LINEAR),
        P("Saka      ",  7, ARS, 1247,  220,  1247,  220, 0.0f, LINEAR),
        P_NUM("Lammens   ",  1,  MU_GK, GK_NUM,  213,  496,   213,  496, 0.0f, LINEAR),
        P("Dalot     ",  2,  MU, 1018,  861,  1018,  861, 0.0f, LINEAR),
        P("Maguire   ",  5,  MU,  907,  683,   907,  683, 0.0f, LINEAR),
        P("Martinez  ",  6,  MU, 1008,  316,  1008,  316, 0.0f, LINEAR),
        P("Shaw      ", 23,  MU, 1253,  104,  1253,  104, 0.0f, LINEAR),
        P("Casemiro  ", 18,  MU,  971,  512,   971,  512, 0.0f, LINEAR),
        P("Mainoo    ", 37,  MU, 1088,  522,  1088,  522, 0.0f, LINEAR),
        P("Fernandes ",  8,  MU, 1318,  426,  1318,  426, 0.0f, LINEAR),
        P("Amad      ", 16,  MU, 1410,  876,  1410,  876, 0.0f, LINEAR),
        P("Mbeumo    ", 19,  MU, 1479,  633,  1479,  633, 0.0f, LINEAR),
        P("Dorgu     ", 13,  MU, 1369,  295,  1369,  295, 0.0f, LINEAR),
    };
    SpawnAll(&h, t, g3, 22);
    HL_BallAt(&h, t, 1038, 317);
    t += 0.3f;

    /* Aksi 1->2 (1s) */
    HL_Move(&h, t,  1, P_CONT(g3[ 1], 1520,  742, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g3[ 2], 1500,  566, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g3[ 3], 1428,  432, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g3[ 4], 1451,  314, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g3[ 5], 1230,  472, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g3[ 7], 1171,  371, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g3[ 8], 1230,  751, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g3[ 9], 1050,  534, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g3[10], 1276,  251, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g3[12], 1056,  866, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g3[13],  921,  704, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g3[14], 1034,  316, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g3[15], 1265,  120, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g3[16], 1014,  504, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g3[17], 1117,  514, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g3[18], 1379,  431, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g3[19], 1410,  832, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g3[20], 1499,  641, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g3[21], 1328,  316, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1038, 317, 1327, 351, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 2->3 (1s) */
    HL_Move(&h, t,  0, P_CONT(g3[ 0], 1783,  535, 1.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g3[ 1], 1494,  726, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g3[ 2], 1483,  540, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g3[ 3], 1422,  432, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g3[ 4], 1425,  296, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g3[ 5], 1242,  428, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g3[ 6], 1295,  543, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g3[ 7], 1188,  371, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g3[ 8], 1233,  738, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g3[ 9], 1050,  557, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g3[10], 1319,  303, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g3[12], 1102,  837, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g3[13],  962,  720, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g3[14], 1066,  316, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g3[15], 1285,  130, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g3[16], 1028,  486, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g3[17], 1146,  545, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g3[18], 1373,  428, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g3[19], 1384,  814, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g3[20], 1488,  623, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g3[21], 1294,  370, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1327, 351, 1293, 410, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 3->4 (1s) */
    HL_Move(&h, t,  1, P_CONT(g3[ 1], 1485,  723, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g3[ 2], 1477,  527, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g3[ 3], 1436,  427, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g3[ 4], 1434,  286, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g3[ 5], 1283,  415, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g3[ 6], 1304,  574, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g3[ 7], 1188,  361, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g3[ 8], 1236,  748, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g3[ 9], 1059,  557, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g3[10], 1328,  293, 1.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g3[11],  193,  512, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g3[12], 1093,  806, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g3[13],  997,  712, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g3[16], 1037,  483, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g3[17], 1166,  571, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g3[19], 1384,  824, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g3[20], 1474,  615, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g3[21], 1242,  414, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1293, 410, 1351, 433, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 4->5 */
    HL_Move(&h, t,  1, P_CONT(g3[ 1], 1485,  731, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g3[ 2], 1492,  511, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g3[ 4], 1448,  289, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g3[ 5], 1292,  386, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g3[ 6], 1287,  488, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g3[ 8], 1245,  738, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g3[ 9], 1108,  531, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g3[10], 1325,  288, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g3[12], 1102,  788, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g3[14], 1066,  319, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g3[15], 1285,  133, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g3[17], 1175,  467, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g3[19], 1387,  837, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g3[20], 1483,  615, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1351, 433, 1264, 427, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 5->6 */
    HL_Move(&h, t,  1, P_CONT(g3[ 1], 1499,  728, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g3[ 2], 1506,  511, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g3[ 3], 1488,  427, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g3[ 4], 1460,  292, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g3[ 5], 1335,  360, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g3[ 6], 1293,  472, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g3[ 7], 1200,  364, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g3[ 8], 1248,  735, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g3[ 9], 1149,  539, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g3[10], 1354,  285, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g3[12], 1114,  765, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g3[13], 1026,  715, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g3[14], 1095,  324, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g3[16], 1063,  491, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g3[17], 1195,  470, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g3[18], 1370,  431, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g3[19], 1401,  832, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g3[21], 1343,  546, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1264, 427, 1360, 442, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 6->7 */
    HL_Move(&h, t,  0, P_CONT(g3[ 0], 1786,  519, 1.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g3[ 1], 1458,  723, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g3[ 2], 1486,  537, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g3[ 3], 1491,  437, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g3[ 4], 1504,  333, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g3[ 5], 1364,  368, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g3[ 6], 1336,  477, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g3[ 7], 1220,  385, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g3[ 8], 1268,  704, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g3[ 9], 1227,  555, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g3[10], 1412,  303, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g3[12], 1181,  768, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g3[13], 1096,  684, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g3[14], 1141,  340, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g3[16], 1109,  483, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g3[17], 1259,  478, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g3[18], 1370,  434, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g3[19], 1375,  798, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g3[20], 1492,  631, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g3[21], 1366,  541, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1360, 442, 1389, 530, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 7->8 (2s) */
    HL_Move(&h, t,  1, P_CONT(g3[ 1], 1550,  648, 2.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g3[ 2], 1509,  550, 2.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g3[ 3], 1581,  548, 2.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g3[ 4], 1556,  444, 2.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g3[ 5], 1451,  453, 2.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g3[ 6], 1382,  529, 2.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g3[ 7], 1318,  462, 2.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g3[ 8], 1297,  683, 2.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g3[ 9], 1262,  571, 2.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g3[10], 1539,  371, 2.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g3[12], 1230,  732, 2.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g3[13], 1125,  671, 2.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g3[14], 1317,  351, 2.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g3[16], 1234,  424, 2.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g3[17], 1285,  457, 2.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g3[18], 1390,  444, 2.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g3[19], 1410,  772, 2.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g3[20], 1527,  629, 2.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g3[21], 1459,  539, 2.0f, LINEAR));
    HL_Ball(&h, t, B(1389, 530, 1482, 541, 2.0f, LINEAR));
    t += 2.0f;

    /* Aksi 8->9 (1s) - Dorgu tembak */
    HL_Move(&h, t,  1, P_CONT(g3[ 1], 1666,  594, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g3[ 2], 1552,  581, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g3[ 3], 1581,  553, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g3[ 4], 1582,  483, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g3[ 5], 1480,  456, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g3[ 6], 1382,  545, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g3[ 7], 1353,  480, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g3[ 8], 1375,  667, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g3[ 9], 1300,  584, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g3[10], 1574,  381, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g3[12], 1279,  735, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g3[13], 1186,  650, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g3[14], 1360,  346, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g3[16], 1344,  395, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g3[17], 1302,  457, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g3[18], 1445,  431, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g3[19], 1604,  702, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g3[20], 1628,  598, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g3[21], 1569,  581, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1482, 541, 1820, 488, 1.0f, LINEAR));
    t += 1.0f;

    /* ===== GOL 3 - di bawah Aksi 8->9 ===== */
    HL_Goal(&h, t, 1, 2, 50);
    HL_Text(&h, t, "GOOOL!! 1-2  |  50'  Patrick Dorgu", 28, WHITE);

    /* Aksi 9->10 selebrasi MU (21s) */
    HL_Move(&h, t,  0, P_CONT(g3[ 0], 1719,  530, 21.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g3[ 1], 1440,  750, 21.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g3[ 2], 1393,  573, 21.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g3[ 3], 1573,  568, 21.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g3[ 4], 1562,  382, 21.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g3[ 5], 1486,  236, 21.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g3[ 6], 1403,  425, 21.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g3[ 7], 1232,  496, 21.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g3[ 8], 1114,  742, 21.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g3[ 9], 1039,  514, 21.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g3[10], 1209,  267, 21.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g3[11],  474,  906, 21.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g3[12], 1592,  872, 21.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g3[13], 1533,  863, 21.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g3[14], 1708,  784, 21.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g3[15], 1569,  775, 21.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g3[16], 1611,  794, 21.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g3[17], 1551,  820, 21.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g3[18], 1650,  791, 21.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g3[19], 1638,  855, 21.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g3[20], 1706,  831, 21.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g3[21], 1685,  871, 21.0f, LINEAR));
    HL_Ball(&h, t, B(1820, 488, 1808, 499, 21.0f, LINEAR));
    t += 21.0f;
    t += 2.0f;  /* jeda pasca gol */

    HL_Hide(&h, t);
    /* ============================================================
       GOL 4 - 84' | Merino | 2-2  (Substitusi aktif)
       ============================================================ */
    HL_Hide(&h, t);

    PlayerDef g4b[22] = {
        P_NUM("Raya",      1, ARS_GK, GK_NUM, 1820,  553,  1820,  553, 0.0f, LINEAR),
        P("B.White",   4, ARS,  122,  630,   122,  630, 0.0f, LINEAR),
        P("Gabriel",   6, ARS,  164,  488,   164,  488, 0.0f, LINEAR),
        P("Saliba",    2, ARS,  290,  593,   290,  593, 0.0f, LINEAR),
        P("Timber",   12, ARS,  251,  675,   251,  675, 0.0f, LINEAR),
        P("Eze",      10, ARS,  428,  619,   428,  619, 0.0f, LINEAR),
        P("Rice",     41, ARS,  100,  630,   100,  630, 0.0f, LINEAR),
        P("Merino",   23, ARS,  176,  590,   176,  590, 0.0f, LINEAR),
        P("Madueke",  20, ARS,  364,  400,   364,  400, 0.0f, LINEAR),
        P("Gyokeres", 11, ARS,  297,  524,   297,  524, 0.0f, LINEAR),
        P("Saka",      7, ARS,  100,   80,   100,   80, 0.0f, LINEAR),
        P_NUM("Lammens",   1, MU_GK, GK_NUM,  100,  519,   100,  519, 0.0f, LINEAR),
        P("Dalot",     2,  MU,  238,  491,   238,  491, 0.0f, LINEAR),
        P("Maguire",   5,  MU,  172,  508,   172,  508, 0.0f, LINEAR),
        P("Martinez",  6,  MU,  246,  581,   246,  581, 0.0f, LINEAR),
        P("Shaw",     23,  MU,  150,  559,   150,  559, 0.0f, LINEAR),
        P("Casemiro", 18,  MU,  180,  455,   180,  455, 0.0f, LINEAR),
        P("Mainoo",   37,  MU,  148,  515,   148,  515, 0.0f, LINEAR),
        P("Fernandes", 8,  MU,  205,  388,   205,  388, 0.0f, LINEAR),
        P("Amad",     16,  MU,  288,  408,   288,  408, 0.0f, LINEAR),
        P("Cunha",    10,  MU,  141,  614,   141,  614, 0.0f, LINEAR),
        P("Sesko",    30,  MU,  178,  548,   178,  548, 0.0f, LINEAR),
    };
    SpawnAll(&h, t, g4b, 22);
    HL_BallAt(&h, t, 113, 89);
    t += 0.3f;

    /* Aksi 1->2 (2s) */
    HL_Move(&h, t,  1, P_CONT(g4b[ 1],  168,  591, 2.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g4b[ 2],  211,  468, 2.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g4b[ 3],  269,  512, 2.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g4b[ 4],  258,  651, 2.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g4b[ 5],  366,  611, 2.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g4b[ 6],  172,  596, 2.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g4b[ 7],  232,  458, 2.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g4b[ 8],  321,  401, 2.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g4b[ 9],  250,  522, 2.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g4b[11],  206,  461, 2.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g4b[12],  256,  488, 2.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g4b[13],  209,  478, 2.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g4b[14],  264,  458, 2.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g4b[15],  175,  548, 2.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g4b[16],  186,  444, 2.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g4b[17],  223,  454, 2.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g4b[18],  255,  400, 2.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g4b[19],  310,  469, 2.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g4b[20],  208,  584, 2.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g4b[21],  100,  568, 2.0f, LINEAR));
    HL_Ball(&h, t, B(113, 89, 229, 438, 2.0f, LINEAR));
    t += 2.0f;

    /* Aksi 2->3 (1s) */
    HL_Move(&h, t,  0, P_CONT(g4b[ 0], 1675,  530, 1.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g4b[ 1],  178,  543, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g4b[ 2],  197,  465, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g4b[ 5],  360,  589, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g4b[ 6],  211,  598, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g4b[ 7],  242,  428, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g4b[ 8],  303,  393, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g4b[ 9],  236,  517, 1.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g4b[11],  202,  439, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g4b[13],  234,  469, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g4b[14],  262,  451, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g4b[15],  188,  540, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g4b[16],  186,  429, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g4b[17],  261,  483, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g4b[18],  262,  377, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g4b[19],  300,  462, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g4b[20],  116,  541, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g4b[21],  103,  573, 1.0f, LINEAR));
    HL_Ball(&h, t, B(229, 438, 129, 539, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 3->4 (1s) */
    HL_Move(&h, t,  1, P_CONT(g4b[ 1],  171,  559, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g4b[ 2],  170,  481, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g4b[ 3],  311,  508, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g4b[ 4],  232,  646, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g4b[ 5],  306,  577, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g4b[ 6],  198,  611, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g4b[ 7],  206,  485, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g4b[ 9],  252,  558, 1.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g4b[11],  214,  451, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g4b[14],  284,  455, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g4b[15],  241,  593, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g4b[16],  159,  441, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g4b[17],  261,  494, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g4b[19],  310,  502, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g4b[21],  100,  582, 1.0f, LINEAR));
    HL_Ball(&h, t, B(129, 539, 182, 506, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 4->5 (0.8s) */
    HL_Move(&h, t,  0, P_CONT(g4b[ 0], 1619,  522, 0.8f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g4b[ 1],  159,  566, 0.8f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g4b[ 4],  210,  661, 0.8f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g4b[ 5],  294,  574, 0.8f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g4b[ 6],  191,  611, 0.8f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g4b[ 8],  261,  386, 0.8f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g4b[ 9],  235,  551, 0.8f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g4b[10],  220,  169, 0.8f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g4b[11],  159,  506, 0.8f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g4b[13],  157,  540, 0.8f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g4b[14],  300,  424, 0.8f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g4b[15],  224,  589, 0.8f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g4b[16],  147,  438, 0.8f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g4b[17],  288,  483, 0.8f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g4b[18],  217,  386, 0.8f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g4b[19],  288,  534, 0.8f, LINEAR));
    HL_Ball(&h, t, B(182, 506, 104, 584, 0.8f, LINEAR));
    t += 0.8f;

    /* Aksi 5->6 (1s) */
    HL_Move(&h, t,  2, P_CONT(g4b[ 2],  163,  466, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g4b[ 3],  365,  462, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g4b[ 4],  272,  695, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g4b[ 5],  356,  584, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g4b[ 6],  211,  643, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g4b[ 7],  225,  447, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g4b[ 8],  280,  367, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g4b[ 9],  260,  577, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g4b[10],  285,  200, 1.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g4b[11],  120,  525, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g4b[12],  255,  483, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g4b[13],  180,  582, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g4b[14],  332,  400, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g4b[15],  254,  635, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g4b[16],  147,  415, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g4b[17],  292,  475, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g4b[18],  197,  364, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g4b[19],  311,  586, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g4b[20],  250,  547, 1.0f, LINEAR));
    HL_Ball(&h, t, B(104, 584, 362, 465, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 6->7 (0.8s) - Merino tembak */
    HL_Move(&h, t,  0, P_CONT(g4b[ 0], 1613,  509, 0.8f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g4b[ 1],  166,  600, 0.8f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g4b[ 2],  175,  447, 0.8f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g4b[ 3],  382,  482, 0.8f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g4b[ 4],  288,  721, 0.8f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g4b[ 5],  372,  576, 0.8f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g4b[ 6],  345,  642, 0.8f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g4b[ 7],  248,  445, 0.8f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g4b[ 8],  292,  355, 0.8f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g4b[ 9],  247,  599, 0.8f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g4b[10],  339,  248, 0.8f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g4b[11],  120,  513, 0.8f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g4b[12],  200,  509, 0.8f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g4b[13],  193,  570, 0.8f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g4b[14],  375,  385, 0.8f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g4b[15],  232,  657, 0.8f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g4b[16],  158,  395, 0.8f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g4b[17],  328,  449, 0.8f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g4b[18],  203,  343, 0.8f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g4b[19],  304,  616, 0.8f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g4b[20],  289,  517, 0.8f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g4b[21],  107,  586, 0.8f, LINEAR));
    HL_Ball(&h, t, B(362, 465, 353, 566, 0.8f, LINEAR));
    t += 0.8f;

    /* ===== GOL 4 - di bawah Aksi 6->7 ===== */
    HL_Goal(&h, t, 2, 2, 84);
    HL_Text(&h, t, "GOOOL!! 2-2  |  84'  Mikel Merino", 28, GOLD);

    /* Aksi 7->8 (0.7s) */
    HL_Move(&h, t,  1, P_CONT(g4b[ 1],  166,  626, 0.7f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g4b[ 2],  188,  457, 0.7f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g4b[ 3],  409,  489, 0.7f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g4b[ 4],  298,  748, 0.7f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g4b[ 6],  371,  654, 0.7f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g4b[ 7],  298,  452, 0.7f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g4b[ 8],  334,  355, 0.7f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g4b[ 9],  256,  621, 0.7f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g4b[10],  355,  278, 0.7f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g4b[11],  143,  560, 0.7f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g4b[12],  209,  510, 0.7f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g4b[13],  212,  589, 0.7f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g4b[14],  388,  385, 0.7f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g4b[15],  248,  687, 0.7f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g4b[16],  167,  406, 0.7f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g4b[17],  337,  449, 0.7f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g4b[18],  226,  336, 0.7f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g4b[19],  324,  646, 0.7f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g4b[20],  262,  535, 0.7f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g4b[21],  206,  647, 0.7f, LINEAR));
    HL_Ball(&h, t, B(353, 566, 271, 530, 0.7f, LINEAR));
    t += 0.7f;

    /* Aksi 8->9 selebrasi Arsenal (11s) */
    HL_Move(&h, t,  0, P_CONT(g4b[ 0], 1483,  399, 11.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g4b[ 1],  147,  269, 11.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g4b[ 2],  165,  201, 11.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g4b[ 3],  293,  235, 11.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g4b[ 4],  172,  331, 11.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g4b[ 5],  220,  207, 11.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g4b[ 6],  258,  196, 11.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g4b[ 7],  175,  149, 11.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g4b[ 8],  282,  160, 11.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g4b[ 9],  224,  280, 11.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g4b[10],  223,  140, 11.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g4b[11],  143,  560, 11.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g4b[12],  345,  836, 11.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g4b[13],  306,  650, 11.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g4b[14],  351,  399, 11.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g4b[15],  399,  223, 11.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g4b[16],  561,  622, 11.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g4b[17],  576,  405, 11.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g4b[18],  708,  538, 11.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g4b[19],  846,  233, 11.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g4b[20],  805,  752, 11.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g4b[21],  906,  542, 11.0f, LINEAR));
    HL_Ball(&h, t, B(271, 530, 961, 539, 11.0f, LINEAR));
    t += 11.0f;

    HL_Hide(&h, t);
    /* ============================================================
       GOL 5 - 87' | Cunha | 2-3
       ============================================================ */
    HL_Hide(&h, t);

    PlayerDef g5[22] = {
        P_NUM("Raya",      1, ARS_GK, GK_NUM, 1820,  537,  1820,  537, 0.0f, LINEAR),
        P("B.White",   4, ARS, 1374,  315,  1374,  315, 0.0f, LINEAR),
        P("Gabriel",   6, ARS, 1458,  551,  1458,  551, 0.0f, LINEAR),
        P("Saliba",    2, ARS, 1376,  467,  1376,  467, 0.0f, LINEAR),
        P("Timber",   12, ARS, 1383,  737,  1383,  737, 0.0f, LINEAR),
        P("Eze",      10, ARS, 1054,  412,  1054,  412, 0.0f, LINEAR),
        P("Rice",     41, ARS, 1220,  468,  1220,  468, 0.0f, LINEAR),
        P("Merino",   23, ARS, 1197,  391,  1197,  391, 0.0f, LINEAR),
        P("Madueke",  20, ARS, 1062,  295,  1062,  295, 0.0f, LINEAR),
        P("Gyokeres", 11, ARS,  817,  487,   817,  487, 0.0f, LINEAR),
        P("Saka",      7, ARS, 1040,  575,  1040,  575, 0.0f, LINEAR),
        P_NUM("Lammens",   1, MU_GK, GK_NUM,  100,  552,   100,  552, 0.0f, LINEAR),
        P("Dalot",     2,  MU,  989,  588,   989,  588, 0.0f, LINEAR),
        P("Maguire",   5,  MU,  719,  529,   719,  529, 0.0f, LINEAR),
        P("Martinez",  6,  MU,  790,  431,   790,  431, 0.0f, LINEAR),
        P("Shaw",     23,  MU,  938,  216,   938,  216, 0.0f, LINEAR),
        P("Casemiro", 18,  MU,  947,  432,   947,  432, 0.0f, LINEAR),
        P("Mainoo",   37,  MU, 1176,  417,  1176,  417, 0.0f, LINEAR),
        P("Fernandes", 8,  MU, 1120,  329,  1120,  329, 0.0f, LINEAR),
        P("Amad",     16,  MU, 1281,  737,  1281,  737, 0.0f, LINEAR),
        P("Cunha",    10,  MU, 1294,  312,  1294,  312, 0.0f, LINEAR),
        P("Sesko",    30,  MU, 1316,  475,  1316,  475, 0.0f, LINEAR),
    };
    SpawnAll(&h, t, g5, 22);
    HL_BallAt(&h, t, 1141, 318);
    t += 0.3f;

    /* Aksi 1->2 (1s) */
    HL_Move(&h, t,  0, P_CONT(g5[ 0], 1808,  521, 1.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g5[ 1], 1396,  297, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g5[ 2], 1467,  551, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g5[ 3], 1393,  463, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g5[ 4], 1382,  701, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g5[ 5], 1083,  413, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g5[ 6], 1242,  431, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g5[ 7], 1229,  328, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g5[ 9],  868,  503, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g5[10], 1075,  590, 1.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g5[11],  138,  543, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g5[13],  741,  552, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g5[14],  836,  419, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g5[15], 1003,  215, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g5[16],  988,  420, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g5[17], 1166,  409, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g5[18], 1150,  320, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g5[19], 1307,  732, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g5[20], 1292,  386, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g5[21], 1332,  536, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1141, 318, 1180, 317, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 2->3 (0.5s) */
    HL_Move(&h, t,  1, P_CONT(g5[ 1], 1396,  304, 0.5f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g5[ 2], 1477,  551, 0.5f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g5[ 3], 1420,  472, 0.5f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g5[ 4], 1379,  697, 0.5f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g5[ 5], 1092,  416, 0.5f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g5[ 6], 1256,  434, 0.5f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g5[ 7], 1203,  337, 0.5f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g5[ 8], 1081,  291, 0.5f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g5[ 9],  884,  507, 0.5f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g5[10], 1104,  607, 0.5f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g5[12], 1034,  623, 0.5f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g5[13],  783,  579, 0.5f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g5[14],  846,  399, 0.5f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g5[15], 1032,  215, 0.5f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g5[16], 1004,  440, 0.5f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g5[17], 1172,  401, 0.5f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g5[18], 1241,  298, 0.5f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g5[19], 1317,  732, 0.5f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g5[20], 1321,  384, 0.5f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g5[21], 1347,  509, 0.5f, LINEAR));
    HL_Ball(&h, t, B(1180, 317, 1195, 384, 0.5f, LINEAR));
    t += 0.5f;

    /* Aksi 3->4 (1s) */
    HL_Move(&h, t,  0, P_CONT(g5[ 0], 1779,  512, 1.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g5[ 1], 1408,  296, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g5[ 2], 1477,  535, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g5[ 3], 1458,  438, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g5[ 4], 1408,  675, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g5[ 5], 1127,  393, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g5[ 6], 1211,  383, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g5[ 7], 1242,  372, 1.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g5[ 8], 1135,  303, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g5[ 9],  907,  519, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g5[10], 1143,  592, 1.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g5[11],  155,  543, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g5[12], 1038,  632, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g5[13],  813,  586, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g5[14],  879,  415, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g5[15], 1058,  210, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g5[16], 1029,  445, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g5[17], 1186,  409, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g5[19], 1327,  736, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g5[21], 1407,  466, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1195, 384, 1314, 389, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 4->5 (1s) */
    HL_Move(&h, t,  0, P_CONT(g5[ 0], 1762,  512, 1.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g5[ 1], 1437,  305, 1.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g5[ 2], 1478,  523, 1.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g5[ 3], 1481,  400, 1.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g5[ 4], 1464,  647, 1.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g5[ 5], 1152,  419, 1.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g5[ 6], 1238,  422, 1.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g5[ 7], 1200,  368, 1.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g5[ 9],  924,  527, 1.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g5[10], 1225,  583, 1.0f, LINEAR));
    HL_Move(&h, t, 11, P_CONT(g5[11],  196,  543, 1.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g5[12], 1092,  608, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g5[13],  832,  613, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g5[14],  886,  419, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g5[15], 1080,  232, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g5[16], 1057,  471, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g5[17], 1305,  361, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g5[18], 1334,  293, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g5[19], 1382,  762, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g5[20], 1292,  428, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g5[21], 1437,  461, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1314, 389, 1292, 459, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 5->6 (2s) */
    HL_Move(&h, t,  0, P_CONT(g5[ 0], 1765,  497, 2.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g5[ 1], 1564,  346, 2.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g5[ 2], 1511,  510, 2.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g5[ 3], 1552,  431, 2.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g5[ 4], 1539,  629, 2.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g5[ 5], 1201,  419, 2.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g5[ 6], 1303,  453, 2.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g5[ 7], 1323,  344, 2.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g5[ 8], 1240,  275, 2.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g5[ 9],  962,  523, 2.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g5[10], 1221,  595, 2.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g5[12], 1138,  603, 2.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g5[13],  886,  616, 2.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g5[14],  940,  424, 2.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g5[15], 1132,  228, 2.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g5[16], 1086,  466, 2.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g5[17], 1431,  399, 2.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g5[18], 1495,  321, 2.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g5[19], 1504,  700, 2.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g5[20], 1382,  493, 2.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g5[21], 1599,  452, 2.0f, LINEAR));
    HL_Ball(&h, t, B(1292, 459, 1398, 500, 2.0f, LINEAR));
    t += 2.0f;

    /* Aksi 6->7 (0.8s) - Cunha tembak */
    HL_Move(&h, t,  0, P_CONT(g5[ 0], 1784,  523, 0.8f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g5[ 1], 1605,  351, 0.8f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g5[ 2], 1515,  517, 0.8f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g5[ 3], 1574,  430, 0.8f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g5[ 4], 1623,  606, 0.8f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g5[ 5], 1237,  465, 0.8f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g5[ 6], 1419,  497, 0.8f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g5[ 8], 1275,  264, 0.8f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g5[ 9], 1040,  481, 0.8f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g5[10], 1317,  645, 0.8f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g5[12], 1164,  630, 0.8f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g5[13],  987,  600, 0.8f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g5[14], 1130,  351, 0.8f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g5[15], 1249,  210, 0.8f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g5[16], 1147,  494, 0.8f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g5[17], 1500,  433, 0.8f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g5[18], 1528,  326, 0.8f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g5[19], 1600,  707, 0.8f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g5[20], 1449,  548, 0.8f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g5[21], 1632,  432, 0.8f, LINEAR));
    HL_Ball(&h, t, B(1398, 500, 1820, 600, 0.8f, LINEAR));
    t += 0.8f;

    /* ===== GOL 5 - di bawah Aksi 6->7 ===== */
    HL_Goal(&h, t, 2, 3, 87);
    HL_Text(&h, t, "GOOOOL!!  CUNHA 2-3!!  MAN UTD MENANG!! 87'", 30, WHITE);

    /* Aksi 7->8 selebrasi MU (8s) */
    HL_Move(&h, t,  0, P_CONT(g5[ 0], 1819,  549, 8.0f, LINEAR));
    HL_Move(&h, t,  1, P_CONT(g5[ 1], 1544,  340, 8.0f, LINEAR));
    HL_Move(&h, t,  2, P_CONT(g5[ 2], 1522,  719, 8.0f, LINEAR));
    HL_Move(&h, t,  3, P_CONT(g5[ 3], 1603,  437, 8.0f, LINEAR));
    HL_Move(&h, t,  4, P_CONT(g5[ 4], 1596,  590, 8.0f, LINEAR));
    HL_Move(&h, t,  5, P_CONT(g5[ 5], 1120,  262, 8.0f, LINEAR));
    HL_Move(&h, t,  6, P_CONT(g5[ 6], 1328,  593, 8.0f, LINEAR));
    HL_Move(&h, t,  7, P_CONT(g5[ 7], 1359,  403, 8.0f, LINEAR));
    HL_Move(&h, t,  8, P_CONT(g5[ 8], 1126,  765, 8.0f, LINEAR));
    HL_Move(&h, t,  9, P_CONT(g5[ 9], 1023,  508, 8.0f, LINEAR));
    HL_Move(&h, t, 10, P_CONT(g5[10], 1182,  496, 8.0f, LINEAR));
    HL_Move(&h, t, 12, P_CONT(g5[12], 1645,  273, 8.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g5[13], 1559,  224, 8.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g5[14], 1609,  199, 8.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g5[15], 1637,  183, 8.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g5[16], 1614,  238, 8.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g5[17], 1642,  218, 8.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g5[18], 1687,  189, 8.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g5[19], 1693,  286, 8.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g5[20], 1759,  196, 8.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g5[21], 1686,  223, 8.0f, LINEAR));
    HL_Ball(&h, t, B(1820, 600, 1795, 532, 8.0f, LINEAR));
    t += 8.0f;

    /* Aksi 8->9 */
    HL_Move(&h, t, 20, P_CONT(g5[20], 1762,  153, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 9->10 */
    HL_Move(&h, t, 12, P_CONT(g5[12], 1633,  297, 1.0f, LINEAR));
    HL_Move(&h, t, 13, P_CONT(g5[13], 1614,  145, 1.0f, LINEAR));
    HL_Move(&h, t, 14, P_CONT(g5[14], 1609,  210, 1.0f, LINEAR));
    HL_Move(&h, t, 15, P_CONT(g5[15], 1640,  190, 1.0f, LINEAR));
    HL_Move(&h, t, 16, P_CONT(g5[16], 1608,  264, 1.0f, LINEAR));
    HL_Move(&h, t, 17, P_CONT(g5[17], 1638,  230, 1.0f, LINEAR));
    HL_Move(&h, t, 18, P_CONT(g5[18], 1696,  193, 1.0f, LINEAR));
    HL_Move(&h, t, 19, P_CONT(g5[19], 1693,  295, 1.0f, LINEAR));
    HL_Move(&h, t, 20, P_CONT(g5[20], 1774,  201, 1.0f, LINEAR));
    HL_Move(&h, t, 21, P_CONT(g5[21], 1689,  239, 1.0f, LINEAR));
    HL_Ball(&h, t, B(1795, 532, 1048, 508, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 10->11 */
    HL_Move(&h, t, 20, P_CONT(g5[20], 1770, 173, 1.0f, LINEAR));
    t += 1.0f;

    /* Aksi 11->12 */
    HL_Move(&h, t, 20, P_CONT(g5[20], 1770, 227, 1.0f, LINEAR));
    t += 1.0f;

    /* Full time */
    HL_Hide(&h, t);
    HL_Text(&h, t, "PELUIT PANJANG!!  FT: Arsenal 2 - 3 Manchester United", 24, YELLOW);
    HL_Wait(&h, t + 4.5f);

    h.running = true;
    return h;
}
