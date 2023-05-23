CC=gcc
CFLAGS=-Wall -Wextra -g
LIBS=-L. -lreactor
RPATH=-Wl,-rpath,'$$ORIGIN'

all: libreactor.so react_server client

client: client.o
	$(CC) $(CFLAGS) $(RPATH) -o client client.o $(LIBS)

react_server: react_server.o
	$(CC) $(CFLAGS) $(RPATH) -o react_server react_server.o $(LIBS)

react_server.o: react_server.c reactor.h
	$(CC) $(CFLAGS) -c react_server.c

libreactor.so: reactor.o hashmap.o
	$(CC) -shared -o libreactor.so reactor.o hashmap.o

reactor.o: reactor.c reactor.h hashmap.h
	$(CC) $(CFLAGS) -fPIC -c reactor.c

hashmap.o: hashmap.c hashmap.h
	$(CC) $(CFLAGS) -fPIC -c hashmap.c

.PHONY: clean
clean:
	rm -f *.o react_server client libreactor.so
