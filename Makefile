CPP_SRC=$(wildcard *.cpp)
HPP_SRC=$(wildcard *.cpp)
CC=g++
INC=-lX11

main: $(CPP_SRC) $(HPP_SRC)
	$(CC) -o main $(CPP_SRC) $(INC) -Wall -Wextra