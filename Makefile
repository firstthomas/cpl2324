CC = g++

CompileParms = -c -Wall -std=c++11 -O2

OBJS = token.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o token

token.o: token.cc
	$(CC) $(CompileParms)  token.cc