#include <stdio.h>
#include <stdlib.h>

unsigned long factorial(unsigned long n) {
  unsigned long result = 1;
  while (n) {
    result *= n--;
  }
  return result;
}

int main(int argc, char **argv) {
  unsigned long n = (argc > 1) ? strtol(argv[1], NULL, 10) : 0;

  printf("factorial(%lu) = %lu\n", n, factorial(n));
  return 0; 
}
