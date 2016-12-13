#include <stdio.h>
#include <string.h>
#include "signal.h"
#include <unistd.h>







void handle_signal(int signum, siginfo_t *siginfo, void *context );

int main() {

    struct sigaction sigact;

    sigact.sa_flags = SA_SIGINFO;
    sigact.sa_sigaction = handle_signal;

  

    if( sigaction(SIGUSR1,&sigact, NULL) == -1) {
        perror("Error, cannot handle SIGUSR1");
    }
    pause();

    return 0;
}



void handle_signal(int signum, siginfo_t *siginfo, void *context) {
    printf("SIGNAL NUMBER: %i \n",siginfo->si_signo);
    printf("Process ID: %i \n", siginfo->si_pid);
    printf("User ID: %i \n",siginfo->si_uid);

}
