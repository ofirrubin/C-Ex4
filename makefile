CC=gcc
AR=ar
FLAGS= -Wall -g


all: main

main: main.c Graph.c Graph.h GraphAlgo.c GraphAlgo.h
	$(CC) $(FLAGS) main.c Graph.c GraphAlgo.c -o graph -lm

.PHONY: all clean

clean: # Remove any file that might created.
	rm -f *.o *.a *.so *.gch main
