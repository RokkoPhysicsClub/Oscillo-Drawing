#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <wiringPi.h>
#include <pthread.h>

#define N 256
int dot[256][256];
int dot2[256][256];

typedef struct {
    int map[65536];
    int end;
} data;

data d;

void ochiX(int x) {
    for (int i = 0; i <= 7; i++) {
        digitalWrite(i, (x & 1U));
        x = x >> 1;
    }
}

void ochiY(int y) {
    for (int i = 0; i <= 7; i++) {
        digitalWrite(i + 8, (y & 1U));
        y = y >> 1;
    }
}

void Point(int x, int y) {
    ochiX(x);
    ochiY(y);
    //delayMicroseconds(1);
}

void *program(void *p) {
    struct timeval tv;
    int time;
    FILE *fp;
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
               strcat(path, fname),"r");
    if (fp == NULL) {
        printf("%s file not open!\n", fname);
    }
    
    int images = 0;  // number of images
    
    fscanf(fp, "%d", &images);
    
    for (int i = 0; i < images; i++) {
        // loop for the number of image
        
        int elements = 0;  // number of elements
        
        //    clock_t start, end;
        //    start = clock();
        
        gettimeofday(&tv, NULL);
        time = (int)(tv.tv_usec);
        
        fscanf(fp, "%d", &elements);
        
        int arr[elements][3];
        
        for(int i=0; i < 256; i++){
            for(int j=0;j < 256; j++){
                dot2[255-i][j] = 0;
            }
        }
        
        for (int j = 0; j < elements; j++) {
            // loop for the number of elements
            fscanf(fp, "%d %d %d", &arr[j][0], &arr[j][1], &arr[j][2]);
            for (int g = arr[j][0]; g <= arr[j][1]; g++) {
                dot2[255-arr[j][2]][g] = 1;
            }
        }
        
        for(int i=0; i < 256; i++){
            for(int j=0;j < 256; j++){
                dot[255-i][j] = dot2[255-i][j];
            }
        }
        
        //end = clock();
        int dt = 0;
        gettimeofday(&tv, NULL);
        dt = (int)(tv.tv_usec - time);
        if (frameLength > dt && dt > 0) {
            delayMicroseconds(frameLength - dt);
        }if(dt < 0 && frameLength > (1000000 - dt)){
            delayMicroseconds(frameLength - (1000000 - dt));
        } else {
        }
    }
    fclose(fp);
    return 0;
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
