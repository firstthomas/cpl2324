# CC = g++

# CompileParms = -c -Wall -std=c++11 -O2

# OBJS = token.o tree.o parser.o main.o

# Opdr: $(OBJS)
# 	$(CC) $(OBJS) -o main\

# parser.o: parser.cc parser.h token.h tree.h node.h
# 	$(CC) $(CompileParms) parser.cc

# tree.o: tree.cc tree.h
# 	$(CC) $(CompileParms) tree.cc

# token.o: token.cc token.h
# 	$(CC) $(CompileParms) token.cc

# main.o: main.cc token.h parser.h
# 	$(CC) $(CompileParms)  main.cc

# clean:
# 	$(RM) $(OBJS)

CXX=g++
RM=rm -f
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)
SRCS= main.cc parser.cc token.cc tree.cc
OBJS=$(subst .cc,.o,$(SRCS))
all: main
main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main $(OBJS) $(LDLIBS)
main.o: main.cc parser.h tree.h
parser.o: parser.h token.h parser.cc
token.o: token.h token.cc
tree.o: tree.h node.h tree.cc
clean:
	$(RM) $(OBJS)
distclean: clean
	$(RM) main
build: main
	echo finished
run: build
	./main positives.txt