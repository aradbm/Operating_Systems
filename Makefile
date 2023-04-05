CC = gcc
FLAGS = -Wall -g
.PHONY: all
all: copy cmp libcodecA

cmp : cmp.c
	$(CC) $(FLAGS) -o cmp cmp.c
copy : copy.c
	$(CC) $(FLAGS) -o copy copy.c
libcodecA: codecA.c
	$(CC) $(FLAGS) -fPIC -shared -o ./libcodecA codecA.c

# task1:  hello_ariel.c hello_ariel.h main1_1.c
# 	gcc -o hello1 hello_ariel.c main1_1.c

# task2:	hello_ariel.h main1_1.c lib
# 	gcc main1_1.c -L. -l Hello -o hello2

# task3:  hello_ariel.h main1_3.c lib
# 	gcc main1_3.c -fPIC -ldl -o hello3

# lib:	hello_ariel.h hello_ariel.c
# 	gcc -shared hello_ariel.c -fPIC -o libHello.so

.PHONY: clean
clean:
	-rm -f *.out cmp copy libcodecA
