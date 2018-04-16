//=====================================================================//
//                                                                     //
//  �ե�����̾ : ImageFilter.h                                         //
//  ��      �� : PPM(Portable PixMap) �ޤ��� PGM(Portable GrayMap)���� //
//               �Υǡ����������������ؿ������                      //
//  ��  ��  �� : 2004. 2. 14 ��¼ ���� (Computer Graphics Lab.)        //
//               2013. 9. 5 ���� �� (Computer Vision Lab.)             //
//                                                                     //
//=====================================================================//
#ifndef _IMAGEFILTER_H_
#define _IMAGEFILTER_H_

//---------------------------------------------------------------------//
// �㣱��                                                              //
// void  NegativeImage(void)                                           //
//  ��      �� : PPM���������ϥǡ�����ͥ��������Ѵ�                   //
//  ��  ��  �� : 2004. 2. 11 ��¼ ���� (Computer Graphics Lab.)        //
//               2013. 9. 5 ���� �� (Computer Vision Lab.)             //
//---------------------------------------------------------------------//
void NegativeImage(void);

//---------------------------------------------------------------------//
// void  GrayscaleImage(void)                                          //
//  ��      �� : ���顼�����򥰥쥤��������������Ѵ�����              //
//---------------------------------------------------------------------//
void GrayscaleImage(void);

//---------------------------------------------------------------------//
// �㣲��                                                              //
// void DrawLines(void)                                                //
//  ��      �� : PGM���������ϥǡ�����������������                     //
//  ��  ��  �� : 2004. 2. 12 ��¼ ���� (Computer Graphics Lab.)        //
//               2013. 9. 5 ���� �� (Computer Vision Lab.)             //
//---------------------------------------------------------------------//
void DrawLines(int iWidth, int iHeight, int lineX, int lineY, int iWidthTemplate, int iHeightTemplate);
void BrightnessHistogram(void);
void BlackWhiteImage(void);
void neighborPix(void);
void neighborPix3D(void);
void EdgeDetection(void);
void EdgeDetectionSobel(void);
void templateMatching(void);
void smoothing(void);
void bilateralFiltering(void);

#endif
