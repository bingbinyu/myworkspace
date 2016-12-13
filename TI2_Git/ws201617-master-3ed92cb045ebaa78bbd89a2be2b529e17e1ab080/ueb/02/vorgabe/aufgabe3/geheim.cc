#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

const char my_password[] = "TeI2 ist nicht immer einfach, oder?";

static char input_buf[100];

bool set_echo(bool enable) {
  // Taken from http://stackoverflow.com/questions/1413445/reading-a-password-from-stdcin
  struct termios tty;
  tcgetattr(STDIN_FILENO, &tty);
  if (enable)
    tty.c_lflag |= ECHO;
  else
    tty.c_lflag &= ~ECHO;

  return tcsetattr(STDIN_FILENO, TCSANOW, &tty) == 0;
}

bool check_password(const char input[sizeof(input_buf)]) {
  char pass[sizeof(input_buf)];
  bool ok = true;

  /* construct password from pieces */
  memset(pass, 0, sizeof(pass));
  memcpy(pass, my_password, 4);
  pass[4] = '-';
  memcpy(pass+5, my_password + 5, 3);
  pass[8] = '_';
  memcpy(pass+9, my_password + 21, 7);

  for (size_t i = 0; i < sizeof(input_buf); i++) {
    ok = (pass[i] == input[i]) & ok;
  }

  return ok;
}

int main() {
  bool ok = false;

  while (!ok) {
    std::cout << "Bitte das Passwort eingeben: " << std::endl;
    if (!set_echo(false)) {
      std::cerr << "Cannot disable terminal echo, exiting" << std::endl;
      return -1;
    }

    if (!std::cin.getline(input_buf, sizeof(input_buf), '\n')) {
      set_echo(true);
      std::cerr << "Error during input, exiting" << std::endl;
      return -2;
    } else {
      set_echo(true);
    }

    if ((ok = check_password(input_buf))) {
      std::cout << "Das war richtig!" << std::endl;
    } else {
      std::cout << "Leider nein :-(" << std::endl;
    }
  }

  return 0;
}
