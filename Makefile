CC= gcc
CFLAGS=-I.
FLAG=-Wall -g

all: main

main: main.o
	$(CC) -pthread -o main main.c $(FLAG)

run: main
	./main

.PHONY:clean
clean: 
	rm -f *.o main 12347 myrandomfile.txt newfile.txt mysharedfile.txt threadnewfile.txt