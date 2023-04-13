CC = gcc
FLAGS = -Wall -g
.PHONY: all
all: copy cmp libcodecA stshell

cmp : cmp.c
	$(CC) $(FLAGS) -o cmp cmp.c
copy : copy.c
	$(CC) $(FLAGS) -o copy copy.c
libcodecA: codecA.c
	$(CC) $(FLAGS) -fPIC -shared -o ./libcodecA codecA.c

stshell: stshell.c
	$(CC) $(FLAGS) -o stshell stshell.c

.PHONY: clean
clean:
	-rm -f *.out cmp copy libcodecA stshell
