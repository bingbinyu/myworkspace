#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void sig_handler(int signo, siginfo_t *sinfo, void *context)
{
    std::cout << "Signal number: " << signo << "\tProcess ID: " << sinfo->si_pid << "\t User ID: " << sinfo->si_uid << std::endl << std::flush;
}

int main()
{
    struct sigaction a;
    memset(&a,'\0',sizeof(a));
    a.sa_sigaction = &sig_handler;
    a.sa_flags = SA_SIGINFO;
    if (sigaction(SIGUSR1, &a, NULL) < 0) {
        perror ("Could not register Sighandler");
        return 1;
    }
    while(1)
    {
        pause();
    }
    return 0;
}
