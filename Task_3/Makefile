CC= gcc
FLAG=-Wall -g

all: stnc runs runc

stnc: stnc.o
	$(CC) -o stnc stnc.c $(FLAG)

# runs: stnc
# 	./stnc -s 6000 -p tcp IPV4
# runc:
# 	./stnc -c 127.0.0.1 6000 -p tcp IPV4

runs: stnc
	./stnc -s 6000 -p uds dgram -q
runc:
	./stnc -c 127.0.0.1 6000 -p uds stream -q

.PHONY:clean
clean: 
	rm -f *.o stnc newfile.txt myrandomfile.txt