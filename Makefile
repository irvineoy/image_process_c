#
#    ファイル名 : Makefile
#
#    更  新  日 : 2003. 3. 21 駒井 教平 (Computer Vision & Games Lab.)
#                 2004. 2. 13 木村 彰徳 (Computer Graphics Lab.)
#                 2011. 4. 11 備藤 達郎 (Computer Vision Lab.)
#                 2014.11. 24 松尾 直志
#
SHELL=bash

# C言語コンパイラ
CC      = gcc 
# C言語コンパイルオプション
# -g : デバッグオプション
# -Wall: 最大警告レベル (GNU C)
CFLAGS  = -g -Wall -pedantic-errors -std=c99
# リンクオプション
# -lm : 標準数学ライブラリ
LDFLAGS = -lm

export LANG=C
export LC_ALL=C
NOW=`date +%b%d.%H%M`

# ソースプログラム
MAIN  = main.c
SRCS  = ImageFileIO.c ImageFilter.c ImageTools.c 
HDRS  = ${SRCS:.c=.h}

# オブジェクトファイル
OBJS  = ${SRCS:.c=.o} ${MAIN:.c=.o}

# 実行プログラム名
EXE   = imgfilter

ALL = $(EXE)

$(EXE) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# ソースファイルの依存関係
ImageFileIO.o : ImageFileIO.c ImageFileIO.h
ImageFilter.o : ImageFilter.c ImageFilter.h ImageFileIO.h ImageTools.h
ImageTools.o  : ImageTools.c ImageTools.h ImageFileIO.h

clean:
	rm -f $(OBJS) $(EXE)

clean-all:
	rm -f $(OBJS) $(EXE) a.out *core *~

backup:
	(cd ..; tar -zcvf sousei2_2011.$(NOW).tgz sousei2_2011/{*.[ch],Makefile,TransformKanjiCode,*.txt,Airport.ppm,Building.ppm,Castle.ppm,Characters.ppm,Female.ppm,GeometryImage.ppm,Plane.ppm,R.pgm,Rits.pgm,Satsuma.pgm,Rits.ppm})
