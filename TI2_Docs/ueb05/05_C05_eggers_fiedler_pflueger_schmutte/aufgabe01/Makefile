CFLAGS=-O0 -Wall -Wextra -std=c11

all: factorial

%.s:	%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -S $< -o $@

.PHONY: clean
clean:
	rm -f *~ *.o core factorial
