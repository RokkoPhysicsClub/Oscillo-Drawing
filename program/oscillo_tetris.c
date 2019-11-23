#include "oscillofunction.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#define WIDTH 10
#define HEIGHT 16
int background[18][12] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int tmp[HEIGHT + 2][WIDTH + 2];
int draw[HEIGHT + 2][WIDTH + 2];
int block[6][4][3][3] = {
    //四角
    {{{1, 1, 0}, {1, 1, 0}, {0, 0, 0}},
     {{1, 1, 0}, {1, 1, 0}, {0, 0, 0}},
     {{1, 1, 0}, {1, 1, 0}, {0, 0, 0}},
     {{1, 1, 0}, {1, 1, 0}, {0, 0, 0}}

    },

    {// L
     {{0, 1, 0}, {0, 1, 0}, {0, 1, 1}},
     {{0, 0, 0}, {1, 1, 1}, {1, 0, 0}},
     {{1, 1, 0}, {0, 1, 0}, {0, 1, 0}},
     {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}}

    },

    {//逆L
     {{0, 1, 0}, {0, 1, 0}, {1, 1, 0}},
     {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}},
     {{0, 1, 1}, {0, 1, 0}, {0, 1, 0}},
     {{0, 0, 0}, {1, 1, 1}, {0, 0, 1}}},

    {//
     //  <-こんなの
     {{0, 1, 0}, {1, 1, 0}, {1, 0, 0}},
     {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}},
     {{0, 1, 0}, {1, 1, 0}, {1, 0, 0}},
     {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}

    },
    //
    // <-こんなの
    {{{1, 0, 0}, {1, 1, 0}, {0, 1, 0}},
     {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}},
     {{1, 0, 0}, {1, 1, 0}, {0, 1, 0}},
     {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}

    },
    //
    ////// <-こんなの
    {{{0, 1, 0}, {1, 1, 1}, {0, 0, 0}},
     {{0, 1, 0}, {0, 1, 1}, {0, 1, 0}},
     {{0, 0, 0}, {1, 1, 1}, {0, 1, 0}},
     {{0, 1, 0}, {1, 1, 0}, {0, 1, 0}}

    }

};

int i = 0;
int j = 0;
int flame;
int score;
int anzen;
int blockx = 4;
int blocky = 1;
int blockrotate = 1;
int blockshape = 1; //ブロックの形
int blockcolor;     //ブロックの色

int kasou_blockx = 4;
int kasou_blocky = 1;
int kasou_blockrotate = 1;
int kasou_blockshape = 1;

char c; // keynum
char command[10];
int main(void) {
    if(wiringPiSetup() == -1)
        return 1;

    pinMode(0, OUTPUT); // pin17
    pinMode(1, OUTPUT); // pin18
    pinMode(2, OUTPUT); // pin27
    pinMode(3, OUTPUT); // pin22
    pinMode(4, OUTPUT); // pin23
    pinMode(5, OUTPUT); // pin24
    pinMode(6, OUTPUT); // pin25
    pinMode(7, OUTPUT); // pin4

    pinMode(8, OUTPUT);  // pin2
    pinMode(9, OUTPUT);  // pin3
    pinMode(10, OUTPUT); // pin8
    pinMode(11, OUTPUT); // pin7
    pinMode(12, OUTPUT); // pin10
    pinMode(13, OUTPUT); // pin9
    pinMode(14, OUTPUT); // pin11
    pinMode(15, OUTPUT); // pin14

    //キー入力のための初期化
    struct termios oldSettings, newSettings;

    tcgetattr(fileno(stdin), &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &newSettings);
    //キー入力のための初期化ここまで
    for(int j = 0; j < HEIGHT + 2; j++) {
        for(int i = 0; i < WIDTH + 2; i++) {
            draw[j][i] = background[j][i]; //配列のコピー
        }
    }

    while(1) {
        flame++;
        for(int j = 0; j < HEIGHT + 2; j++) {
            for(int i = 0; i < WIDTH + 2; i++) {
                draw[j][i] = background[j][i]; //配列のコピー
            }
        }

        // blocky+=1;

        if(flame % 50 == 0)
            command[0] = 115;
        switch(command[0]) {
        case 97:
            anzen = 1;
            kasou_blockx = blockx - 1;
            kasou_blockshape = blockshape;
            kasou_blockrotate = blockrotate;
            kasou_blocky = blocky;
            for(j = kasou_blocky; j < kasou_blocky + 3; j++) {
                for(i = kasou_blockx; i < kasou_blockx + 3; i++) {
                    // printf("kasou_block[%d][%d]:background[%d][%d]\n",j-kasou_blocky,i-kasou_blockx,j,i);
                    if(block[kasou_blockshape][kasou_blockrotate]
                            [j - kasou_blocky][i - kasou_blockx] != 0 &&
                       background[j][i] != 0) {
                        anzen = 0;
                    }
                }
            }
            if(anzen == 1) {
                blockx -= 1;
            }
            break;
        case 100:
            anzen = 1;
            kasou_blockshape = blockshape;
            kasou_blockrotate = blockrotate;
            kasou_blocky = blocky;
            kasou_blockx = blockx + 1;
            for(j = kasou_blocky; j < kasou_blocky + 3; j++) {
                for(i = kasou_blockx; i < kasou_blockx + 3; i++) {
                    // printf("kasou_block[%d][%d]:background[%d][%d]\n",j-kasou_blocky,i-kasou_blockx,j,i);
                    if(block[kasou_blockshape][kasou_blockrotate]
                            [j - kasou_blocky][i - kasou_blockx] != 0 &&
                       background[j][i] != 0) {
                        anzen = 0;
                    } else {
                        // blockx+=1;
                    }
                }
            }
            if(anzen == 1) {
                blockx += 1;
            }
            break;
        case 115: //落ちる
            anzen = 1;
            kasou_blockx = blockx;
            kasou_blockshape = blockshape;
            kasou_blockrotate = blockrotate;
            kasou_blocky = blocky + 1;
            for(j = kasou_blocky; j < kasou_blocky + 3; j++) {
                for(i = kasou_blockx; i < kasou_blockx + 3; i++) {
                    // printf("block[%d][%d]:background[%d][%d]\n",j-blocky,i-blockx,j,i);
                    if(block[kasou_blockshape][kasou_blockrotate]
                            [j - kasou_blocky][i - kasou_blockx] != 0 &&
                       background[j][i] != 0) {
                        anzen = 0;
                        kasou_blocky -= 1;
                        for(int l = 0; l < 3; l++) {
                            for(int k = 0; k < 3; k++) {
                                if(block[kasou_blockshape][kasou_blockrotate][l]
                                        [k] != 0)
                                    background[kasou_blocky + l][kasou_blockx +
                                                                 k] =
                                        block[kasou_blockshape]
                                             [kasou_blockrotate][l][k];
                            }
                        }
                        for(int l = 0; l < 3; l++) {
                            for(int k = 0; k < 3; k++) {
                                if(block[kasou_blockshape][kasou_blockrotate][l]
                                        [k] != 0)
                                    draw[kasou_blocky + l][kasou_blockx + k] =
                                        block[kasou_blockshape]
                                             [kasou_blockrotate][l][k];
                            }
                        }
                        int combo = 0;
                        for(int l = 1; l < HEIGHT + 1; l++) {
                            int yokocount = 0; //揃った数数える
                            for(int k = 1; k < WIDTH + 1; k++) {
                                if(background[l][k] != 0)
                                    yokocount++;
                            }
                            if(yokocount == WIDTH) {
                                score += 100;

                                for(int m = l; m > 1; m--) {
                                    for(int k = 1; k < WIDTH + 1; k++) {
                                        background[m][k] =
                                            background[m - 1][k]; // 1行消す
                                        yokocount = 0;
                                    }
                                }
                            }
                            score += combo * 100;
                        }
                        srand((unsigned)time(NULL));
                        i = 4;
                        j = 4; //ループ抜け
                        int rs = rand() % 6;
                        int rr = rand() % 4;
                        kasou_blockx = 4;
                        kasou_blocky = 2;
                        kasou_blockshape = rs;
                        kasou_blockrotate = rr;

                        blockx = 4;
                        blocky = 2;
                        blockshape = rs;
                        blockrotate = rr;
                        break;
                    }
                }
            }
            if(anzen == 1) {
                blocky += 1;
            }
            break;
        case 119: //回転
            anzen = 1;
            kasou_blockx = blockx;
            kasou_blockshape = blockshape;
            kasou_blocky = blocky;
            kasou_blockrotate = (blockrotate + 1) % 4;
            for(j = blocky; j < blocky + 3; j++) {
                for(i = kasou_blockx; i < kasou_blockx + 3; i++) {
                    // printf("block[%d][%d]:background[%d][%d]\n",j-blocky,i-blockx,j,i);
                    if(block[kasou_blockshape][kasou_blockrotate]
                            [j - kasou_blocky][i - kasou_blockx] != 0 &&
                       background[j][i] != 0) {
                        // blockrotate-=1;
                        anzen = 0;
                    }
                }
            }
            if(anzen == 1) {
                blockrotate += 1;
                blockrotate = blockrotate % 4;
            }

            break;
        }

        if(command[0] == 115) {
        }

        for(int j = blocky; j < 3 + blocky; j++) {
            for(int i = blockx; i < 3 + blockx; i++) {
                if(block[blockshape][blockrotate][j - blocky][i - blockx] != 0)
                    draw[j][i] = block[blockshape][blockrotate][j - blocky]
                                      [i - blockx]; //ブロックの設置(見るよう)
            }
        }
        // printf("%d,%d:score:%d\n",blockx,blocky,score);

        for(int j = 0; j < HEIGHT + 2; j++) { //表示
            for(int i = 0; i < WIDTH + 2; i++) {
                switch(draw[j][i]) {
                case 0:
                    // printf(" ");

                    break;
                case 1:
                    Square(i * 12, 255 - j * 12, (i + 1) * 12, 255 - j * 12,
                           i * 12, 255 - (j + 1) * 12, (i + 1) * 12,
                           255 - (j + 1) * 12);
                    Square(i * 12, 255 - (j + 1) * 12, (i + 1) * 12,
                           255 - (j + 1) * 12, (i + 1) * 12, 255 - j * 12,
                           i * 12, 255 - j * 12);
                    // Paint2("block1.osi",i*12,j*12);
                    // printf("#");
                    break;
                }
            }
            // printf("\n");
        }

        command[0] = 1;
        //キーボード入力処理ここから(正直わからん)

        fd_set set;
        struct timeval tv;
        tv.tv_sec = 0.1;
        tv.tv_usec = 0;
        FD_ZERO(&set);
        FD_SET(fileno(stdin), &set);
        int res = select(fileno(stdin) + 1, &set, NULL, NULL, &tv);
        if(res > 0) {
            read(fileno(stdin), &c, 1);
            command[0] = c;
        }

        //キーボード入力処理ここまで
    }

    tcsetattr(fileno(stdin), TCSANOW, &oldSettings); //キー入力の終了処理
    return 0;
}
