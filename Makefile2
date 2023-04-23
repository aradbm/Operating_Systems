CC= gcc
CFLAGS=-I.
FLAG=-Wall -g
DEPS = codec.h
PWD = $(shell pwd)
all: encode decode codecA codecB

codecA: codecA.so
codecB: codecB.so

encode: encode.o
	$(CC) $(FLAG) -o encode encode.o -ldl
decode: decode.o
	$(CC) $(FLAG) -o decode decode.o -ldl

%.o: %.c $(DEPS)
	$(CC) $(FLAG) -c -o $@ $< $(CFLAGS)


codecA.so: codecA.o codec.h
	$(CC) codecA.c -c -o -fPIC 
	$(CC) codecA.o -shared -o codecA.so 

codecB.so: codecB.o codec.h
	$(CC) codecB.c -c -o -fPIC 
	$(CC) codecB.o -shared -o codecB.so 


.PHONY:clean
clean: 
	rm -f *.o *.so *.a encode decode copy cmp codecA codecB
