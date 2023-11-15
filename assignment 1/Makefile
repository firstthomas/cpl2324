# CC = g++

# CompileParms = -c -Wall -std=c++11 -O2

# OBJS = token.o parser.o main.o

# Opdr: $(OBJS)
# 	$(CC) $(OBJS) -o main

# parser.o: parser.cc parser.h
# 	$(CC) $(CompileParms) parser.cc

# token.o: token.cc token.h
# 	$(CC) $(CompileParms) token.cc

# main.o: main.cc token.h
# 	$(CC) $(CompileParms)  main.cc

# CC=gcc
CXX=g++
RM=rm -f
# CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)
SRCS= main.cc parser.cc token.cc
OBJS=$(subst .cc,.o,$(SRCS))
all: tool
tool: $(OBJS)
	$(CXX) $(LDFLAGS) -o tool $(OBJS) $(LDLIBS)
tool.o: main.cc parser.h
parser.o: parser.h parser.cc
token.o: token.h token.cc
clean:
	$(RM) $(OBJS)
distclean: clean
	$(RM) tool
build: tool
	echo finished
run: build
	./tool positives.txt
# alternatively:
# ./tool < positives.txt
# if your program reads from the standard input (stdin)