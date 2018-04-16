//=====================================================================//
//                                                                     //
//  �ե�����̾ : ImageFilter.c                                         //
//  ��      �� : PPM(Portable PixMap) �ޤ��� PGM(Portable GrayMap)���� //
//               �Υǡ����������������ؿ������                      //
//  ��  ��  �� : 2004. 2. 14 ��¼ ���� (Computer Graphics Lab.)        //
//               2013. 9. 5 ���� �� (Computer Vision Lab.)             //
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
// �㣱��                                                              //
// void  NegativeImage(void)                                           //
//  ��      �� : PPM���������ϥǡ�����ͥ��������Ѵ�                   //
//  ��  ��  �� : 2004. 2. 11 ��¼ ���� (Computer Graphics Lab.)        //
//               2013. 9. 5 ���� �� (Computer Vision Lab.)             //
//---------------------------------------------------------------------//
void NegativeImage(void) {

    int iWidth, iHeight, iMaxValue;   // �����������⤵��������
    struct RGB * pRGBInputData;       // ���ϥǡ������Ǽ
    struct RGB * pRGBOutputData;      // �������������ǡ������Ǽ
    int i;                            // �롼�ץ�����

    // �ͥ�����
    printf("\n**** Negative Image *****\n");

    // PPM���������ϥǡ������ɤ߹���
    pRGBInputData = ReadPpm(&iWidth, &iHeight, &iMaxValue);
    
    // ���ϥǡ����ʣ������ˤΥ����ΰ�γ���
    // pRGBOutputData[iWidth*iHeight]
    pRGBOutputData = (struct RGB *)malloc(iWidth*iHeight*sizeof(struct RGB));

    // ���ϥǡ���(pRGBInputmData)��RGB���ͤ�ȿž���ơ�
    // ���ϥǡ���(pRGBOutputData)����¸
    for(i = 0; i < iWidth*iHeight; i++){
      pRGBOutputData[i].iRed   = iMaxValue - pRGBInputData[i].iRed;
      pRGBOutputData[i].iGreen = iMaxValue - pRGBInputData[i].iGreen;
      pRGBOutputData[i].iBlue  = iMaxValue - pRGBInputData[i].iBlue;
    }

    // ���ϥǡ�������¸���Ƥ�������ΰ�����
    FreePpm(pRGBInputData);

    // PPM�����Υե�����˽��ϥǡ��������
    WritePpm(pRGBOutputData, iWidth, iHeight, iMaxValue);

    // ���ϥǡ�������¸���Ƥ�������ΰ�����
    FreePpm(pRGBOutputData);
}

//---------------------------------------------------------------------//
// void  GrayscaleImage(void)                                          //
//  ��      �� : ���顼�����򥰥쥤��������������Ѵ�����              //
//---------------------------------------------------------------------//
void GrayscaleImage(void) {

    int iWidth = 0, iHeight = 0, iMaxValue = 0; // �����������⤵��������
    struct RGB *pRGBInputData = NULL; // ���ϥǡ������Ǽ
    int *piOutputData = NULL;         // �������������ǡ������Ǽ
    int i = 0;                        // �롼�ץ�����

    // 2�Ͳ����ϤΥ�å�������ɽ��
    printf("\n**** Start BinarizeImage() *****\n");

    // PPM���������ϥǡ������ɤ߹���
    pRGBInputData = ReadPpm(&iWidth, &iHeight, &iMaxValue);

    // ���ϥǡ����ʣ������ˤΥ����ΰ�γ���
    // piOutputData[iWidth*iHeight]
    piOutputData = (int *)malloc(iWidth * iHeight * sizeof(int));

    // ���ϥǡ���(pRGBInputData)�ο��򥰥쥤����������Ѵ�����
    // ���ϥǡ���(piOutputData)����¸
    for(i = 0; i < iWidth * iHeight; i++){
    // RGBɽ���Ϥ�YIQɽ���Ϥ��ѹ�����
    // ����ǡ�����YIQɽ���Ϥ�Y�ͤ���롣
        piOutputData[i] = 
            0.299 * pRGBInputData[i].iRed +
            0.587 * pRGBInputData[i].iGreen +
            0.114 * pRGBInputData[i].iBlue;
    }

    // ���ϥǡ�������¸���Ƥ�������ΰ�����
    FreePpm(pRGBInputData);

    // PPM�����Υե�����˽��ϥǡ��������
    WritePgm(piOutputData, iWidth, iHeight, iMaxValue);

    // ���ϥǡ�������¸���Ƥ�������ΰ�����
    FreePgm(piOutputData);
}


//---------------------------------------------------------------------//
// ��2��                                                              //
// void DrawLines(void)                                                //
//  ��      �� : PGM�����Υǡ�����������������                         //
//  ��  ��  �� : 2004. 2. 12 ��¼ ���� (Computer Graphics Lab.)        //
//               2013. 9. 5 ���� �� (Computer Vision Lab.)             //
//---------------------------------------------------------------------//
void DrawLines(int iWidth, int iHeight, int lineX, int lineY, int iWidthTemplate, int iHeightTemplate) {
    int iMaxValue;     // �����������⤵��������
    int * piOutputData;                 // �������������ǡ������Ǽ
    int iIndex;                         // ����ǥå���
    //int w, h, x, y;                   // ��ɸ�롼�ץ�����
    int iStartX, iStartY, iEndX, iEndY; // ľ���λ����Ƚ�����ɸ��
    int iWHITE;                         // �����
    // ��������
    printf("\n**** Draw Lines *****\n");

    // �����������⤵�������٤λ�����������
    iMaxValue = 255;
    iWHITE = iMaxValue;
    // ���ϥǡ����ʣ������ˤΥ����ΰ�γ���
    // piOutputData[iWidth*iHeight]
    piOutputData = (int *)malloc(iWidth*iHeight*sizeof(int));
    // ���Ǥ���ǽ����
    for(iIndex = 0; iIndex < iWidth*iHeight; iIndex++)
	   piOutputData[iIndex] = iWHITE;
    // ���ϥǡ���(piOutputData)����������
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
    // PGM�����Υե�����˽��ϥǡ��������
    WritePgm(piOutputData, iWidth, iHeight, iMaxValue);

    // ���ϥǡ�������¸���Ƥ�������ΰ�����
    FreePgm(piOutputData);
}



void BrightnessHistogram(void){
    int Brightness[256] = {0};
    int iWidth, iHeight, iMaxValue;   // �����������⤵��������
    int *piInputData = NULL;         // �������������ǡ������Ǽ
    
    printf("\n**** Start BrightnessHistogram() *****\n");
    
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);  //ǻø�������ɤ߹���

    for(int i = 0; i < iWidth * iHeight; i++){  
        Brightness[piInputData[i]]++;
        //�������ʤ��顢���٤�������ֹ�Ȥ�������Τ��ο��򣱤�ä���
    }
    

    FILE *pFile;  // �ե������ݥ��󥿡����������
    if((pFile=fopen("data.txt","w"))==NULL) { 
        // �ե�����������������뤫�ɤ������ǧ����
        printf("File cannot be opened/n");  
    }
    for(int j = 0; j < 256; j++){
        // ����Υǡ�����ե�����˽񤭹���
        fprintf(pFile,"%d %d\n", j, Brightness[j]); 
    }
    fflush(pFile);  // ����å����񤭹���
    fclose(pFile);  // �ե�����ݥ��󥿡����������
    FreePgm(piInputData);  // �����Υ����ΰ���������
}

void BlackWhiteImage(void){
    int iWidth, iHeight, iMaxValue;   // �����������⤵��������
    int *piInputData = NULL;         // �������������ǡ������Ǽ
    
    printf("\n**** Start BlackWhiteImage() *****\n");

    // ǻø�������ɤ߹���
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);

    // ���Ǥ��������ʤ��顢�⤷���ͤ�Ķ������255�ˤʤäơ��ʤ���0�ˤʤ�
    for(int i = 0; i < iWidth*iHeight; i++){
        if (piInputData[i] > 105){
            piInputData[i] = 255;
        }else{
            piInputData[i] = 0;
        }
    }

    // �����Υǡ�����ե�����˽񤭹���
    WritePgm(piInputData, iWidth, iHeight, iMaxValue);

    // �����Υ����ΰ���������
    FreePgm(piInputData);
}

void neighborPix(void){
    int iWidth, iHeight, iMaxValue;   // �����������⤵��������
    int *piInputData = NULL;         // ǻø�����Υǡ������Ǽ
    
    printf("\n**** Start neighBorPix() *****\n");
    // �����Υǡ������ɤ߹���
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    int* x=NULL;  // Υ���ͤ�����x��
    int* y=NULL;  // Υ���ͤ�����y��
    // ��Ǽ�����������
    x = (int*)malloc(sizeof(int)*iWidth*(iHeight-1));
    y = (int*)malloc(sizeof(int)*iWidth*(iHeight-1));
    // ���٤Ƥβ��Ǥ��������ơ�x��y����˥ǡ�������������
    for (int i = 0; i < iWidth*(iHeight-1); i++)
    {
        x[i] = piInputData[i];
        y[i] = piInputData[i+iWidth];
    }
    // ���ϥե�����򳫤�
    FILE *pFile;
    if((pFile=fopen("neighborPix.txt","w"))==NULL) {  
        printf("File cannot be opened/n");  
    }
    // x��y����Υǡ�����ե�����˽��Ϥ���
    for(int j = 0; j < iWidth*(iHeight-1); j++){
        fprintf(pFile,"%d %d\n", x[j], y[j]); 
    }
    fflush(pFile); 
    fclose(pFile);
    // �����ΰ���������
    FreePgm(piInputData);
    free(x);
    free(y);
}

void neighborPix3D(void){
    int iWidth, iHeight, iMaxValue;   // �����������⤵��������
    int *piInputData = NULL;         // ǻø�����Υǡ������Ǽ
    
    printf("\n**** Start neighBorPix3D() *****\n");
    // �����Υǡ������ɤ߹���
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    int* x=NULL;  // Υ���ͤ�����x��
    int* y=NULL;  // Υ���ͤ�����y��
    int* z=NULL;  // Υ���ͤ�����z��
    // ��Ǽ�����������
    x = (int*)malloc(sizeof(int)*iWidth*(iHeight-2));
    y = (int*)malloc(sizeof(int)*iWidth*(iHeight-2));
    z = (int*)malloc(sizeof(int)*iWidth*(iHeight-2));
    // ���٤Ƥβ��Ǥ��������ơ�x��y��z����˥ǡ�������������
    for (int i = 0; i < iWidth*(iHeight-2); i++)
    {
        x[i] = piInputData[i];
        y[i] = piInputData[i+iWidth];
        z[i] = piInputData[i+iWidth*2];
    }
    // ���ϥե�����򳫤�
    FILE *pFile;
    if((pFile=fopen("neighborPix3D.txt","w"))==NULL) {  
        printf("File cannot be opened/n");  
    }
    // x��y��z����Υǡ�����ե�����˽��Ϥ���
    for(int j = 0; j < iWidth*(iHeight-2); j++){
        fprintf(pFile,"%d %d %d\n", x[j], y[j], z[j]); 
    }
    fflush(pFile); 
    fclose(pFile);
    // �����ΰ���������
    FreePgm(piInputData);
    free(x);
    free(y);
    free(z);
}

void EdgeDetection(void){
    int iWidth, iHeight, iMaxValue;   // �����������⤵��������
    int *piInputData = NULL;  // ���ϥǡ������Ǽ
    int *piOutputData = NULL;  // �������������ǡ������Ǽ
    int j, x, y, max=0;

    printf("\n**** Start EdgeDetection() *****\n");
    // �����Υǡ������ɤ߹���
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    // ���ϥǡ����ʣ������ˤΥ����ΰ�γ���
    piOutputData = (int*)malloc(sizeof(int)*(iWidth-2)*(iHeight-2));
    // �������������ơ���ʬ��׻�����
    for(int i = 0; i < (iWidth-2)*(iHeight-2); i++){
        // �ե��륿���濴������˥ޥåԥ󥰤���
        j = iWidth + 1 + (i/(iWidth-2))*2 + i;
        // 3*3�ե��륿��Ȥä�����ʬ��׻�����
        x = -1 * piInputData[j-iWidth-1] + 1 * piInputData[j-iWidth+1]
            -2 * piInputData[j-1] + 2 * piInputData[j+1]
            -1 * piInputData[j+iWidth-1] + 1 * piInputData[j+iWidth+1];
        y = -1 * piInputData[j-iWidth-1] - 2 * piInputData[j-iWidth] - 1 * piInputData[j-iWidth+1]
            +1 * piInputData[j+iWidth-1] + 2 * piInputData[j+iWidth] + 1 * piInputData[j+iWidth+1];
        piOutputData[i] = (int)sqrt(x*x + y*y);  // ����ʬ���ͤ���ʬ��׻�����
        if(piOutputData[i] > max) max = piOutputData[i];  // ��ʬ�κ����ͤ�õ��
    }
    // 0����255���ϰϤǰ��̤���
    for(int i = 0; i < (iWidth-2)*(iHeight-2); i++){
        piOutputData[i] = (int)((piOutputData[i]/(double)max)*255);
        // printf("%d\n", piOutputData[i]);
    }
    printf("Here is the value of max: %d\n", max);
    // �����ΰ���������
    WritePgm(piOutputData, iWidth-2, iHeight-2, iMaxValue);
    FreePgm(piInputData);
    FreePgm(piOutputData);
}

void EdgeDetectionSobel(void){
    int iWidth, iHeight, iMaxValue;   // �����������⤵��������
    int *piInputData = NULL;
    int *piOutputData = NULL;// �������������ǡ������Ǽ
    int j, x, y, max=0;

    printf("\n**** Start EdgeDetectionSobel() *****\n");
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    piOutputData = (int*)malloc(sizeof(int)*(iWidth-4)*(iHeight-4));

    // �������������ơ���ʬ��׻�����
    for(int i = 0; i < (iWidth-4)*(iHeight-4); i++){
        // �ե��륿���濴������˥ޥåԥ󥰤���
        j = (iWidth*2 + 2) + i/(iWidth-4)*4 + i;
        // 5*5��Sobel�ե��륿��Ȥä�����ʬ��׻�����
        x = -2 * piInputData[j-1+iWidth*(-2)] -1 * piInputData[j-1+iWidth*(-2)] + 1 * piInputData[j+1+iWidth*(-2)] + 2 * piInputData[j+2+iWidth*(-2)]
            -4 * piInputData[j-2+iWidth*(-1)] -2 * piInputData[j-1+iWidth*(-1)] + 2 * piInputData[j+1+iWidth*(-1)] + 4 * piInputData[j+2+iWidth*(-1)]
            -8 * piInputData[j-4+iWidth*0] -4 * piInputData[j-1+iWidth*0] + 4 * piInputData[j+1+iWidth*0] + 8 * piInputData[j+2+iWidth*0]
            -4 * piInputData[j-2+iWidth*1] -2 * piInputData[j-1+iWidth*1] + 2 * piInputData[j+1+iWidth*1] + 4 * piInputData[j+2+iWidth*1]
            -2 * piInputData[j-1+iWidth*2] -1 * piInputData[j-1+iWidth*2] + 1 * piInputData[j+1+iWidth*2] + 2 * piInputData[j+2+iWidth*2];
        y = -2 * piInputData[j-2+iWidth*(-2)] -4 * piInputData[j-1+iWidth*(-2)] -8 * piInputData[j+iWidth*(-2)] -4 * piInputData[j+1+iWidth*(-2)] -2 * piInputData[j+2+iWidth*(-2)]
            -1 * piInputData[j-2+iWidth*(-1)] -2 * piInputData[j-1+iWidth*(-1)] -4 * piInputData[j+iWidth*(-1)] -2 * piInputData[j+1+iWidth*(-1)] -1 * piInputData[j+2+iWidth*(-1)]
            +1 * piInputData[j-2+iWidth*1] +2 * piInputData[j-1+iWidth*1] +4 * piInputData[j+iWidth*1] +2 * piInputData[j+1+iWidth*1] +1 * piInputData[j+2+iWidth*1]
            +2 * piInputData[j-2+iWidth*2] +4 * piInputData[j-1+iWidth*2] +8 * piInputData[j+iWidth*2] +4 * piInputData[j+1+iWidth*2] +2 * piInputData[j+2+iWidth*2];
        piOutputData[i] = (int)sqrt(x*x + y*y);  // ����ʬ���ͤ���ʬ��׻�����
        if(piOutputData[i] > max) max = piOutputData[i]; // ��ʬ�κ����ͤ�õ��
    }
    // 0����255���ϰϤǰ��̤���
    for(int i = 0; i < (iWidth-4)*(iHeight-4); i++){
        piOutputData[i] = (int)((piOutputData[i]/(double)max)*255);
    }
    printf("Here is the value of max: %d\n", max);
    // �����ΰ���������
    WritePgm(piOutputData, iWidth-4, iHeight-4, iMaxValue);
    FreePgm(piInputData);
    FreePgm(piOutputData);
}


//tools
long fromTwoPixesMatching(int* piInputData, int targetPixNum, int iWidth, int* piTemplateData, int iWidthTemplate, int iHeightTemplate){
    // SSD���ͤ�׻�����
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
    int iWidth, iHeight, iMaxValue;   // �����������⤵��������
    int *piInputData = NULL;         // �������åȲ����ǡ������Ǽ
    int iWidthTemplate, iHeightTemplate, iMaxValueTemplate;   // �����������⤵��������
    int *piTemplateData = NULL;         // �ƥ�ץ졼�Ȳ����ǡ������Ǽ
    long *piOutputData = NULL;  // �������������ǡ������Ǽ
    int min = INT_MAX;  // �Ǿ��ͤ�õ��
    int minPoint;  // �Ǿ��ͤ��ֹ��õ��

    printf("\n**** Start templateMatching() *****\n");
    printf("\nPlease input the Template:\n");
    piTemplateData = ReadPgm(&iWidthTemplate, &iHeightTemplate, &iMaxValueTemplate);
    // �ƥ�ץ졼�Ȳ������ɤ߹���
    printf("\nPlease input the target image:\n");
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    // �������åȲ������ɤ߹���
    int outputDataSize = (iWidth-(iWidthTemplate-1))*(iHeight-(iHeightTemplate-1));
    piOutputData = (long*)malloc(sizeof(long)*outputDataSize);
    // SSD��̤���¸����������ݤ���
    for(int i = 0; i < outputDataSize; i++){
        // ���夫�鱦���ޤǡ��ƹԳ������Ӥ���
        piOutputData[i] = fromTwoPixesMatching(piInputData, 
                i + (i/(iWidth-(iWidthTemplate-1)))*(iWidthTemplate-1), 
                iWidth, 
                piTemplateData, 
                iWidthTemplate, 
                iHeightTemplate);
        // printf("%ld\n", piOutputData[i]);
        if(min > piOutputData[i]){  // �Ǿ��ͤ�õ��
            min = piOutputData[i];
            minPoint = i;
        }
    }

    int lineX, lineY;
    lineX = minPoint%(iWidth-iWidthTemplate+1);
    lineY = minPoint/(iWidth-iWidthTemplate+1);
    printf("The X coordinate is: %d\n", minPoint%(iWidth-iWidthTemplate+1));
    printf("The Y coordinate is: %d\n", minPoint/(iWidth-iWidthTemplate+1));
    // ����������
    DrawStraightLine(piInputData, iWidth, iHeight, iMaxValue, lineX, lineY, lineX+iWidthTemplate, lineY, SOLID, WHITELINE);
    DrawStraightLine(piInputData, iWidth, iHeight, iMaxValue, lineX, lineY, lineX, lineY+iHeightTemplate, SOLID, WHITELINE);
    DrawStraightLine(piInputData, iWidth, iHeight, iMaxValue, lineX, lineY+iHeightTemplate, lineX+iWidthTemplate, lineY+iHeightTemplate, SOLID, WHITELINE);
    DrawStraightLine(piInputData, iWidth, iHeight, iMaxValue, lineX+iWidthTemplate, lineY, lineX+iWidthTemplate, lineY+iHeightTemplate, SOLID, WHITELINE);
    // �ܥå�����񤤤�������񤭹���
    WritePgm(piInputData, iWidth, iHeight, iMaxValue);  // ����������̤�׻�����
    FreePgm(piInputData);  // ������������
    FreePgm(piTemplateData);  // ������������
    free(piOutputData);  // ������������
}


double calVariance(int* piInputData, int j, int iWidth, int* position, int num){
    // ʬ����׻�����
    double aver=0, var=0, diff; // �����
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
    int iWidth = 0, iHeight = 0, iMaxValue = 0; // �����������⤵��������
    int *piInputData = NULL;         // �������åȲ����ǡ������Ǽ
    int *piOutputData = NULL;         // �������������ǡ������Ǽ
    double variance[9];    // ʬ������¸����
    int position[9][18];    // �ɽ��ΰ�����а��֤���¸����
    int j;

    // ���ࡼ���󥰳��ϤΥ�å�������ɽ��
    printf("\n**** Start smoothing() *****\n");

    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue); // �������ɤ߹���
    int outputDataSize = (iWidth-(5-1))*(iHeight-(5-1));
    piOutputData = (int*)malloc(sizeof(int)*outputDataSize); // ���ϲ����Υ������¸
    for(int i = 0; i < outputDataSize; i++){  
        // �ե��륿���濴������˥ޥåԥ󥰤���
        j = (iWidth*2 + 2) + i/(iWidth-4)*4 + i;  // �ե��륿���濴������˥ޥåԥ󥰤���

        // ���줫��Ϥ��줾�죹�ɽ��ʬ����׻�����
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

        int minPoint; // ʬ���ͤκǾ��ͤ��ֹ�
        double min=INT_MAX;
        // �Ǿ��ͤ�õ��
        for(int k=0; k<9; k++){
            if(variance[k]<min){
                min = variance[k];
                minPoint = k;
            }
        }

        if(minPoint==4){  // ����������̽�������
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
    // ������������
    FreePgm(piInputData);
    FreePgm(piOutputData);
}


// �������ǥ������󥹤�׻�����
double gaussian(float x, double sigma) {
    return exp(-(pow(x, 2))/(2 * pow(sigma, 2))) / (2 * pi * pow(sigma, 2));

}
void bilateralFiltering(void){
    int iWidth = 0, iHeight = 0, iMaxValue = 0; // �����������⤵��������
    int *piInputData = NULL;         // �������åȲ����ǡ������Ǽ
    int *piOutputData = NULL;         // �������������ǡ������Ǽ
    double sigmaI = 12;  // �������ǥ������󥹷���
    double sigmaS = 16;  // �������ǥ������󥹷���
    double filterSum, wP;
    int mapping;

    // ���ࡼ���󥰳��ϤΥ�å�������ɽ��
    printf("\n**** Start to use bilateral filter() *****\n");
    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);  // �������ɤ߹���
    int outputDataSize = (iWidth-(5-1))*(iHeight-(5-1));
    piOutputData = (int*)malloc(sizeof(int)*outputDataSize); // �������ɤ߹���
    // �������������ơ��ե�������η�̤�׻�����
    for(int i = 0; i < outputDataSize; i++){
        // �ե��륿���濴������˥ޥåԥ󥰤���
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
    WritePgm(piOutputData, iWidth-4, iHeight-4, iMaxValue);  // ��������������񤭹���
    // ������������
    FreePgm(piInputData);
    free(piOutputData);
}
