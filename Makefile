# *****************************************************
# Makefile for executable

# *****************************************************
# Parameters to control Makefile operation

CC = gcc
CFLAGS = -Wall -lm -lX11

# ****************************************************
# Entries to bring the executable up to date

all: program clean

program: main.o graphiclib.o
	$(CC) $(CFLAGS) -o program main.o graphiclib.o

main.o: main.c graphiclib.h
	$(CC) $(CFLAGS) -c main.c

graphiclib.o: graphiclib.c graphiclib.h
	$(CC) $(CFLAGS) -c graphiclib.c

clean:
	rm -f *.o

uninstall:
	rm -f program *~