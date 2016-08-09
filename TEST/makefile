SRC = prog.cpp
OBJ = prog.o
CC = g++
FLAGS = -O2 -fomit-frame-pointer

all: build run

build: $(SRC)
	$(CC) $(FLAGS) -o $(OBJ) $(SRC)

run:
	./$(OBJ) < input
