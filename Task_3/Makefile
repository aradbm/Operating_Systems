CC= gcc
FLAG=-Wall -g

all: server client stnc

stnc: stnc.o
	$(CC) -o stnc stnc.c $(FLAG)
client: client.o
	$(CC) -o client client.c $(FLAG)
server: server.o
	$(CC) -o server server.c $(FLAG)

.PHONY:clean
clean: 
	rm -f *.o stnc *.txt server client