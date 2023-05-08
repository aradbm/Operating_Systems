CC= gcc
FLAG=-Wall -g

all: stnc

stnc: stnc.o
	$(CC) -o stnc stnc.c $(FLAG)
client: client.o
	$(CC) -o client client.c $(FLAG)
server: server.o
	$(CC) -o server server.c $(FLAG)

# runs: stnc
# 	./stnc -s 6000 -p tcp IPV4
# runc:
# 	./stnc -c 127.0.0.1 6000 -p tcp IPV4

runs: stnc
	./stnc -s 6000 -p uds dgram
runc:
	./stnc -c 127.0.0.1 6000 -p uds stream -q

.PHONY:clean
clean: 
	rm -f *.o stnc *.txt server client