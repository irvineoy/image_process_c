//=====================================================================//
//                                                                     //
//  �ե�����̾ : ImageFileIO.c                                         //
//  ��      �� : ppm (Portable PixMap), pgm (Portable GrayMap)�ե����� //
//               �������ϥǡ������ɤ߹��ߤ���ӽ��ϥǡ�����񤭽Ф���  //
//               �Ԥ���                                                //
//  ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)        //
//               2013. 9. 5 ���� �� (Computer Vision Lab.)             //
//                                                                     //
//=====================================================================//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ImageFileIO.h"

void SkipCommentLine(FILE * fp);

//---------------------------------------------------------------------//
// void GetAxisFromIndex(int iWidth, int iIndex, int * iX, int * iY)   //
// ��      �� : �������Υ���ǥå������飲������ɸ�����               //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                     //
// [����]                                                              //
// iWidth       : �����ϡ˲��������ʲ��ǿ���                           //
// iX           : �����ϡ˲������κ�ɸ�ʲ��ǿ���                       //
// iY           : �����ϡ˽������κ�ɸ�ʲ��ǿ���                       //
// iIndex       : �ʽ��ϡ˥���ǥå���                                 //
//---------------------------------------------------------------------//
void GetAxisFromIndex(int iWidth, int iIndex, int * iX, int * iY) {
    *iX = iIndex%iWidth;
    *iY = iIndex/iWidth;
}

//---------------------------------------------------------------------//
// void GetIndexFromAxis(int iWidth, int iX, int iY, int * iIndex)     //
// ��      �� : ��������ɸ���飱�����Υ���ǥå��������               //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                     //
// [����]                                                              //
// iWidth       : �����ϡ˲��������ʲ��ǿ���                           //
// iIndex       : �����ϡ˥���ǥå���                                 //
// iX           : �ʽ��ϡ˲������κ�ɸ�ʲ��ǿ���                       //
// iY           : �ʽ��ϡ˽������κ�ɸ�ʲ��ǿ���                       //
//---------------------------------------------------------------------//
void GetIndexFromAxis(int iWidth, int iX, int iY, int * iIndex) {
    *iIndex = iWidth*iY + iX;
}

//---------------------------------------------------------------------//
// struct RGB * ReadPpm(int * iWidth, int * iHeight, int * iMaxValue)  //
// ��      �� : PPM�ե�������ɤ߹���                                  //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                     //
// [�����]                                                            //
//              : ������([���ǿ�][RGB])��PPM�����Υǡ���               //
//                ���ǿ�=iWidth * iHeight                              //
// [����]                                                              //
// iWidth       : ���������ʲ��ǿ���                                   //
// iHeight      : �����ι⤵�ʲ��ǿ���                                 //
// iMaxValue    : �����γƲ��Ǥ�RGB�κ�����                            //
//---------------------------------------------------------------------//
struct RGB * ReadPpm(int * iWidth, int * iHeight, int * iMaxValue) {

    FILE *fp;                    // �ե�����ݥ���
    enum PPM {P3, P6};           // �ƥ����ȷ��� or �Х��ʥ����
    int iPPMType;                // P3 or P6
    char chFileName[80];         // �ե�����͡���
    const int MAXCHARS = 100;    // ���Ԥκ���ʸ����
    char chLine[MAXCHARS];       // �ե����������ǧ�����ѿ�
    struct RGB * pRGBInputData;  // ���ϥǡ������Ǽ�����ѿ�
    unsigned char * pucData;     // ���ϥǡ������Ǽ�����ѿ�
    struct RGB sRGBcolor;        // ������
    int iNumPixels;              // ���ǿ�
    int iIndex;                  // ����ǥå���
    int w, h;                    // �롼�ץ�����
    
    // �ե�����̾������
    printf("Input INPUT PPM file name[*.ppm]? > ");
    scanf("%s", chFileName);

    // ���Ϥ��줿�ե�����Υ����ץ�
    // �����ץ�˼��Ԥξ��ϡ����顼ʸ����Ϥ����֤��ͤȤ��ƣ����֤���
    if((fp = fopen(chFileName, "r")) == NULL){
        fprintf(stderr, "Cannot open file [%s].\n", chFileName);
        exit(1);
    }

    // �إå����ɤ߹���
    fgets(chLine, MAXCHARS, fp);

    // PPM����(P3)�ǤϤʤ���硢���顼ʸ����Ϥ����֤��ͤȤ��ƣ����֤�
    if (strncmp(chLine, "P3", 2) == 0){
	iPPMType = P3;
    } else if (strncmp(chLine, "P6", 2) == 0){
	iPPMType = P6;
	fclose(fp);
	fp = fopen(chFileName, "rb");
	fgets(chLine, MAXCHARS, fp);
    } else {
	fprintf(stderr, "[%s] is not PPM file.\n", chFileName);
        exit(1);
    }

    // �����ȹԤ��ɤ����Ф�
    SkipCommentLine(fp);

    // �����ǡ������顢�����������⤵���ɤ߹���
    fgets(chLine, MAXCHARS, fp);
    sscanf(chLine, "%d %d", iWidth, iHeight);

    // �����ȹԤ��ɤ����Ф�
    SkipCommentLine(fp);

    // �����ǡ������顢�����٤��ɤ߹���
    fgets(chLine, MAXCHARS, fp);
    sscanf(chLine, "%d", iMaxValue);
    iNumPixels = (*iWidth)*(*iHeight);

    // ���ϲ����ǡ����Υ����ΰ�γ���
    // psInputData[iWidth*iHeight]
    pRGBInputData = (struct RGB *)malloc(iNumPixels*sizeof(struct RGB));

    // �����ͤ��ɤ߹���
    if(iPPMType == P6) {
	pucData = (unsigned char *)malloc(iNumPixels*sizeof(unsigned char[3]));
	fread(pucData, sizeof(unsigned char), iNumPixels*3, fp);
    }
    for(h = 0; h < *iHeight; h++) {
	for(w = 0; w < *iWidth; w++) {
	    if(iPPMType == P3) {
		if(feof(fp)) {
		    fprintf(stderr, "Error: [%s] is not a correct PPM file.\n",
			    chFileName);
		    exit(-1);
		}

		// �����Ǥ�RGB�ǡ������ɤ߹���
		fscanf(fp, "%d %d %d ",
		       &sRGBcolor.iRed, &sRGBcolor.iGreen, &sRGBcolor.iBlue);
		// RGB�ǡ����γ�Ǽ
		GetIndexFromAxis(*iWidth, w, h, &iIndex);
		pRGBInputData[iIndex].iRed   = sRGBcolor.iRed;
		pRGBInputData[iIndex].iGreen = sRGBcolor.iGreen;
		pRGBInputData[iIndex].iBlue  = sRGBcolor.iBlue;
	    } else { // P6
		GetIndexFromAxis(*iWidth, w, h, &iIndex);
		pRGBInputData[iIndex].iRed   = pucData[3*iIndex];
		pRGBInputData[iIndex].iGreen = pucData[3*iIndex+1];
		pRGBInputData[iIndex].iBlue  = pucData[3*iIndex+2];
	    }


        }
    }

    // �ե�����Υ�����
    fclose(fp);  

    return pRGBInputData;
}

//--------------------------------------------------------------------//
// void FreePpm(struct RGB * pRGBOutputData)                          //
// ��      �� : PPM�����β����ǡ�������¸���Ƥ�������ΰ�γ���     //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                    //
// [����]                                                             //
// pRGBOutputData : ������([���ǿ�][RGB])��PPM�����Υǡ���            //
//--------------------------------------------------------------------//
void FreePpm(struct RGB * pRGBOutputData) {
    free(pRGBOutputData);
}

//--------------------------------------------------------------------//
// void WritePpm(struct RGB * pRGBOutputData, int iWidth,             //
//               int iHeight, int iMaxValue)                          //
// ��      �� : PPM�ե�����ؽ񤭽Ф�                                 //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                    //
// [����]                                                             //
// piRGBOutputData : ������([���ǿ�][RGB])��PPM�����Υǡ���           //
//                ���ǿ�=iWidth * iHeight                             //
// iWidth       : ���������ʲ��ǿ���                                  //
// iHeight      : �����ι⤵�ʲ��ǿ���                                //
// iMaxValue    : �����γƲ��Ǥ�RGB�κ�����                           //
//--------------------------------------------------------------------//
void WritePpm(struct RGB * pRGBOutputData, int iWidth, int iHeight, int iMaxValue) {

    FILE *fp;              // �ե�����ݥ���
    char chFileName[80];   // �ե�����͡���
    int i;                 // �롼�ץ�����

    // ���ϥե�����̾������
    printf("Input OUTPUT PPM file name[*.ppm]? > ");
    scanf("%s", chFileName);

    // ���ϥե�����Υ����ץ�
    // �����ץ�˼��Ԥξ��ϡ����顼ʸ����Ϥ����֤��ͤȤ��ƣ����֤�.
    if((fp = fopen(chFileName, "w")) == NULL){
        fprintf(stderr, "Cannot open file [%s].\n", chFileName);
        exit(1);
    }

    // �إå��ΰ�񤭹���(������������)
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d\n", iWidth, iHeight);
    fprintf(fp, "%d\n", iMaxValue); // ������

    // �Ʋ��ǥǡ����񤭹���
    for(i = 0; i < iWidth*iHeight; i++){
        // �����ͤ�ե�����ν񤭹���
        fprintf(fp, "%5d%5d%5d  ",
		pRGBOutputData[i].iRed,
		pRGBOutputData[i].iGreen,
		pRGBOutputData[i].iBlue);
                
        // �������͡�RGB�ˤ��Ȥ˲���
        if((i + 1)%5 == 0){
           fprintf(fp, "\n");
        }
    }

    // �ե�����Υ�����
    fclose(fp);
}

//--------------------------------------------------------------------//
// int * ReadPgm(int * iWidth, int * iHeight, int * iMaxValue)����    //
// ��      �� : PGM�ե�������ɤ߹���                                 //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                    //
// [�����]                                                           //
//              : ������([���ǿ�])��PGM�����Υǡ���                   //
//                ���ǿ�=iWidth * iHeight                             //
// [����]                                                             //
// iWidth       : ���������ʲ��ǿ���                                  //
// iHeight      : �����ι⤵�ʲ��ǿ���                                //
// iMaxValue    : �����β����ͤκ�����                                //
//--------------------------------------------------------------------//
int * ReadPgm(int * iWidth, int * iHeight, int * iMaxValue) {

    FILE *fp;                    // �ե�����ݥ���
    char chFileName[80];         // �ե�����͡���
    enum PGM {P2, P5};           // �ƥ����ȷ��� or �Х��ʥ����
    int iPGMType;                // P2 or P5
    const int MAXCHARS = 100;    // ���Ԥκ���ʸ����
    char chLine[MAXCHARS];       // �ե����������ǧ�����ѿ�
    int * piInputData;           // ���ϥǡ������Ǽ�����ѿ�
    unsigned char * pucData;     // ���ϥǡ������Ǽ�����ѿ�
    int iNumPixels;              // ���ǿ�
    int iIndex;                  // ����ǥå���
    int w, h;                    // �롼�ץ�����
    
    // �ե�����̾������
    printf("Input INPUT PGM file name[*.pgm]? > ");
    scanf("%s", chFileName);

    // ���Ϥ��줿�ե�����Υ����ץ�
    // �����ץ�˼��Ԥξ��ϡ����顼ʸ����Ϥ����֤��ͤȤ��ƣ����֤���
    if((fp = fopen(chFileName, "r")) == NULL){
        fprintf(stderr, "Cannot open file [%s].\n", chFileName);
        exit(1);
    }

    // �إå��ΰ��ɤ߹���
    fgets(chLine, MAXCHARS, fp);

    // PPM����(P3)�ǤϤʤ���硢���顼ʸ����Ϥ����֤��ͤȤ��ƣ����֤�
    if (strncmp(chLine, "P2", 2) == 0){
	iPGMType = P2;
    } else if (strncmp(chLine, "P5", 2) == 0){
	iPGMType = P5;
	fclose(fp);
	fp = fopen(chFileName, "rb");
	fgets(chLine, MAXCHARS, fp);
    } else {
	fprintf(stderr, "[%s] is not PGM file.\n", chFileName);
        exit(1);
    }

    // �����ȹԤ��ɤ����Ф�
    SkipCommentLine(fp);

    // �����ǡ������顢�����������⤵���ɤ߹���
    fgets(chLine, MAXCHARS, fp);
    sscanf(chLine, "%d %d", iWidth, iHeight);

    // �����ȹԤ��ɤ����Ф�
    SkipCommentLine(fp);

    // �����ǡ������顢�����٤��ɤ߹���
    fgets(chLine, MAXCHARS, fp);
    sscanf(chLine, "%d", iMaxValue);
    iNumPixels = (*iWidth)*(*iHeight);

    // ���ϲ����ǡ����Υ����ΰ�γ���
    // piInputData[iWidth*iHeight]
    piInputData = (int *)(malloc(iNumPixels*sizeof(int)));

    // �����ȹԤ��ɤ����Ф�
    SkipCommentLine(fp);

    // �����ͤ��ɤ߹���
    if(iPGMType == P5) {
	pucData = (unsigned char *)malloc(iNumPixels*sizeof(unsigned char));
	fread(pucData, sizeof(unsigned char), iNumPixels, fp);
    }
    for(h = 0; h < *iHeight; h++) {
	for(w = 0; w < *iWidth; w++) {
	    if(iPGMType == P2) {
		if(feof(fp)) {
		    fprintf(stderr, "Error: [%s] is not a correct PGM file.\n",
			    chFileName);
		    exit(-1);
		}

		// �����ǤΥǡ������ɤ߹��ߡ���Ǽ
		GetIndexFromAxis(*iWidth, w, h, &iIndex);
		fscanf(fp, "%d", &piInputData[iIndex]);
	    } else { // P5
		GetIndexFromAxis(*iWidth, w, h, &iIndex);
		piInputData[iIndex] = pucData[iIndex];
	    }
        }
    }

    // �ե�����Υ�����
    fclose(fp);  

    return piInputData;
}

//---------------------------------------------------------------------//
// void FreePgm(int * piOutputData)                                    //
// ��      �� : PGM�����β����ǡ�������¸���Ƥ�������ΰ�γ���      //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                     //
// [����]                                                              //
// piOutputData : ������([���ǿ�][RGB])��PGM�����Υǡ���               //
//---------------------------------------------------------------------//
void FreePgm(int * piOutputData) {
    free(piOutputData);
}

//---------------------------------------------------------------------//
// void WritePgm(int * piOutputData, int iWidth,                       //
//               int iHeight, int iMaxValue)                           //
// ��      �� : PGM�ե�����ؽ񤭽Ф�                                  //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                     //
// [����]                                                              //
// piInputData  : ������([���ǿ�])��PGM�����Υǡ���                    //
//                ���ǿ�=iWidth * iHeight                              //
// iWidth       : ���������ʲ��ǿ���                                   //
// iHeight      : �����ι⤵�ʲ��ǿ���                                 //
// iMaxValue    : �����β����ͤκ�����                                 //
//---------------------------------------------------------------------//
void WritePgm(int * piOutputData, int iWidth, int iHeight, int iMaxValue) {

    FILE *fp;              // �ե�����ݥ���
    char chFileName[80];   // �ե�����͡���
    int i;                 // �롼�ץ�����

    // ���ϥե�����̾������
    printf("Input OUTPUT PGM file name[*.pgm]? > ");
    scanf("%s", chFileName);

    // ���ϥե�����Υ����ץ�
    // �����ץ�˼��Ԥξ��ϡ����顼ʸ����Ϥ����֤��ͤȤ��ƣ����֤�.
    if((fp = fopen(chFileName, "w")) == NULL){
        fprintf(stderr, "Cannot open file [%s].\n", chFileName);
        exit(1);
    }

    // �إå��ΰ�񤭹���(������������)
    fprintf(fp, "P2\n");
    fprintf(fp, "%d %d\n", iWidth, iHeight);
    fprintf(fp, "%d\n", iMaxValue);  // ������

    // �Ʋ��ǥǡ����񤭹���
    for(i = 0; i < iWidth*iHeight; i++){
    
        // �����ͤ�ե�����ν񤭹���
        fprintf(fp, "%5d", piOutputData[i]);
                
        // 10�����ͤ��Ȥ˲���
        if((i + 1)%15 == 0){
           fprintf(fp, "\n");
        }
    }

    // �ե�����Υ�����
    fclose(fp);
}

//---------------------------------------------------------------------//
// void SkipCommentLine(FILE * fp)                                     //
// ��      �� : �����ȹԤ��ɤ����Ф�                                 //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                     //
// [����]                                                              //
// fp     : �ե����륹�ȥ꡼��ݥ���                                 //
//---------------------------------------------------------------------//
void SkipCommentLine(FILE * fp) {
    
    const int MAXCHARS = 100;
    char chLine[MAXCHARS]; 
    fpos_t current;

    while(!feof(fp)) {
	// ���ߤΥ��ȥ꡼����֤���¸
	fgetpos(fp, &current);
	
	// ���Լ���
	fgets(chLine, MAXCHARS, fp);

	// �����ȹԤǤʤ���С����ȥ꡼����֤��ᤷ�ƥ꥿����
	if(chLine[0] != '#') {
	    fsetpos(fp, &current);
	    return;
	}
    }    
}
