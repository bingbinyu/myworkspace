#include <cstdlib>
#include <iostream>

#include "show.hh"
#include "fib.hh"

int main(int argc, char **argv) {
  if (argc > 1) {
    const unsigned long n = strtol(argv[1], NULL, 10);

    for (unsigned long i = 0; i <= n; i++) { 
      show(fib(i));
    }

    std::cout << std::endl;
  }
  return 0;
}
