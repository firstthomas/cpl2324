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
	./main < positives.txt