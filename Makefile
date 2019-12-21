CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-O2 -std=c++11 
LDFLAGS=
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system

SRCS=snake.cc support.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: snake

snake: $(OBJS)
	$(CXX) $(LDFLAGS) -o snake $(OBJS) $(LDLIBS)

snake.o: snake.cc support.hh

support.o: support.hh support.cc

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) snake
