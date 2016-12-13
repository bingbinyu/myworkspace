LINK.o=$(LINK.cc)
CC=gcc
CXX=g++
CPPFLAGS=
CXXFLAGS=-g -Wall -Wextra
LDLIBS=
SRCS=$(wildcard *.cc)
CXXFLAGS+=-std=c++0x
#CXXFLAGS+=-std=c++14

ti2sh: $(SRCS:%.cc=%.o) r.o parser.h

r.o:	r.l parser.h

clean:
	rm -f *.d *.o ti2sh
