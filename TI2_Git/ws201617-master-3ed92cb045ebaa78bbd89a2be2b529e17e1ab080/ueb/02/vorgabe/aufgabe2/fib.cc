#include "fib.hh"

unsigned long fib(unsigned long n) {
  unsigned long r = 1;

  if (n > 1) {
    r = fib(n-2) + fib(n-1);
  }
           
  return r;
}

