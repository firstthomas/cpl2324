CC = g++

CompileParms = -c -Wall -std=c++11 -O2

OBJS = token.o tree.o parser.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o main\

parser.o: parser.cc parser.h token.h tree.h node.h
	$(CC) $(CompileParms) parser.cc

tree.o: tree.cc tree.h
	$(CC) $(CompileParms) tree.cc

# prefix.o: prefix.cc prefix.h
# 	$(CC) $(CompileParms) prefix.cc

token.o: token.cc token.h
	$(CC) $(CompileParms) token.cc

main.o: main.cc token.h parser.h
	$(CC) $(CompileParms)  main.cc

clean:
	$(RM) $(OBJS)