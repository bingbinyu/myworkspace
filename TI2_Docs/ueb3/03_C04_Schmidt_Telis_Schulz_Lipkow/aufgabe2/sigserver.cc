#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <cerrno>

/* 
 *  Der Signalhandler, der das empfangene Signal "behandelt" und 
 *  die Signalnummer, die Prozess-ID und die User-ID des sendenden
 *  Prozesses ausgibt.
*/
void sighandler(int sig, siginfo_t *siginfo, void *unused) {	
        std::cout << "Signal_number: " << siginfo->si_signo << std::endl;
	std::cout << "Process_ID: " << siginfo->si_pid << std::endl;
	std::cout << "User_ID: " <<  siginfo->si_uid << std::endl;	
}

int main() {
	// Die Struktur des sigaction()-Systemaufrufs
	struct sigaction act;
	
	// Hier wird der Funktion des Signalhandlers gesetzt
	act.sa_sigaction = &sighandler;
	
	/* Hier wird festgelegt, dass sa_sigaction als
         * Signalhandler gesetzt wird
	*/
	act.sa_flags = SA_SIGINFO;
	
	if (sigaction(SIGUSR1, &act, NULL) == -1) {
		std::cerr << strerror(errno) << std::endl;
		return 1;
	}
	
	// Endlosschleife... Warten auf Signal
	std::cout << "Waiting for signal..." << std::endl;
	if(pause() == -1) {
	  std::cerr << strerror(errno) << std::endl;
	}

	return 0;
 }
