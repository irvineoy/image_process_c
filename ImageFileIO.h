//=====================================================================//
//                                                                     //
//  �ե�����̾ : ImageFileIO.h                                         //
//  ��      �� : ppm (Portable PixMap), pgm (Portable GrayMap)�ե����� //
//               �������ϥǡ������ɤ߹��ߤ���ӽ��ϥǡ�����񤭽Ф���  //
//               �Ԥ���                                                //
//  ��  ��  �� : 2004. 2. 11 ��¼ ���� (Computer Graphics Lab.)        //
//               2014. 9. 5 ���� �� (Computer VIsion Lab.)             //
//               2014. 11. 24 ���� ľ��                                //
//                                                                     //
//=====================================================================//
#ifndef _IMAGEFILEIO_H_
#define _IMAGEFILEIO_H_ 1

// ��¤�� RGB��
struct RGB {
    int iRed;
    int iGreen;
    int iBlue;
};

// RGB �ѥ�᡼��
#define RED   0
#define GREEN 1
#define BLUE  2

//---------------------------------------------------------------------//
// void GetAxisFromIndex(int iWidth, int iIndex, int * iX, int * iY)   //
// ��      �� : �������Υ���ǥå������飲������ɸ�����               //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                     //
// [����]                                                              //
// iWidth       : �����ϡ˲��������ʲ��ǿ���                           //
// iIndex       : �����ϡ˥���ǥå���                                 //
// iX           : �ʽ��ϡ˲������κ�ɸ�ʲ��ǿ���                       //
// iY           : �ʽ��ϡ˽������κ�ɸ�ʲ��ǿ���                       //
//---------------------------------------------------------------------//
void GetAxisFromIndex(int iWidth, int iIndex, int * iX, int * iY);

//---------------------------------------------------------------------//
// void GetIndexFromAxis(int iWidth, int iX, int iY, int * iIndex)     //
// ��      �� : ��������ɸ���飱�����Υ���ǥå��������               //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                     //
// [����]                                                              //
// iWidth       : �����ϡ˲��������ʲ��ǿ���                           //
// iX           : �����ϡ˲������κ�ɸ�ʲ��ǿ���                       //
// iY           : �����ϡ˽������κ�ɸ�ʲ��ǿ���                       //
// iIndex       : �ʽ��ϡ˥���ǥå���                                 //
//---------------------------------------------------------------------//
void GetIndexFromAxis(int iWidth, int iX, int iY, int * iIndex);

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
struct RGB * ReadPpm(int * iWidth, int * iHeight, int * iMaxValue);

//--------------------------------------------------------------------//
// void FreePpm(struct RGB * pRGBOutputData)                          //
// ��      �� : PPM�����β����ǡ�������¸���Ƥ�������ΰ�γ���     //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                    //
// [����]                                                             //
// pRGBOutputData : ������([���ǿ�][RGB])��PPM�����Υǡ���            //
//--------------------------------------------------------------------//
void FreePpm(struct RGB * pRGBOutputData);

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
void WritePpm(struct RGB * pRGBOutputData, int iWidth, int iHeight, int iMaxValue);

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
int * ReadPgm(int * iWidth, int * iHeight, int * iMaxValue);

//---------------------------------------------------------------------//
// void FreePgm(int * piOutputData)                                    //
// ��      �� : PGM�����β����ǡ�������¸���Ƥ�������ΰ�γ���      //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                     //
// [����]                                                              //
// piOutputData : ������([���ǿ�][RGB])��PGM�����Υǡ���               //
//---------------------------------------------------------------------//
void FreePgm(int * piOutputData);

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
void WritePgm(int * piOutputData, int iWidth, int iHeight, int iMaxValue);

//---------------------------------------------------------------------//
// void WritePgm(int * piOutputData, int iWidth,                       //
//               int iHeight, int iResolution)                         //
// ��      �� : PGM�ե�����ؽ񤭽Ф�                                  //
// ��  ��  �� : 2004. 2. 15 ��¼ ���� (Computer Graphics Lab.)         //
//              2013. 9. 5 ���� �� (Computer Vision Lab.)              //
//                                                                     //
// [����]                                                              //
// piInputData  : ������([���ǿ�])��PGM�����Υǡ���                    //
//                ���ǿ�=iWidth * iHeight                              //
// iWidth       : ���������ʲ��ǿ���                                   //
// iHeight      : �����ι⤵�ʲ��ǿ���                                 //
// iResolution  : �����β�����                                         //
//---------------------------------------------------------------------//
void WritePgm(int * piOutputData, int iWidth, int iHeight, int iResolution);

#endif
