LINK.o=$(LINK.cc)
CC=gcc
CXX=g++
CPPFLAGS=
CXXFLAGS=-g -Wall -Wextra
LDLIBS=
SRCS=$(wildcard *.cc)
CXXFLAGS+=-std=c++14

ti2sh: ti2sh.o r.o parser.h

ti2sh_signal: ti2sh_signal.o r.o parser.h

r.o:	r.l parser.h

check:	ti2sh
	echo "das check-Skript ist noch nicht fertig"
	(cd checks && ./check-ti2sh)

clean:
	rm -f *.d *.o ti2sh ti2sh_signal
