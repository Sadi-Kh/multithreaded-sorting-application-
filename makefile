CC = gcc
CFLAGS = -Wall -pthread

all: sort

sort: sorting_multithreaded.c
	$(CC) $(CFLAGS) -o sort sorting_multithreaded.c

clean:
	rm -f sort
