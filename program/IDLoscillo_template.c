#include "oscillofunctionMT.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct {
    int map[65536];
    int end;
} data;

data d;

void *program(void *p) {
    //Edit here
LineM(127,100,127,40);
LineM(0,40,255,40);
//PointM(1,1);
}

void *convert(void *p) {
    int num = 0;
    for(;;){
        for(int i = 0;i < 256;i+=2){
            for(int j = 0;j < 256;j++){
                if(dot[255-i][j] == 1){
                    d.map[num] = j + ((255-i) << 8);
                    num++;
                }
            }
        }

        for(int i = 1;i < 256;i+=2){
            for(int j = 0;j < 256;j++){
                if(dot[255-i][j] == 1){
                    d.map[num] = j + ((255-i) << 8);
                    num++;
                }
            }
        }
        
        for(int i = num + 1;i < 65536;i++){
            d.map[i] = 0;
        }
        d.end = num;
        num = 0;
    }
}

void *display(void *p) {
    int x,y;
    for(;;){
        for(int i = 0;i < d.end;i++){
            x = d.map[i] & 255;
            y = d.map[i] >> 8;
            if(i > 0 && y != d.map[i-1]>>8){
                ochiY(y);
            }
            for(int i = 0;i < 1 + (20000 / (d.end + 1));i++){
                ochiX(x);
            }
        }
    }
    return 0;
}

int main(void) {
    
    if (wiringPiSetup() == -1) return 1;
    
    pinMode(0, OUTPUT);  // pin17
    pinMode(1, OUTPUT);  // pin18
    pinMode(2, OUTPUT);  // pin27
    pinMode(3, OUTPUT);  // pin22
    pinMode(4, OUTPUT);  // pin23
    pinMode(5, OUTPUT);  // pin24
    pinMode(6, OUTPUT);  // pin25
    pinMode(7, OUTPUT);  // pin4
    
    pinMode(8, OUTPUT);   // pin2
    pinMode(9, OUTPUT);   // pin3
    pinMode(10, OUTPUT);  // pin8
    pinMode(11, OUTPUT);  // pin7
    pinMode(12, OUTPUT);  // pin10
    pinMode(13, OUTPUT);  // pin9
    pinMode(14, OUTPUT);  // pin11
    pinMode(15, OUTPUT);  // pin14
    
    pthread_t pthread[3];
    pthread_create( &pthread[0], NULL, &program, &dot);
    pthread_create( &pthread[1], NULL, &convert, &dot);
    pthread_create( &pthread[2], NULL, &display, &d);
    
    pthread_join(pthread[0], NULL); 
    pthread_join(pthread[1], NULL);
    pthread_join(pthread[2], NULL);
    
    return 0;
}
