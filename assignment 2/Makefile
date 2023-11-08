CC = g++

CompileParms = -c -Wall -std=c++11 -O2

OBJS = token.o parser.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o main\

parser.o: parser.cc parser.h token.h tree.h node.h
	$(CC) $(CompileParms) parser.cc

token.o: token.cc token.h
	$(CC) $(CompileParms) token.cc

main.o: main.cc token.h
	$(CC) $(CompileParms)  main.cc