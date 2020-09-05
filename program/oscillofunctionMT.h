#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#define N 256
int dot[256][256];

void ochiX(int x) {
  for(int i = 0;i <= 7;i++){
    digitalWrite(i, (x & 1U));
    x = x >> 1;
  }
}

void ochiY(int y) {
  for(int i = 0;i <= 7;i++){
    digitalWrite(i+8, (y & 1U));
    y = y >> 1;
  }
}

void Point(int x,int y){
  ochiX(x);
  ochiY(y);
  //delayMicroseconds(1);
}

void PointM(int x,int y){
    dot[y][x] = 1;
}
void unPointM(int x,int y){
    dot[y][x] = 0;
}

void LineM(int x1, int y1, int x2, int y2){
  int distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
  for (int i = 0; i < distance; i++) {
    int x = x1 + (x2 - x1) * i / distance;
    int y = y1 + (y2 - y1) * i / distance;
      dot[y][x] = 1;
  }
}
void unLineM(int x1, int y1, int x2, int y2){
    int distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    for (int i = 0; i < distance; i++) {
        int x = x1 + (x2 - x1) * i / distance;
        int y = y1 + (y2 - y1) * i / distance;
        dot[y][x] = 0;
    }
}


void verticalM(int y1, int y2, int x){
  for (int g = y1; g <= y2; g++){
      dot[g][x] = 1;
  }
}
void unverticalM(int y1, int y2, int x){
    for (int g = y1; g <= y2; g++){
        dot[g][x] = 0;
    }
}

void horizontalM(int x1, int x2,int y){
  for (int g = x1; g <= x2; g++){
      dot[y][g] = 1;
  }
}
void unhorizontalM(int x1, int x2,int y){
    for (int g = x1; g <= x2; g++){
        dot[y][g] = 0;
    }
}

void SquareM(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
  LineM(x1, y1, x2, y2);
  LineM(x2, y2, x3, y3);
  LineM(x3, y3, x4, y4);
  LineM(x4, y4, x1, y1);
}
void unSquareM(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    unLineM(x1, y1, x2, y2);
    unLineM(x2, y2, x3, y3);
    unLineM(x3, y3, x4, y4);
    unLineM(x4, y4, x1, y1);
}

void TriangleM(int x1, int y1, int x2, int y2, int x3, int y3){
  LineM(x1, y1, x2, y2);
  LineM(x2, y2, x3, y3);
  LineM(x3, y3, x1, y1);
}
void unTriangleM(int x1, int y1, int x2, int y2, int x3, int y3){
    unLineM(x1, y1, x2, y2);
    unLineM(x2, y2, x3, y3);
    unLineM(x3, y3, x1, y1);
}

void CilcleM(int x1, int y1, int r){
  int p = (6.3 * r);
  for (int i = 0; i <= p; i++) {
    int x = x1 + r * cos(i * 2 * 3.1416 / p);
    int y = y1 + r * sin(i * 2 * 3.1416 / p);
      dot[y][x] = 1;
  }
}
void unCilcleM(int x1, int y1, int r){
    int p = (6.3 * r);
    for (int i = 0; i <= p; i++) {
        int x = x1 + r * cos(i * 2 * 3.1416 / p);
        int y = y1 + r * sin(i * 2 * 3.1416 / p);
        dot[y][x] = 0;
    }
}

void PaintM(char fname[]){
    FILE *fp;
    char path[] = "../data/";
    
    fp = fopen(strcat(path, fname), "r");
    if(fp == NULL) {
        printf("%s file not open!\n", fname);
    }
    
    int elements = 0;//number of elements
    
    fscanf(fp,"%d",&elements);
    fscanf(fp,"%d",&elements);
    
    int arr[elements][3];
    for (int i = 0; i < elements; ++i) {
        fscanf(fp,"%d %d %d",&arr[i][0],&arr[i][1],&arr[i][2]);
    }
        for (int i = 0; i < elements; ++i) {
            for (int g = arr[i][0]; g <= arr[i][1]; g++){
                dot[255-arr[i][2]][g] = 1;
            }
        }
    
    fclose(fp);
}

void PaintxyM(char fname[], int x, int y) {
    FILE *fp;
    char path[] = "../data/";
    
    fp = fopen(strcat(path, fname), "r");
    if (fp == NULL) {
        printf("%s file not open!\n", fname);
    }
    
    int elements = 0;  // number of elements
    
    fscanf(fp, "%d", &elements);
    fscanf(fp, "%d", &elements);
    
    int arr[elements][3];
    for (int i = 0; i < elements; ++i) {
        fscanf(fp, "%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
    }
   
    for (int i = 0; i < elements; ++i) {
        for (int g = arr[i][0]; g <= arr[i][1]; g++) {
            dot[255-(y - arr[i][2])][g + x] = 1;
        }
    }
    
    fclose(fp);
}

void Reflesh(int x1,int y1,int x2,int y2){
    for(int y = y1;y >= y2;y-=1){
        for(int x = x1;x <= x2;x++){
            dot[y][x] = 0;
        }
    }
    
}
void unReflesh(int x1,int y1,int x2,int y2){
    for(int y = y1;y >= y2;y-=1){
        for(int x = x1;x <= x2;x++){
            dot[y][x] = 1;
        }
    }
    
}
