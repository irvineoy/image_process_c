//=====================================================================//
//                                                                     //
//  �ե�����̾ : ImageTools.h                                          //
//  ��      �� : PGM (Portable GrayMap)�����Υǡ����˥ץ�ߥƥ��֤�    //
//               �޷�����������ؿ������                              //
//  ��  ��  �� : 2004. 2. 12 ��¼ ���� (Computer Graphics Lab.)        //
//               2013. 9. 5 ���� �� (Computer Vision Lab.)             //
//                                                                     //
//=====================================================================//
#ifndef _IMAGETOOLS_H_
#define _IMAGETOOLS_H_

//-----------------------------------------------------------------------//
// void DrawStraightLine(int * piImageData,                              //
//                       int iWidth, int iHeight, int iMaxValue,         //
//                       int iStartX, int iStartY, int iEndX, int iEndY, //
//                       int STYLE, int iBW)                             //
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
// iSTYLE      :�����ϡ�ľ���ο���SOLID��DASHED �ޤ��� DOTTED            //
// iBW         :�����ϡ�ľ���ο���BLACKLINE �ޤ��� WHITELINE             //
//-----------------------------------------------------------------------//
enum lineStype {SOLID, DASHED, DOTTED};
enum lineBW {BLACKLINE, WHITELINE};
void DrawStraightLine(int * piImageData,
		      int iWidth, int iHeight, int iMaxValue,
		      int iStartX, int iStartY, int iEndX, int iEndY,
		      int iSTYLE, int iBW);

//-----------------------------------------------------------------------//
// void Histogram1D(int * piHistData, int iNumHistData,                  //
//                  int iNumBin, int iMinBin, int iMaxBin, int iGRID)    //
//                                                                       //
//  ��  �� : �������ҥ��ȥ����                                          //
//  ������ : 2004. 2. 13 ��¼ ���� (Computer Graphics Lab.)              //
//           2013. 9. 5 ���� �� (Computer Vision Lab.)                   //
//                                                                       //
// [����]                                                                //
// piHistData   :�����ϡ˥ҥ��ȥ���ߥ󥰤���ǡ���                      //
// iNumHistData :�����ϡ˥ҥ��ȥ���ߥ󥰤���ǡ�����                    //
// iNumBin      :�����ϡ˥ӥ��                                          //
// iMinBin      :�����ϡ˥ӥ�κǾ���                                    //
// iMaxBin      :�����ϡ˥ӥ�κ�����                                    //
// iGRID         :�����ϡ˥���åɤ�̵ͭ (GRID, NOGRID, XGRID, YGRID)    //
//-----------------------------------------------------------------------//
#define NOGRID 0
#define GRID   1
#define XGRID  2
#define YGRID  3
void Histogram1D(int * piHistData, int iNumHistData,
		 int iNumBin, int iMinBin, int iMaxBin, int iGRID);


#endif
