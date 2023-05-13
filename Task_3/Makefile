CC= gcc
FLAG=-Wall -g

all: stnc

asd: client server runserver
stnc: stnc.o
	$(CC) -o stnc stnc.c $(FLAG)
client: client.o
	$(CC) -o client client.c $(FLAG)
server: server.o
	$(CC) -o server server.c $(FLAG)

### performance test - tcp IPV4 ###
# runs: stnc
# 	./stnc -s 6000 -p tcp IPV4
# runc:
# 	./stnc -c 127.0.0.1 6000 -p tcp IPV4

### performance test - uds IPV6 ###
runserver: stnc
	./server 127.0.0.1 6000
runclient: stnc
	./client 127.0.0.1 6000

.PHONY:clean
clean: 
	rm -f *.o stnc *.txt server client