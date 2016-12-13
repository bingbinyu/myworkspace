CC=g++
CXXFLAGS=-O0 -Wall -Wextra -std=c++11

fib:: main.o fib.o show.o

%.s:	%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -S $< -o $@

