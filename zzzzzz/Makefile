CC= gcc
FLAG=-Wall -g

all: stnc run

stnc: stnc.o
	$(CC) -o stnc stnc.c $(FLAG)

run: stnc
	./stnc

.PHONY:clean
clean: 
	rm -f *.o stnc