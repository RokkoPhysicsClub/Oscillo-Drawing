#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>

int a;
int b;
#define N 256

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

void Paint() {
    FILE *fp; // FILE^\¢Ì
    char fname[] = "";
    char str[N];

    printf("ファイル名:");
    scanf("%s", fname);

    char path[] = "../data/";

    fp = fopen(
        strcat(path, fname),
        "r"); // t@CðJ­B¸s·éÆNULLðÔ·B
    if(fp == NULL) {
        printf("%s file not open!\n", fname);
    }

    int elements = 0; // number of elements

    fscanf(fp, "%d", &elements);
    fscanf(fp, "%d", &elements);

    int arr[elements][3];
    for(int i = 0; i < elements; ++i) {
        fscanf(fp, "%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
    }

    for(;;) {
        for(int i = 0; i < elements; ++i) {
            ochiY(255 - arr[i][2]);
            for(int g = arr[i][0]; g <= arr[i][1]; g++) {
                ochiX(g);
            }
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

    Paint();

    return 0;
}
