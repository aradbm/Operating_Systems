CC= gcc
FLAG=-Wall -g

all: stnc run

stnc: stnc.o
	$(CC) -o stnc stnc.c $(FLAG)

run: stnc
	./stnc -s 6000 -p  && ./stnc -c 127.0.0.1 6000 -p

.PHONY:clean
clean: 
	rm -f *.o stnc 