CC = gcc
CFLAGS = -pthread

all: st_pipeline

st_pipeline: Prime.o CustomQueue.o ActiveObject.o st_pipeline.o
	$(CC) $(CFLAGS) -o st_pipeline Prime.o CustomQueue.o ActiveObject.o st_pipeline.o -lm

Prime.o: Prime.c Prime.h
	$(CC) $(CFLAGS) -c Prime.c

CustomQueue.o: CustomQueue.c CustomQueue.h
	$(CC) $(CFLAGS) -c CustomQueue.c

ActiveObject.o: ActiveObject.c ActiveObject.h CustomQueue.h
	$(CC) $(CFLAGS) -c ActiveObject.c

st_pipeline.o: st_pipeline.c ActiveObject.h CustomQueue.h Prime.h
	$(CC) $(CFLAGS) -c st_pipeline.c

clean:
	rm *.o st_pipeline
