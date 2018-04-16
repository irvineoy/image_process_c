//=====================================================================//
//                                                                     //
//  ファイル名 : main.c                                                //
//  内      容 : 画像処理プログラムのメインプログラム                  //
//  更  新  日 : 2004. 2. 17 木村 彰徳 (Computer Graphics Lab.)        //
//               2013. 9. 5 脇田 航 (Computer Vision Lab.)             //
//                                                                     //
//=====================================================================//
#include <stdio.h>

#include "ImageFilter.h"

int main(void) {
  // 画像処理を行う関数の呼び出し
  // 例１）PPM形式の入力データをネガ画像に変換
	printf("\n======  Image Processing =====\n");
	printf("0: Negative Image\n");
  printf("1: Grayscale Image\n");
  printf("2: Brightness Histogram\n");
  printf("3: BlackWhiteImage\n");
  printf("4: neighborPix\n");
  printf("5: neighborPix3D\n");
  printf("6: EdgeDetection\n");
  printf("7: EdgeDetectionSobel\n");
  printf("8: templateMatching\n");
  printf("9: smoothing\n");
	printf("10: bilateralFiltering\n");
	int i;
    scanf("%d",&i);  
    if(i==0)NegativeImage();
    if(i==1)GrayscaleImage();
    if(i==2)BrightnessHistogram();
    if(i==3)BlackWhiteImage();
    if(i==4)neighborPix();
    if(i==5)neighborPix3D();
    if(i==6)EdgeDetection();
    if(i==7)EdgeDetectionSobel();
    if(i==8)templateMatching();
    if(i==9)smoothing();
	  if(i==10)bilateralFiltering();
  // 例２）PGM形式のデータに線を描く
  // DrawLines();

  // 正常終了
  return 0;
}
