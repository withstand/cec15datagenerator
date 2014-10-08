# 
CC=gcc
LIB=ar rcs 
CFLAGS=-Imeschach -lm -fPIC -Idatagenerator
LIBS=meschach.lib

DGDRI=datagenerator/
LIBDIR=meschach/
MESCHACH_H=err.h machine.h matrix2.h matrix.h meminfo.h
FILES=$(LIBDIR)copy.c $(LIBDIR)err.c $(LIBDIR)hsehldr.c $(LIBDIR)init.c \
	$(LIBDIR)ivecop.c $(LIBDIR)machine.c $(LIBDIR)meminfo.c \
	$(LIBDIR)memory.c $(LIBDIR)memstat.c $(LIBDIR)qrfactor.c $(LIBDIR)submat.c \
	$(LIBDIR)vecop.c

OBJS=$(FILES:.c=.o)

all: datagenerator_test

datagenerator_test : datagenerator_test.c $(DGDRI)datagenerator.o meschach.a
	$(CC) -o datagenerator_test datagenerator_test.c $(DGDRI)datagenerator.o meschach.a $(CFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

meschach.a: $(OBJS)
	$(LIB) meschach.a $(OBJS)


clean:
	rm meschach.a $(OBJS) $(DGDRI)datagenerator.o datagenerator_test

