CC = g++

CompileParms = -c -Wall -std=c++11 -O2

OBJS = token.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o main

token.o: token.cc token.h
	$(CC) $(CompileParms) token.cc

main.o: main.cc token.h
	$(CC) $(CompileParms)  main.cc