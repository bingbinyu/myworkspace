#include <cstdio>
#include <iostream>
#include <string>

int show(const std::string &s) {
  const char *zeichenkette = s.c_str();
  return printf("%s\n", zeichenkette);
}

int main() {
  (void)show("Hallo");
  return 0;
}
