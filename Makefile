#Author: Timothy Schultz
#CS 4280
#Project 4

CC = g++ 
CFLAGS = -g -Wall 
TARGET = compfs
OBJ = main.o scanner.o parser.o generator.o
SRC = main.cpp scanner.cpp parser.cpp generator.cpp

all: $(TARGET) 

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

main.o: main.cpp scanner.h 
	$(CC) $(CFLAGS) -c main.cpp

scanner.o: scanner.cpp scanner.h token.h parser.h
	$(CC) $(CFLAGS) -c scanner.cpp

parser.o: parser.cpp scanner.h parser.h node.h
	$(CC) $(CFLAGS) -c parser.cpp

stack.o: generator.cpp stack.h
	$(CC) $(CFLAGS) -c generator.cpp

.PHONY: clean
clean:
	/bin/rm -f *.o $(TARGET)
