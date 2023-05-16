CC=gcc
CFLAGS=-Wall -Wextra -g


all: react_server client

client: client.o
	$(CC) $(CFLAGS) -o client client.o

react_server: react_server.o reactor.o hashmap.o
	$(CC) $(CFLAGS) -o react_server react_server.o reactor.o hashmap.o

react_server.o: react_server.c reactor.h
	$(CC) $(CFLAGS) -c react_server.c

reactor.o: reactor.c reactor.h hashmap.h
	$(CC) $(CFLAGS) -c reactor.c

hashmap.o: hashmap.c hashmap.h
	$(CC) $(CFLAGS) -c hashmap.c

.PHONY: clean
clean:
	rm -f *.o react_server client
