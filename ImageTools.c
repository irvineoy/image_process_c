//=====================================================================//
//                                                                     //
//  �ե�����̾ : ImageTools.c                                          //
//  ��      �� : PGM (Portable GrayMap)�����Υǡ����˥ץ�ߥƥ��֤�    //
//               �޷�����������ؿ������                              //
//  ��  ��  �� : 2004. 2. 12 ��¼ ���� (Computer Graphics Lab.)        //
//               2013. 9. 5 ���� �� (Computer Vision Lab.)             //
//                                                                     //
//=====================================================================//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ImageTools.h"

#include "ImageFileIO.h"

//-----------------------------------------------------------------------//
// void DrawStraightLine(int * piImageData,                              //
//                       int iWidth, int iHeight, int iMaxValue,         //
//                       int iStartX, int iStartY, int iEndX, int iEndY, //
//                       int iSTYLE, int iBW)                            //
//  ��      �� : PGM�����Υǡ�����ľ�������                             //
//  ��  ��  �� : 2004. 2. 12 ��¼ ���� (Computer Graphics Lab.)          //
//               2013. 9. 5 ���� �� (Computer Vision Lab.)               //
//                                                                       //
// [����]                                                                //
// piImageData :�����ϡ�ľ����������PGM�����Υǡ���                      //
// iWidth      :�����ϡ�ľ����������PGM�����Υǡ��������ʲ��ǿ���        //
// iHeight     :�����ϡ�ľ����������PGM�����Υǡ����ι⤵�ʲ��ǿ���      //
// iMaxValue   :�����ϡ�ľ����������PGM�����Υǡ����β��Ǥκ�����        //
// iStartX     :�����ϡ�ľ���λ����� X ��ɸ                              //
// iStartY     :�����ϡ�ľ���λ����� Y ��ɸ                              //
// iEndX       :�����ϡ�ľ���ν����� X ��ɸ                              //
// iEndY       :�����ϡ�ľ���ν����� Y ��ɸ                              //
// iSTYLE      :�����ϡ�ľ���ο�. SOLID��DASHED �ޤ��� DOTTED            //
//               (������̤������                                         //
// iBW         :�����ϡ�ľ���ο���BLACKLINE �ޤ��� WHITELINE             //
//-----------------------------------------------------------------------//
void DrawStraightLine(int * piImageData,
		      int iWidth, int iHeight, int iMaxValue,
		      int iStartX, int iStartY, int iEndX, int iEndY,
		      int iSTYLE, int iBW) {

    int iIndex;                         // ����ǥå���
    float w, h;                         // ��ɸ�롼�ץ�����
    const float fStep = 0.5;            // ľ�����������ƥå�
    const int iBLACK = 0;               // ��
    const int iWHITE = iMaxValue;       // ��
    int iXmin, iXmax, iYmin, iYmax;     // ��ɸ

    // ľ��������

    // |tan��| < 1 �ޤ��� iStartY == iEndY
    if(abs(iEndY - iStartY) < abs(iEndX - iStartX) || iStartY == iEndY) {

        if(iStartX > iEndX) {
            iXmin = iEndX;
            iXmax = iStartX;
        } else {
            iXmin = iStartX;
            iXmax = iEndX;
        }
 
	for(w = iXmin; w < iXmax; w+=fStep) {
            h = (iEndY - iStartY)*(w - iStartX)/(iEndX - iStartX) + iStartY;
	    if(h >= 0 && h < iHeight) {
	        GetIndexFromAxis(iWidth, (int)w, (int)h, &iIndex);
		if(iBW == BLACKLINE) {  // ��
		    piImageData[iIndex] = iBLACK;
		} else {                // ��
		    piImageData[iIndex] = iWHITE;
		}
            }
        }

    // |tan��| >= 1 �ޤ��� iStartX == iEndX
    } else {

        if(iStartY > iEndY) {
            iYmin = iEndY;
            iYmax = iStartY;
        } else {
            iYmin = iStartY;
            iYmax = iEndY;
        }
	
	for(h = iYmin; h < iYmax; h+=fStep) {
            w = (iEndX - iStartX)*(h - iStartY)/(iEndY - iStartY) + iStartX;
	    if(w >= 0 && w < iWidth) {
		GetIndexFromAxis(iWidth, (int)w, (int)h, &iIndex);
		if(iBW == BLACKLINE) {  // ��
		    piImageData[iIndex] = iBLACK;
		} else {                // ��
		    piImageData[iIndex] = iWHITE;
		}
	    }
	}
    }
    
}

