CC = gcc
CFLAGS = -g -std=c99 -w -pipe -O3
MAIN = execute.c
MAIN_OUT = out/execute.out 
IO = io.c 
STUDENT = student.c 
CONV = convert.c 
CONV_OUT = out/convert.out 
GENERATE = generate.c
GENERATE_OUT = out/generate.out
all:
	$(CC) $(CFLAGS) $(IO) $(STUDENT) $(MAIN) -o $(MAIN_OUT)
	$(CC) $(CFLAGS) $(IO) $(STUDENT) $(CONV) -o $(CONV_OUT)
	$(CC) $(CFLAGS) $(IO) $(STUDENT) $(GENERATE) -o $(GENERATE_OUT)

execute:  
	./$(MAIN_OUT) $(FILE)

clean:
	rm -f out/*.out

generate: 
	./$(GENERATE_OUT) $(FILE) $(COUNT)

convert:
	./$(CONV_OUT) $(FILE1) $(FILE2)
