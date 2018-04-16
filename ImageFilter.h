//=====================================================================//
//                                                                     //
//  ファイル名 : ImageFilter.h                                         //
//  内      容 : PPM(Portable PixMap) または PGM(Portable GrayMap)形式 //
//               のデータを画像処理する関数の定義                      //
//  更  新  日 : 2004. 2. 14 木村 彰徳 (Computer Graphics Lab.)        //
//               2013. 9. 5 脇田 航 (Computer Vision Lab.)             //
//                                                                     //
//=====================================================================//
#ifndef _IMAGEFILTER_H_
#define _IMAGEFILTER_H_

//---------------------------------------------------------------------//
// 例１）                                                              //
// void  NegativeImage(void)                                           //
//  内      容 : PPM形式の入力データをネガ画像に変換                   //
//  更  新  日 : 2004. 2. 11 木村 彰徳 (Computer Graphics Lab.)        //
//               2013. 9. 5 脇田 航 (Computer Vision Lab.)             //
//---------------------------------------------------------------------//
void NegativeImage(void);

//---------------------------------------------------------------------//
// void  GrayscaleImage(void)                                          //
//  内      容 : カラー画像をグレイスケール画像に変換する              //
//---------------------------------------------------------------------//
void GrayscaleImage(void);

//---------------------------------------------------------------------//
// 例２）                                                              //
// void DrawLines(void)                                                //
//  内      容 : PGM形式の入力データに線を描く　　                     //
//  更  新  日 : 2004. 2. 12 木村 彰徳 (Computer Graphics Lab.)        //
//               2013. 9. 5 脇田 航 (Computer Vision Lab.)             //
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
