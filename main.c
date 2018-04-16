//=====================================================================//
//                                                                     //
//  �ե�����̾ : main.c                                                //
//  ��      �� : ���������ץ����Υᥤ��ץ����                  //
//  ��  ��  �� : 2004. 2. 17 ��¼ ���� (Computer Graphics Lab.)        //
//               2013. 9. 5 ���� �� (Computer Vision Lab.)             //
//                                                                     //
//=====================================================================//
#include <stdio.h>

#include "ImageFilter.h"

int main(void) {
  // ����������Ԥ��ؿ��θƤӽФ�
  // �㣱��PPM���������ϥǡ�����ͥ��������Ѵ�
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
  // �㣲��PGM�����Υǡ�������������
  // DrawLines();

  // ���ｪλ
  return 0;
}
