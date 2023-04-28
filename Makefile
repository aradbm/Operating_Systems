CC= gcc
CFLAGS=-I.
FLAG=-Wall -g
DEPS = codec.h
PWD = $(shell pwd)
all: encode decode codecA codecB cmp copy stshell myshell

codecA: codecA.so
codecB: codecB.so

encode: encode.o
	$(CC) $(FLAG) -o encode encode.o -ldl
decode: decode.o
	$(CC) $(FLAG) -o decode decode.o -ldl

%.o: %.c $(DEPS)
	$(CC) $(FLAG) -c -o $@ $< $(CFLAGS)


cmp : cmp.c
	$(CC) $(FLAGS) -o cmp cmp.c
copy : copy.c
	$(CC) $(FLAGS) -o copy copy.c
stshell: stshell.c
	$(CC) $(FLAGS) -o stshell stshell.c
myshell: myshell.c
	$(CC) $(FLAGS) -o myshell myshell.c

codecA.so: codecA.o codec.h
	$(CC) codecA.c -c -o -fPIC 
	$(CC) codecA.o -shared -o codecA.so 

codecB.so: codecB.o codec.h
	$(CC) codecB.c -c -o -fPIC 
	$(CC) codecB.o -shared -o codecB.so 


.PHONY:clean
clean: 
	rm -f *.o *.so *.a encode decode copy cmp codecA codecB myshell stshell
