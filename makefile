# 
CC=gcc
CFLAGS= -lm -fPIC -Idatagenerator

DGDRI=datagenerator/


all: datagenerator_test

datagenerator_test : datagenerator_test.c $(DGDRI)datagenerator.o
	$(CC) -o datagenerator_test datagenerator_test.c $(DGDRI)datagenerator.o $(CFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@



clean:
	rm $(DGDRI)datagenerator.o datagenerator_test

