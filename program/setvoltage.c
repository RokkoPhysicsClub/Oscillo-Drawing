#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#define BIT 8
void outX(int x){
	for(int i=0;i<=BIT-1;i++){
		digitalWrite(i,(x&1U));
		x=x>>1;
	}
}
void outY(int y){
        for(int i=0;i<=BIT-1;i++){
                digitalWrite(i+8, (x&1U));
                y=y>>1;
        }
}
void main(void){
int value;
printf("input X value(0-255)...");
scanf("%d", &value);
outX(value);
printf("input Y value(0-255)...");
scanf("%d", &value);
outY(value);
}
