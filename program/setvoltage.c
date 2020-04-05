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
printf("input X value(0-255)...");
scanf("%d", &value);
outX(value);
printf("input Y value(0-255)...");
scanf("%d", &value);
outY(value);
}
