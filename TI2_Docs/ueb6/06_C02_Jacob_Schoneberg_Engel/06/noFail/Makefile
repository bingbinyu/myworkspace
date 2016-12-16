LINK.o = $(LINK.cc)
CFLAGS= -Wall -Wextra -g -O2 #-pg
CXXFLAGS= -Wall -Wextra -g -O2 #-pg
CXXFLAGS+=-std=c++0x
#CXXFLAGS+=-std=c++11

PROGRAMS:=mycpNoFail

.PHONY: all clean
all: $(PROGRAMS)

clean:
	-$(RM) *~ *.o core $(PROGRAMS)

