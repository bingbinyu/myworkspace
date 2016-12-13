#include <iostream>
#include <cerrno>
#include <cstring>
#include <signal.h>
#include <unistd.h>

#define SIGNAL SIGUSR1
#define C(x)   #x

void usr1_handler(int num,
                  siginfo_t *info,
                  void *context __attribute__((unused))) {
  std::cout << "received " << C(SIGNAL) << " (" << num << ")" << std::endl;
  std::cout << "signo: " << info->si_signo << std::endl
            << "sending process: " << info->si_pid << std::endl
            << "with uid: " << info->si_uid << std::endl;
}

int main() {
  struct sigaction act;

  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = usr1_handler;

  if (sigaction(SIGNAL, &act, NULL) < 0) {
    std::cerr << "cannot instantiate " << C(SIGNAL) << " handler: "
              << strerror(errno) << std::endl;
    return -1;
  }

  std::cout << C(SIGNAL) << " handler for process " << getpid()
            << " installed." << std::endl;

  while (true) {
    if ((pause() < 0) && (errno != EINTR)) {
      std::cerr << "E: " << strerror(errno) << std::endl;
      return -2;
    }
  }
  
  return 0;
}
