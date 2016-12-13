#include <signal.h>
#include <iostream>
#include <unistd.h>

void handler(int sig, siginfo_t *act, void *context)
{
  std::cout<<"Signal gefunden!" << std::endl;
  std::cout<<"Nummer " << sig << "  PID: " <<  act->si_pid <<  "  UID: " <<  act->si_uid <<std::endl;
}

int main (void)
{
  struct sigaction sa;
  sa.sa_sigaction= &handler;
  sa.sa_flags = SA_SIGINFO;
  if(sigaction(SIGUSR1, &sa, NULL) != 0)
    {
      std::cout<< "Error!"<<std::endl;
      return -1;
    }
  while(pause())
    {
    }
return 0;
}
