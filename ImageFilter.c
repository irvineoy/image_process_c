//=====================================================================//
//                                                                     //
//  ファイル名 : ImageFilter.c                                         //
//  内      容 : PPM(Portable PixMap) または PGM(Portable GrayMap)形式 //
//               のデータを画像処理する関数の定義                      //
//  更  新  日 : 2004. 2. 14 木村 彰徳 (Computer Graphics Lab.)        //
//               2013. 9. 5 脇田 航 (Computer Vision Lab.)             //
//                                                                     //
//=====================================================================//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include<limits.h>

#include "ImageFilter.h"

#include "ImageFileIO.h"
#include "ImageTools.h"

#define pi 3.14159
//---------------------------------------------------------------------//
// 例１）                                                              //
// void  NegativeImage(void)                                           //
//  内      容 : PPM形式の入力データをネガ画像に変換                   //
//  更  新  日 : 2004. 2. 11 木村 彰徳 (Computer Graphics Lab.)        //
//               2013. 9. 5 脇田 航 (Computer Vision Lab.)             //
//---------------------------------------------------------------------//
void NegativeImage(void) {

    int iWidth, iHeight, iMaxValue;   // 画像の幅，高さ，解像度
    struct RGB * pRGBInputData;       // 入力データを格納
    struct RGB * pRGBOutputData;      // 画像処理したデータを格納
    int i;                            // ループカウンタ

    // ネガ画像
    printf("\n**** Negative Image *****\n");

    // PPM形式の入力データの読み込み
    pRGBInputData = ReadPpm(&iWidth, &iHeight, &iMaxValue);
    
    // 出力データ（１次元）のメモリ領域の確保
    // pRGBOutputData[iWidth*iHeight]
    pRGBOutputData = (struct RGB *)malloc(iWidth*iHeight*sizeof(struct RGB));

    // 入力データ(pRGBInputmData)のRGBの値を反転して，
    // 出力データ(pRGBOutputData)に保存
    for(i = 0; i < iWidth*iHeight; i++){
      pRGBOutputData[i].iRed   = iMaxValue - pRGBInputData[i].iRed;
      pRGBOutputData[i].iGreen = iMaxValue - pRGBInputData[i].iGreen;
      pRGBOutputData[i].iBlue  = iMaxValue - pRGBInputData[i].iBlue;
    }

    // 入力データを保存しているメモリ領域を解放
    FreePpm(pRGBInputData);

    // PPM形式のファイルに出力データを出力
    WritePpm(pRGBOutputData, iWidth, iHeight, iMaxValue);

    // 出力データを保存しているメモリ領域を解放
    FreePpm(pRGBOutputData);
}

//---------------------------------------------------------------------//
// void  GrayscaleImage(void)                                          //
//  内      容 : カラー画像をグレイスケール画像に変換する              //
//---------------------------------------------------------------------//
void GrayscaleImage(void) {

    int iWidth = 0, iHeight = 0, iMaxValue = 0; // 画像の幅，高さ，解像度
    struct RGB *pRGBInputData = NULL; // 入力データを格納
    int *piOutputData = NULL;         // 画像処理したデータを格納
    int i = 0;                        // ループカウンタ

    // 2値化開始のメッセージを表示
    printf("\n**** Start BinarizeImage() *****\n");

    // PPM形式の入力データの読み込み
    pRGBInputData = ReadPpm(&iWidth, &iHeight, &iMaxValue);

    // 出力データ（１次元）のメモリ領域の確保
    // piOutputData[iWidth*iHeight]
    piOutputData = (int *)malloc(iWidth * iHeight * sizeof(int));

    // 入力データ(pRGBInputData)の色をグレイスケールに変換して
    // 出力データ(piOutputData)に保存
    for(i = 0; i < iWidth * iHeight; i++){
    // RGB表色系をYIQ表色系を変更する
    // これで、ただYIQ表色系のY値を求める。
        piOutputData[i] = 
            0.299 * pRGBInputData[i].iRed +
            0.587 * pRGBInputData[i].iGreen +
            0.114 * pRGBInputData[i].iBlue;
    }

    // 入力データを保存しているメモリ領域を解放
    FreePpm(pRGBInputData);

    // PPM形式のファイルに出力データを出力
    WritePgm(piOutputData, iWidth, iHeight, iMaxValue);

    // 出力データを保存しているメモリ領域を解放
    FreePgm(piOutputData);
}


//---------------------------------------------------------------------//
// 例2）                                                              //
// void DrawLines(void)                                                //
//  内      容 : PGM形式のデータに線を描く　　                         //
//  更  新  日 : 2004. 2. 12 木村 彰徳 (Computer Graphics Lab.)        //
//               2013. 9. 5 脇田 航 (Computer Vision Lab.)             //
//---------------------------------------------------------------------//
void DrawLines(int iWidth, int iHeight, int lineX, int lineY, int iWidthTemplate, int iHeightTemplate) {
    int iMaxValue;     // 画像の幅，高さ，解像度
    int * piOutputData;                 // 画像処理したデータを格納
    int iIndex;                         // インデックス
    //int w, h, x, y;                   // 座標ループカウンタ
    int iStartX, iStartY, iEndX, iEndY; // 直線の始点と終点座標　
    int iWHITE;                         // 白の値
    // 線を描く
    printf("\n**** Draw Lines *****\n");

    // 画像の幅，高さ，解像度の指定と白の設定
    iMaxValue = 255;
    iWHITE = iMaxValue;
    // 出力データ（１次元）のメモリ領域の確保
    // piOutputData[iWidth*iHeight]
    piOutputData = (int *)malloc(iWidth*iHeight*sizeof(int));
    // 画素を白で初期化
    for(iIndex = 0; iIndex < iWidth*iHeight; iIndex++)
	   piOutputData[iIndex] = iWHITE;
    // 出力データ(piOutputData)に線を描く
    iStartX = lineX; 
    iStartY = lineY;
    iEndY = iHeight;
    for(iEndX = iWidth - 1; iEndX >= 0; iEndX-=5) {
	DrawStraightLine(piOutputData, iWidth, iHeight, iMaxValue,
			 iStartX, iStartY, iEndX, iEndY, SOLID, BLACKLINE);
    }
    iEndX = iWidth;
    for(iEndY = iHeight - 1; iEndY >= 0; iEndY-=5) {
	DrawStraightLine(piOutputData, iWidth, iHeight, iMaxValue,
			 iStartX, iStartY, iEndX, iEndY, SOLID, BLACKLINE);
    }
    // PGM形式のファイルに出力データを出力
    WritePgm(piOutputData, iWidth, iHeight, iMaxValue);

    // 出力データを保存しているメモリ領域を解放
    FreePgm(piOutputData);
}



void BrightnessHistogram(void){
    int Brightness[256] = {0};
    int iWidth, iHeight, iMaxValue;   // 画像の幅，高さ，解像度
    int *piInputData = NULL;         // 画像処理したデータを格納
    
    printf("\n**** Start BrightnessHistogram() *****\n");
    
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);  //濃淡画像を読み込む

    for(int i = 0; i < iWidth * iHeight; i++){  
        Brightness[piInputData[i]]++;
        //走査しながら、輝度を配列の番号として配列のその数を１を加える
    }
    

    FILE *pFile;  // ファイルをポインターを定義する
    if((pFile=fopen("data.txt","w"))==NULL) { 
        // ファイルを正しく開けるかどうかを確認する
        printf("File cannot be opened/n");  
    }
    for(int j = 0; j < 256; j++){
        // 配列のデータをファイルに書き込む
        fprintf(pFile,"%d %d\n", j, Brightness[j]); 
    }
    fflush(pFile);  // キャッシュを書き込む
    fclose(pFile);  // ファイルポインターを解放する
    FreePgm(piInputData);  // 画像のメモリ領域を解放する
}

void BlackWhiteImage(void){
    int iWidth, iHeight, iMaxValue;   // 画像の幅，高さ，解像度
    int *piInputData = NULL;         // 画像処理したデータを格納
    
    printf("\n**** Start BlackWhiteImage() *****\n");

    // 濃淡画像を読み込む
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);

    // 画素を走査しながら、もし閾値を超えたら255になって、ないと0になる
    for(int i = 0; i < iWidth*iHeight; i++){
        if (piInputData[i] > 105){
            piInputData[i] = 255;
        }else{
            piInputData[i] = 0;
        }
    }

    // 画像のデータをファイルに書き込む
    WritePgm(piInputData, iWidth, iHeight, iMaxValue);

    // 画像のメモリ領域を解放する
    FreePgm(piInputData);
}

void neighborPix(void){
    int iWidth, iHeight, iMaxValue;   // 画像の幅，高さ，解像度
    int *piInputData = NULL;         // 濃淡画像のデータを格納
    
    printf("\n**** Start neighBorPix() *****\n");
    // 画像のデータを読み込む
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    int* x=NULL;  // 離散値の点のx軸
    int* y=NULL;  // 離散値の点のy軸
    // 格納メモリを申請する
    x = (int*)malloc(sizeof(int)*iWidth*(iHeight-1));
    y = (int*)malloc(sizeof(int)*iWidth*(iHeight-1));
    // すべての画素を走査して、xとy配列にデータを代入する
    for (int i = 0; i < iWidth*(iHeight-1); i++)
    {
        x[i] = piInputData[i];
        y[i] = piInputData[i+iWidth];
    }
    // 出力ファイルを開く
    FILE *pFile;
    if((pFile=fopen("neighborPix.txt","w"))==NULL) {  
        printf("File cannot be opened/n");  
    }
    // xとy配列のデータをファイルに出力する
    for(int j = 0; j < iWidth*(iHeight-1); j++){
        fprintf(pFile,"%d %d\n", x[j], y[j]); 
    }
    fflush(pFile); 
    fclose(pFile);
    // メモリ領域を解放する
    FreePgm(piInputData);
    free(x);
    free(y);
}

void neighborPix3D(void){
    int iWidth, iHeight, iMaxValue;   // 画像の幅，高さ，解像度
    int *piInputData = NULL;         // 濃淡画像のデータを格納
    
    printf("\n**** Start neighBorPix3D() *****\n");
    // 画像のデータを読み込む
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    int* x=NULL;  // 離散値の点のx軸
    int* y=NULL;  // 離散値の点のy軸
    int* z=NULL;  // 離散値の点のz軸
    // 格納メモリを申請する
    x = (int*)malloc(sizeof(int)*iWidth*(iHeight-2));
    y = (int*)malloc(sizeof(int)*iWidth*(iHeight-2));
    z = (int*)malloc(sizeof(int)*iWidth*(iHeight-2));
    // すべての画素を走査して、xとyとz配列にデータを代入する
    for (int i = 0; i < iWidth*(iHeight-2); i++)
    {
        x[i] = piInputData[i];
        y[i] = piInputData[i+iWidth];
        z[i] = piInputData[i+iWidth*2];
    }
    // 出力ファイルを開く
    FILE *pFile;
    if((pFile=fopen("neighborPix3D.txt","w"))==NULL) {  
        printf("File cannot be opened/n");  
    }
    // xとyとz配列のデータをファイルに出力する
    for(int j = 0; j < iWidth*(iHeight-2); j++){
        fprintf(pFile,"%d %d %d\n", x[j], y[j], z[j]); 
    }
    fflush(pFile); 
    fclose(pFile);
    // メモリ領域を解放する
    FreePgm(piInputData);
    free(x);
    free(y);
    free(z);
}

void EdgeDetection(void){
    int iWidth, iHeight, iMaxValue;   // 画像の幅，高さ，解像度
    int *piInputData = NULL;  // 入力データを格納
    int *piOutputData = NULL;  // 画像処理したデータを格納
    int j, x, y, max=0;

    printf("\n**** Start EdgeDetection() *****\n");
    // 画像のデータを読み込む
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    // 出力データ（１次元）のメモリ領域の確保
    piOutputData = (int*)malloc(sizeof(int)*(iWidth-2)*(iHeight-2));
    // 画像を走査して、微分を計算する
    for(int i = 0; i < (iWidth-2)*(iHeight-2); i++){
        // フィルタの中心を画像にマッピングする
        j = iWidth + 1 + (i/(iWidth-2))*2 + i;
        // 3*3フィルタを使って偏微分を計算する
        x = -1 * piInputData[j-iWidth-1] + 1 * piInputData[j-iWidth+1]
            -2 * piInputData[j-1] + 2 * piInputData[j+1]
            -1 * piInputData[j+iWidth-1] + 1 * piInputData[j+iWidth+1];
        y = -1 * piInputData[j-iWidth-1] - 2 * piInputData[j-iWidth] - 1 * piInputData[j-iWidth+1]
            +1 * piInputData[j+iWidth-1] + 2 * piInputData[j+iWidth] + 1 * piInputData[j+iWidth+1];
        piOutputData[i] = (int)sqrt(x*x + y*y);  // 偏微分の値で微分を計算する
        if(piOutputData[i] > max) max = piOutputData[i];  // 微分の最大値を探す
    }
    // 0から255の範囲で圧縮する
    for(int i = 0; i < (iWidth-2)*(iHeight-2); i++){
        piOutputData[i] = (int)((piOutputData[i]/(double)max)*255);
        // printf("%d\n", piOutputData[i]);
    }
    printf("Here is the value of max: %d\n", max);
    // メモリ領域を解放する
    WritePgm(piOutputData, iWidth-2, iHeight-2, iMaxValue);
    FreePgm(piInputData);
    FreePgm(piOutputData);
}

void EdgeDetectionSobel(void){
    int iWidth, iHeight, iMaxValue;   // 画像の幅，高さ，解像度
    int *piInputData = NULL;
    int *piOutputData = NULL;// 画像処理したデータを格納
    int j, x, y, max=0;

    printf("\n**** Start EdgeDetectionSobel() *****\n");
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    piOutputData = (int*)malloc(sizeof(int)*(iWidth-4)*(iHeight-4));

    // 画像を走査して、微分を計算する
    for(int i = 0; i < (iWidth-4)*(iHeight-4); i++){
        // フィルタの中心を画像にマッピングする
        j = (iWidth*2 + 2) + i/(iWidth-4)*4 + i;
        // 5*5のSobelフィルタを使って偏微分を計算する
        x = -2 * piInputData[j-1+iWidth*(-2)] -1 * piInputData[j-1+iWidth*(-2)] + 1 * piInputData[j+1+iWidth*(-2)] + 2 * piInputData[j+2+iWidth*(-2)]
            -4 * piInputData[j-2+iWidth*(-1)] -2 * piInputData[j-1+iWidth*(-1)] + 2 * piInputData[j+1+iWidth*(-1)] + 4 * piInputData[j+2+iWidth*(-1)]
            -8 * piInputData[j-4+iWidth*0] -4 * piInputData[j-1+iWidth*0] + 4 * piInputData[j+1+iWidth*0] + 8 * piInputData[j+2+iWidth*0]
            -4 * piInputData[j-2+iWidth*1] -2 * piInputData[j-1+iWidth*1] + 2 * piInputData[j+1+iWidth*1] + 4 * piInputData[j+2+iWidth*1]
            -2 * piInputData[j-1+iWidth*2] -1 * piInputData[j-1+iWidth*2] + 1 * piInputData[j+1+iWidth*2] + 2 * piInputData[j+2+iWidth*2];
        y = -2 * piInputData[j-2+iWidth*(-2)] -4 * piInputData[j-1+iWidth*(-2)] -8 * piInputData[j+iWidth*(-2)] -4 * piInputData[j+1+iWidth*(-2)] -2 * piInputData[j+2+iWidth*(-2)]
            -1 * piInputData[j-2+iWidth*(-1)] -2 * piInputData[j-1+iWidth*(-1)] -4 * piInputData[j+iWidth*(-1)] -2 * piInputData[j+1+iWidth*(-1)] -1 * piInputData[j+2+iWidth*(-1)]
            +1 * piInputData[j-2+iWidth*1] +2 * piInputData[j-1+iWidth*1] +4 * piInputData[j+iWidth*1] +2 * piInputData[j+1+iWidth*1] +1 * piInputData[j+2+iWidth*1]
            +2 * piInputData[j-2+iWidth*2] +4 * piInputData[j-1+iWidth*2] +8 * piInputData[j+iWidth*2] +4 * piInputData[j+1+iWidth*2] +2 * piInputData[j+2+iWidth*2];
        piOutputData[i] = (int)sqrt(x*x + y*y);  // 偏微分の値で微分を計算する
        if(piOutputData[i] > max) max = piOutputData[i]; // 微分の最大値を探す
    }
    // 0から255の範囲で圧縮する
    for(int i = 0; i < (iWidth-4)*(iHeight-4); i++){
        piOutputData[i] = (int)((piOutputData[i]/(double)max)*255);
    }
    printf("Here is the value of max: %d\n", max);
    // メモリ領域を解放する
    WritePgm(piOutputData, iWidth-4, iHeight-4, iMaxValue);
    FreePgm(piInputData);
    FreePgm(piOutputData);
}


//tools
long fromTwoPixesMatching(int* piInputData, int targetPixNum, int iWidth, int* piTemplateData, int iWidthTemplate, int iHeightTemplate){
    // SSDの値を計算する
    long sumValue = 0;
    for(int j = 0; j < iHeightTemplate; j++){
        for(int k = 0; k < iWidthTemplate; k++){
            int difference = (piTemplateData[j*iWidthTemplate + k] - piInputData[targetPixNum + j*iWidth + k]);
            sumValue += difference * difference;
        }
    }
    return sumValue;
}
void templateMatching(void){
    int iWidth, iHeight, iMaxValue;   // 画像の幅，高さ，解像度
    int *piInputData = NULL;         // ターゲット画像データを格納
    int iWidthTemplate, iHeightTemplate, iMaxValueTemplate;   // 画像の幅，高さ，解像度
    int *piTemplateData = NULL;         // テンプレート画像データを格納
    long *piOutputData = NULL;  // 画像処理したデータを格納
    int min = INT_MAX;  // 最小値を探す
    int minPoint;  // 最小値の番号を探す

    printf("\n**** Start templateMatching() *****\n");
    printf("\nPlease input the Template:\n");
    piTemplateData = ReadPgm(&iWidthTemplate, &iHeightTemplate, &iMaxValueTemplate);
    // テンプレート画像を読み込む
    printf("\nPlease input the target image:\n");
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    // ターゲット画像を読み込み
    int outputDataSize = (iWidth-(iWidthTemplate-1))*(iHeight-(iHeightTemplate-1));
    piOutputData = (long*)malloc(sizeof(long)*outputDataSize);
    // SSD結果を保存するメモリを確保する
    for(int i = 0; i < outputDataSize; i++){
        // 左上から右下まで、各行各列を比較する
        piOutputData[i] = fromTwoPixesMatching(piInputData, 
                i + (i/(iWidth-(iWidthTemplate-1)))*(iWidthTemplate-1), 
                iWidth, 
                piTemplateData, 
                iWidthTemplate, 
                iHeightTemplate);
        // printf("%ld\n", piOutputData[i]);
        if(min > piOutputData[i]){  // 最小値を探す
            min = piOutputData[i];
            minPoint = i;
        }
    }

    int lineX, lineY;
    lineX = minPoint%(iWidth-iWidthTemplate+1);
    lineY = minPoint/(iWidth-iWidthTemplate+1);
    printf("The X coordinate is: %d\n", minPoint%(iWidth-iWidthTemplate+1));
    printf("The Y coordinate is: %d\n", minPoint/(iWidth-iWidthTemplate+1));
    // 白い線を描く
    DrawStraightLine(piInputData, iWidth, iHeight, iMaxValue, lineX, lineY, lineX+iWidthTemplate, lineY, SOLID, WHITELINE);
    DrawStraightLine(piInputData, iWidth, iHeight, iMaxValue, lineX, lineY, lineX, lineY+iHeightTemplate, SOLID, WHITELINE);
    DrawStraightLine(piInputData, iWidth, iHeight, iMaxValue, lineX, lineY+iHeightTemplate, lineX+iWidthTemplate, lineY+iHeightTemplate, SOLID, WHITELINE);
    DrawStraightLine(piInputData, iWidth, iHeight, iMaxValue, lineX+iWidthTemplate, lineY, lineX+iWidthTemplate, lineY+iHeightTemplate, SOLID, WHITELINE);
    // ボックスを書いた画像を書き込む
    WritePgm(piInputData, iWidth, iHeight, iMaxValue);  // 処理した結果を計算する
    FreePgm(piInputData);  // メモリを解放する
    FreePgm(piTemplateData);  // メモリを解放する
    free(piOutputData);  // メモリを解放する
}


double calVariance(int* piInputData, int j, int iWidth, int* position, int num){
    // 分散を計算する
    double aver=0, var=0, diff; // 初期化
    for(int i=0; i<num; i++){
        aver += piInputData[j+position[i*2]*iWidth+position[i*2+1]];
    }
    aver = aver/num;
    for(int i=0; i<num; i++){
        diff = piInputData[j+position[i*2]*iWidth+position[i*2+1]]-aver;
        var += diff * diff;
    }
    var = var/num;
    return var;
}
void smoothing(void){
    int iWidth = 0, iHeight = 0, iMaxValue = 0; // 画像の幅，高さ，解像度
    int *piInputData = NULL;         // ターゲット画像データを格納
    int *piOutputData = NULL;         // 画像処理したデータを格納
    double variance[9];    // 分散を保存する
    int position[9][18];    // 局所領域の相対位置を保存する
    int j;

    // スムーシング開始のメッセージを表示
    printf("\n**** Start smoothing() *****\n");

    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue); // 画像を読み込む
    int outputDataSize = (iWidth-(5-1))*(iHeight-(5-1));
    piOutputData = (int*)malloc(sizeof(int)*outputDataSize); // 出力画像のメモリを保存
    for(int i = 0; i < outputDataSize; i++){  
        // フィルタの中心を画像にマッピングする
        j = (iWidth*2 + 2) + i/(iWidth-4)*4 + i;  // フィルタの中心を画像にマッピングする

        // これからはそれぞれ９局所の分散を計算する
        position[0][0] = -2; position[0][1] = -2; position[0][2] = -2; position[0][3] = -1; 
        position[0][4] = -1; position[0][5] = -2; position[0][6] = -1; position[0][7] = -1; 
        position[0][8] = -1; position[0][9] = 0; position[0][10] = 0; position[0][11] = -1;
        position[0][12] = 0; position[0][13] = 0;
        variance[0] = calVariance(piInputData, j, iWidth, position[0], 7);

        position[1][0] = -2; position[1][1] = -1; position[1][2] = -2; position[1][3] = 0; 
        position[1][4] = -2; position[1][5] = 1; position[1][6] = -1; position[1][7] = -1; 
        position[1][8] = -1; position[1][9] = 0; position[1][10] = -1; position[1][11] = 1;
        position[1][12] = 0; position[1][13] = 0;
        variance[1] = calVariance(piInputData, j, iWidth, position[1], 7);

        position[2][0] = -2; position[2][1] = 1; position[2][2] = -2; position[2][3] = 2; 
        position[2][4] = -1; position[2][5] = 0; position[2][6] = -1; position[2][7] = 1; 
        position[2][8] = -1; position[2][9] = 2; position[2][10] = 0; position[2][11] = 0;
        position[2][12] = 0; position[2][13] = 1;
        variance[2] = calVariance(piInputData, j, iWidth, position[2], 7);

        position[3][0] = -1; position[3][1] = -2; position[3][2] = -1; position[3][3] = -1; 
        position[3][4] = 0; position[3][5] = -2; position[3][6] = 0; position[3][7] = -1; 
        position[3][8] = 0; position[3][9] = 0; position[3][10] = 1; position[3][11] = -2;
        position[3][12] = 1; position[3][13] = -1;
        variance[3] = calVariance(piInputData, j, iWidth, position[3], 7);

        position[4][0] = -1; position[4][1] = -1; position[4][2] = -1; position[4][3] = 0; 
        position[4][4] = -1; position[4][5] = 1; position[4][6] = 0; position[4][7] = -1; 
        position[4][8] = 0; position[4][9] = 0; position[4][10] = 0; position[4][11] = 1;
        position[4][12] = 1; position[4][13] = -1; position[4][14] = 1; position[4][15] = 0;
        position[4][16] = 1; position[4][17] = 1;
        variance[4] = calVariance(piInputData, j, iWidth, position[4], 9);

        position[5][0] = 1; position[5][1] = 2; position[5][2] = 1; position[5][3] = 1; 
        position[5][4] = -0; position[5][5] = 2; position[5][6] = -0; position[5][7] = 1; 
        position[5][8] = -0; position[5][9] = -0; position[5][10] = -1; position[5][11] = 2;
        position[5][12] = -1; position[5][13] = 1;
        variance[5] = calVariance(piInputData, j, iWidth, position[5], 7);

        position[6][0] = 2; position[6][1] = -1; position[6][2] = 2; position[6][3] = -2; 
        position[6][4] = 1; position[6][5] = -0; position[6][6] = 1; position[6][7] = -1; 
        position[6][8] = 1; position[6][9] = -2; position[6][10] = -0; position[6][11] = -0;
        position[6][12] = -0; position[6][13] = -1;
        variance[6] = calVariance(piInputData, j, iWidth, position[6], 7);

        position[7][0] = 2; position[7][1] = 1; position[7][2] = 2; position[7][3] = -0; 
        position[7][4] = 2; position[7][5] = -1; position[7][6] = 1; position[7][7] = 1; 
        position[7][8] = 1; position[7][9] = -0; position[7][10] = 1; position[7][11] = -1;
        position[7][12] = -0; position[7][13] = -0;
        variance[7] = calVariance(piInputData, j, iWidth, position[7], 7);

        position[8][0] = 2; position[8][1] = 2; position[8][2] = 2; position[8][3] = 1; 
        position[8][4] = 1; position[8][5] = 2; position[8][6] = 1; position[8][7] = 1; 
        position[8][8] = 1; position[8][9] = -0; position[8][10] = -0; position[8][11] = 1;
        position[8][12] = -0; position[8][13] = -0;
        variance[8] = calVariance(piInputData, j, iWidth, position[8], 7);

        int minPoint; // 分散値の最小値の番号
        double min=INT_MAX;
        // 最小値を探す
        for(int k=0; k<9; k++){
            if(variance[k]<min){
                min = variance[k];
                minPoint = k;
            }
        }

        if(minPoint==4){  // 真ん中は特別処理する
            double pixValue = 0;
            for(int k=0; k<9; k++){
                pixValue += piInputData[j+position[4][k*2]*iWidth+position[4][k*2+1]];
            }
            pixValue = pixValue/9;
            piOutputData[i] = (int)pixValue;
        }
        else{
            double pixValue = 0;
            for(int k=0; k<7; k++){
                pixValue += piInputData[j+position[minPoint][k*2]*iWidth+position[minPoint][k*2+1]];
            }
            pixValue = pixValue/7;
            piOutputData[i] = (int)pixValue;
        }
    }

    WritePgm(piOutputData, iWidth-4, iHeight-4, iMaxValue);
    // メモリを解放する
    FreePgm(piInputData);
    FreePgm(piOutputData);
}


// ガウスディスタンスを計算する
double gaussian(float x, double sigma) {
    return exp(-(pow(x, 2))/(2 * pow(sigma, 2))) / (2 * pi * pow(sigma, 2));

}
void bilateralFiltering(void){
    int iWidth = 0, iHeight = 0, iMaxValue = 0; // 画像の幅，高さ，解像度
    int *piInputData = NULL;         // ターゲット画像データを格納
    int *piOutputData = NULL;         // 画像処理したデータを格納
    double sigmaI = 12;  // ガウスディスタンス係数
    double sigmaS = 16;  // ガウスディスタンス係数
    double filterSum, wP;
    int mapping;

    // スムーシング開始のメッセージを表示
    printf("\n**** Start to use bilateral filter() *****\n");
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);  // 画像を読み込む
    int outputDataSize = (iWidth-(5-1))*(iHeight-(5-1));
    piOutputData = (int*)malloc(sizeof(int)*outputDataSize); // 画像を読み込む
    // 画像を走査して、フィルダーの結果を計算する
    for(int i = 0; i < outputDataSize; i++){
        // フィルタの中心を画像にマッピングする
        mapping = (iWidth*2 + 2) + i/(iWidth-4)*4 + i;
        filterSum = 0;
        wP = 0;
        for(int j = -2; j <= 2; j++) {
            for(int k = -2; k <= 2; k++) {
                double gi = gaussian(piInputData[mapping]-piInputData[mapping+j+k*iWidth], sigmaI);
                double gs = gaussian(sqrt(j*j+k*k), sigmaS);
                double w = gi * gs;
                filterSum = filterSum + piInputData[mapping+j+k*iWidth] * w;
                wP = wP + w;
            }
        }
        filterSum = filterSum / wP;
        piOutputData[i] = (int)filterSum;
    }
    WritePgm(piOutputData, iWidth-4, iHeight-4, iMaxValue);  // 処理した画像を書き込む
    // メモリを解放する
    FreePgm(piInputData);
    free(piOutputData);
}
