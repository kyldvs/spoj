SRC = prog.cpp
OBJ = prog.o
CC = g++
FLAGS = -Wall -O2 -fomit-frame-pointer -std=c++0x

all: build run

build: $(SRC)
	$(CC) $(FLAGS) -o $(OBJ) $(SRC)

run:
	./$(OBJ) < input
