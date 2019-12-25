### Introduction
This project is an archive of my code for the course Computer Vision and Image Understanding.

### This project implements the following  functions:
1. BrightnessHistogram
2. BlackWhiteImage
3. neighborPix
4. neighborPix3D
5. EdgeDetection
6. EdgeDetectionSobel
7. templateMatching
8. smoothing
9. bilateralFiltering
10. others

### Usage
```
gcc  -g -Wall   -c -o ImageFileIO.o ImageFileIO.c
gcc  -g -Wall   -c -o ImageFilter.o ImageFilter.c
gcc  -g -Wall   -c -o ImageTools.o ImageTools.c
gcc  -g -Wall   -c -o BitmapFont.o BitmapFont.c
gcc  -g -Wall   -c -o main.o main.c
gcc  -o imgfilter ImageFileIO.o ImageFilter.o ImageTools.o BitmapFont.o main.o -lm

./imgfilter 
```
### Contact
Ouyang （irvineoy@163.com）
