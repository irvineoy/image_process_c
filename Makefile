#
#    �ե�����̾ : Makefile
#
#    ��  ��  �� : 2003. 3. 21 ��� ��ʿ (Computer Vision & Games Lab.)
#                 2004. 2. 13 ��¼ ���� (Computer Graphics Lab.)
#                 2011. 4. 11 ��ƣ ãϺ (Computer Vision Lab.)
#                 2014.11. 24 ���� ľ��
#
SHELL=bash

# C���쥳��ѥ���
CC      = gcc 
# C���쥳��ѥ��륪�ץ����
# -g : �ǥХå����ץ����
# -Wall: ����ٹ��٥� (GNU C)
CFLAGS  = -g -Wall -pedantic-errors -std=c99
# ��󥯥��ץ����
# -lm : ɸ����إ饤�֥��
LDFLAGS = -lm

export LANG=C
export LC_ALL=C
NOW=`date +%b%d.%H%M`

# �������ץ����
MAIN  = main.c
SRCS  = ImageFileIO.c ImageFilter.c ImageTools.c 
HDRS  = ${SRCS:.c=.h}

# ���֥������ȥե�����
OBJS  = ${SRCS:.c=.o} ${MAIN:.c=.o}

# �¹ԥץ����̾
EXE   = imgfilter

ALL = $(EXE)

$(EXE) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# �������ե�����ΰ�¸�ط�
ImageFileIO.o : ImageFileIO.c ImageFileIO.h
ImageFilter.o : ImageFilter.c ImageFilter.h ImageFileIO.h ImageTools.h
ImageTools.o  : ImageTools.c ImageTools.h ImageFileIO.h

clean:
	rm -f $(OBJS) $(EXE)

clean-all:
	rm -f $(OBJS) $(EXE) a.out *core *~

backup:
	(cd ..; tar -zcvf sousei2_2011.$(NOW).tgz sousei2_2011/{*.[ch],Makefile,TransformKanjiCode,*.txt,Airport.ppm,Building.ppm,Castle.ppm,Characters.ppm,Female.ppm,GeometryImage.ppm,Plane.ppm,R.pgm,Rits.pgm,Satsuma.pgm,Rits.ppm})
