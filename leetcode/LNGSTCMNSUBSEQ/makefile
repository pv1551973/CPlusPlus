CC=g++
CFLAGS=-ggdb -g3 -pedantic-errors -Wall -Wextra -Wfatal-errors -Wpedantic -std=c++20
DEPS = 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: coliru.o 
	$(CC) -o executable coliru.o

run:
	./executable >& output.txt

clean:
	rm -f *.o executable
	>output.txt
