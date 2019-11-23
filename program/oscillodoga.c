#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wiringPi.h>

#define N 256 // 1sÌÅå¶(oCg)

void ochiX(int x) {
    for(int i = 0; i <= 7; i++) {
        digitalWrite(i, (x & 1U));
        x = x >> 1;
    }
}

void ochiY(int y) {
    for(int i = 0; i <= 7; i++) {
        digitalWrite(i + 8, (y & 1U));
        y = y >> 1;
    }
}

void Point(int x, int y) {
    ochiX(x);
    ochiY(y);
    delayMicroseconds(1);
}

void Draw() {
    FILE *fp; // FILE^\¢Ì
    char fname[] = "";
    char str[N];
    double frameRate = 0;
    int frameLength = 0;

    printf("ファイル名:");
    scanf("%s", fname);

    printf("Frame Rate:");
    scanf("%lf", &frameRate);
    frameLength = (int)(1000000.0 / frameRate);

    char path[] = "../data/";

    fp = fopen(
        strcat(path, fname),
        "r"); // t@CðJ­B¸s·éÆNULLðÔ·B
    if(fp == NULL) {
        printf("%s file not open!\n", fname);
    }

    int images = 0; // number of images

    fscanf(fp, "%d", &images);

    // printf("%d\n",images);

    for(int i = 0; i < images; i++) {
        // loop for the number of image

        int elements = 0; // number of elements

        clock_t start, end;
        start = clock();

        fscanf(fp, "%d", &elements);

        int arr[elements][3];

        for(int j = 0; j < elements; j++) {
            // loop for the number of elements
            fscanf(fp, "%d %d %d", &arr[j][0], &arr[j][1], &arr[j][2]);
            if(arr[j][2] != arr[j - 1][2]) {
                ochiY(255 - arr[j][2]);
            }
            for(int g = arr[j][0]; g <= arr[j][1]; g++) {
                ochiX(g);
            }
        }
        Point(i, 0);
        end = clock();
        int t = (int)(((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0);
        if(frameLength > t) {
            delayMicroseconds(frameLength - t);
        } else {
        }
    }
    fclose(fp); // t@CðÂ¶é
}

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

    Draw();

    return 0;
}