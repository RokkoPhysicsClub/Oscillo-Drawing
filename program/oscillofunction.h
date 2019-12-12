#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wiringPi.h>

#define N 256

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
  delayMicroseconds(1);
}

void Line(int x1, int y1, int x2, int y2) {
  int distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
  for (int i = 0; i < distance; i++) {
    int x = x1 + (x2 - x1) * i / distance;
    int y = y1 + (y2 - y1) * i / distance;
    ochiX(x);
    ochiY(y);
  }
}

void vertical(int y1, int y2, int x) {
  ochiX(x);
  for (int g = y1; g <= y2; g++) {
    ochiY(g);
  }
}

void horizontal(int x1, int x2, int y) {
  ochiY(y);
  for (int g = x1; g <= x2; g++) {
    ochiX(g);
  }
}

void Square(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
  Line(x1, y1, x2, y2);
  Line(x2, y2, x3, y3);
  Line(x3, y3, x4, y4);
  Line(x4, y4, x1, y1);
}

void Triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
  Line(x1, y1, x2, y2);
  Line(x2, y2, x3, y3);
  Line(x3, y3, x1, y1);
}

void Cilcle(int x1, int y1, int r) {
  int dot = (6.3 * r);
  for (int i = 0; i <= dot; i++) {
    int x = x1 + r * cos(i * 2 * 3.1416 / dot);
    int y = y1 + r * sin(i * 2 * 3.1416 / dot);
    ochiX(x);
    ochiY(y);
  }
}

void Draw() {
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
      strcat(path, fname),
      "r");  
  if (fp == NULL) {
    printf("%s file not open!\n", fname);
  }

  int images = 0;  // number of images

  fscanf(fp, "%d", &images);

  // printf("%d\n",images);

  for (int i = 0; i < images; i++) {
    // loop for the number of image

    int elements = 0;  // number of elements

    clock_t start, end;
    start = clock();

    fscanf(fp, "%d", &elements);

    int arr[elements][3];

    for (int j = 0; j < elements; j++) {
      // loop for the number of elements
      fscanf(fp, "%d %d %d", &arr[j][0], &arr[j][1], &arr[j][2]);
      if (arr[j][2] != arr[j - 1][2]) {
        ochiY(255 - arr[j][2]);
      }
      for (int g = arr[j][0]; g <= arr[j][1]; g++) {
        ochiX(g);
      }
    }
    Point(i, 0);
    end = clock();
    int t = (int)(((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0);
    if (frameLength > t) {
      delayMicroseconds(frameLength - t);
    } else {
    }
  }
  fclose(fp);
}

void Drawf(char fname[], double frameRate) {
  FILE *fp;
  char str[N];

  int frameLength = 0;
  frameLength = (int)(1000000.0 / frameRate);
  char path[] = "../data/";

  fp = fopen(strcat(path, fname), "r");
  if (fp == NULL) {
    printf("%s file not open!\n", fname);
  }

  int images = 0;  // number of images

  fscanf(fp, "%d", &images);

  for (int i = 0; i < images - 20; i++) {
    // loop for the number of image

    int elements = 0;  // number of elements

    clock_t start, end;
    start = clock();

    fscanf(fp, "%d", &elements);

    int arr[elements][3];

    for (int j = 0; j < elements; j++) {
      // loop for the number of elements
      fscanf(fp, "%d %d %d", &arr[j][0], &arr[j][1], &arr[j][2]);
      if (arr[j][2] != arr[j - 1][2]) {
        ochiY(255 - arr[j][2]);
      }
      for (int g = arr[j][0]; g <= arr[j][1]; g++) {
        ochiX(g);
      }
    }
    Point(i, 0);
    end = clock();
    int t = (int)(((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0);
    if (frameLength > t) {
      delayMicroseconds(frameLength - t);
    } else {
    }
  }
  fclose(fp);
}

void Paint() {
  FILE *fp;  
  char fname[] = "";
  char str[N];

  printf("ファイル名:");
  scanf("%s", fname);

  char path[] = "../data/";

  fp = fopen(
      strcat(path, fname),"r");
  if (fp == NULL) {
    printf("%s file not open!\n", fname);
  }

  int image = 0;
  fscanf(fp, "%d", &image);

  int elements = 0;  // number of elements

  fscanf(fp, "%d", &elements);

  int arr[elements][3];
  for (int i = 0; i < elements; ++i) {
    fscanf(fp, "%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
  }
  int t = 0;
  clock_t start, end;
  start = clock();
  while (t < 100) {
    for (int i = 0; i < elements; ++i) {
      ochiY(255 - arr[i][2]);
      for (int g = arr[i][0]; g <= arr[i][1]; g++) {
        ochiX(g);
      }
    }
    end = clock();
    t = (int)(((double)(end - start) / CLOCKS_PER_SEC));
  }

  fclose(fp);
}

void Paintf(char fname[], int v) {
  FILE *fp;
  char path[] = "../data/";

  fp = fopen(strcat(path, fname), "r");
  if (fp == NULL) {
    printf("%s file not open!\n", fname);
  }

  int elements = 0;  // number of elements

  fscanf(fp, "%d", &elements);

  int arr[elements][3];
  for (int i = 0; i < elements; ++i) {
    fscanf(fp, "%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
  }
  int t = 0;
  clock_t start, end;
  start = clock();
  while (t < v) {
    for (int i = 0; i < elements; ++i) {
      ochiY(255 - arr[i][2]);
      for (int g = arr[i][0]; g <= arr[i][1]; g++) {
        ochiX(g);
        delayMicroseconds(1);
      }
    }
    end = clock();
    t = (int)(((double)(end - start) / CLOCKS_PER_SEC));
  }

  fclose(fp);
}

void Paint2(char fname[], int x, int y) {
  FILE *fp;
  char path[] = "../data/";

  fp = fopen(strcat(path, fname), "r");
  if (fp == NULL) {
    printf("%s file not open!\n", fname);
  }

  int elements = 0;  // number of elements

  fscanf(fp, "%d", &elements);

  int arr[elements][3];
  for (int i = 0; i < elements; ++i) {
    fscanf(fp, "%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
  }
  int t = 0;
  clock_t start, end;
  start = clock();

  for (int i = 0; i < elements; ++i) {
    ochiY(255 - (y - arr[i][2]));
    for (int g = arr[i][0]; g <= arr[i][1]; g++) {
      ochiX(g + x);
      delayMicroseconds(1);
    }
  }
  end = clock();
  t = (int)(((double)(end - start) / CLOCKS_PER_SEC));

  fclose(fp);
}