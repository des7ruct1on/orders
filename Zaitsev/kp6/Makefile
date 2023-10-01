CC = gcc
CFLAGS = -std=c99 -Wall -Werror 
DEBUG = gdb
FILEOUT = out/execute.out
MAIN_SOURCES = execute.c
GLOBALS_SOURCES = student.c
CONV = convert.c
CONVOUT = out/conv.out
GEN = db_generator.c
GENOUT = out/db.out

all:
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(MAIN_SOURCES)  -o $(FILEOUT)
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(CONV) -o $(CONVOUT)
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(GEN) -o $(GENOUT)
clean:
	rm -f out/*.out
debug:
	$(CC) -g $(CFLAGS) $(SOURCES)  -o $(FILEOUT)
	$(CC) -g $(CFLAGS) $(CONV) -o $(CONVOUT)
	$(CC) -g $(CFLAGS) $(GEN) -o $(GENOUT)
cmp:
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(MAIN_SOURCES) -o $(FILEOUT)
main:
	./$(FILEOUT) $(FILE)
convertation:
	./$(CONVOUT) $(FILE1) $(FILE2)
generation:
	./$(GENOUT) $(FILE) $(COUNT)
convert:
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(CONV) -o $(CONVOUT)
generate:
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(GEN) -o $(GENOUT)