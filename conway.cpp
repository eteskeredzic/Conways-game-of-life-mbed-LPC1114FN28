#include "mbed.h"
#define dp23 P0_0
#include "stdio.h"
#include "SPI_TFT_ILI9341.h"
#include "string"
#include "Arial12x12.h"
#include "Arial24x23.h"
#include "Arial28x28.h"
#include "font_big.h"

SPI_TFT_ILI9341 TFT(dp2, dp1, dp6, dp24, dp23, dp25, " TFT ");
// mosi , miso , sclk , cs , reset , dc
AnalogIn napon(dp9);
DigitalOut enable(dp14);
bool trenutno[30][40] = { {0} };
bool staro[30][40] = { {0} };

void crtaj()
{
   for (int i = 0; i < 30; ++i)
        for (int j = 0; j < 40; ++j)
            if(trenutno[i][j] != staro[i][j])
                for(int k=0;k<4;k++)
                    for(int l=0;l<4;l++)
                        TFT.pixel(4*i+k, 4*j+l, trenutno[i][j] == 1 ? Black : Green);
}

int dajKomsije(short int x, short int y)
{
    int rez = 0;
    if (staro[x - 1][y - 1] == 1)
        ++rez;
    if (staro[x - 1][y] == 1)
        ++rez;
    if (staro[x - 1][y + 1] == 1)
        ++rez;
    if (staro[x][y - 1] == 1)
        ++rez;
    if (staro[x][y + 1] == 1)
        ++rez;
    if (staro[x + 1][y - 1] == 1)
        ++rez;
    if (staro[x + 1][y] == 1)
        ++rez;
    if (staro[x + 1][y + 1] == 1)
        ++rez;
    return rez;
}

short int a = 0;

int main()
{

  // trenutno[16][14] = trenutno[16][15] = trenutno[16][16] = trenutno[15][16] = trenutno[14][15] = 1;  // glider
   // PULSAR
    trenutno[9][11] = trenutno[9][12] = trenutno[9][13] = trenutno[9][17] = trenutno[9][18] = trenutno[9][19] = 1;
    trenutno[14][11] = trenutno[14][12] = trenutno[14][13] = trenutno[14][17] = trenutno[14][18] = trenutno[14][19] = 1;
    trenutno[16][11] = trenutno[16][12] = trenutno[16][13] = trenutno[16][17] = trenutno[16][18] = trenutno[16][19] = 1;
    trenutno[21][11] = trenutno[21][12] = trenutno[21][13] = trenutno[21][17] = trenutno[21][18] = trenutno[21][19] = 1;
    trenutno[11][9] = trenutno[11][14] = trenutno[11][16] = trenutno[11][21] = 1;
    trenutno[12][9] = trenutno[12][14] = trenutno[12][16] = trenutno[12][21] = 1;
    trenutno[13][9] = trenutno[13][14] = trenutno[13][16] = trenutno[13][21] = 1;
    trenutno[17][9] = trenutno[17][14] = trenutno[17][16] = trenutno[17][21] = 1;
    trenutno[18][9] = trenutno[18][14] = trenutno[18][16] = trenutno[18][21] = 1;
    trenutno[19][9] = trenutno[19][14] = trenutno[19][16] = trenutno[19][21] = 1;

    enable = 1;
    TFT.claim(stdout);
    TFT.set_orientation(1);
    TFT.background(Green);
    TFT.foreground(White);
    TFT.cls();
    TFT.set_font((unsigned char*)Arial12x12);
    crtaj();
        for (int i = 0; i < 30; ++i)
            for (int j = 0; j < 40; ++j)
                staro[i][j] = trenutno[i][j]; // prepisuj
    while (1) {
        for (int i = 1; i < 29; ++i) {
            for (int j = 1; j < 39; ++j) {
                a = dajKomsije(i, j);
                if (staro[i][j] == 1 && (a < 2 || a > 3))
                    trenutno[i][j] = 0; // pravila 1 i 3
                else if (staro[i][j] == 0 && (a == 3))
                    trenutno[i][j] = 1; // pravilo 4
                    else if(staro[i][j] == 1 && (a == 2 || a == 3)) trenutno[i][j] = 1;
            }
        }

        crtaj();
        for (int i = 0; i < 30; ++i)
            for (int j = 0; j < 40; ++j)
                staro[i][j] = trenutno[i][j]; // prepisuj
        wait(0.2);
    }
}
