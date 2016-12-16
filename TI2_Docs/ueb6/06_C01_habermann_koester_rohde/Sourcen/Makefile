LINK.o = $(LINK.cc)
CFLAGS=-Werror -Wall -Wextra -g -O2 #-pg
CXXFLAGS=-Werror -Wall -Wextra -g -O2 #-pg
CXXFLAGS+=-std=c++0x
#CXXFLAGS+=-std=c++11

PROGRAMS:=mycp

.PHONY: all clean
all: $(PROGRAMS)

clean:
	-$(RM) *~ *.o core $(PROGRAMS)

