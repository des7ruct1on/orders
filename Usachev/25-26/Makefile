CC = gcc
CFLAGS = -std=c99 -Wall -Werror
DEBUG = gdb
FILEOUT = stack.out
SOURCES = stack.c main.c

all:
	$(CC) $(CFLAGS) $(SOURCES)  -o $(FILEOUT)
clean:
	rm -f *.outs
debug:
	$(CC) $(CFLAGS) -g $(SOURCES)
	sudo $(DEBUG) $(FILEOUT)
cmp:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILEOUT)
run:
	./$(FILEOUT)
