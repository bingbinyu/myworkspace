#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <cerrno>
#include <stdio.h>
using namespace std;

/*
 * Die Methode die bestimmt wie mit den Signalen umgegangen wird.
 * @param signr - Die Nummer des eingegangenen Signals
 * @param siginfo - Struktur mit Informationen ueber das eingegangene Signal
 * Der dritte Parameter wird in diesem Fall nicht benoetigt.
 */
static void handel(int signr, siginfo_t* siginfo, void*){
    cout << "Signalnummer: " << signr << endl;
    cout << "Prozess ID: " << siginfo->si_pid << endl;
    cout << "Real User ID: " << siginfo->si_uid << endl;
}

int main() {
    // Legt unsere sigaction an
    struct sigaction sigact;
    // Setzt die Variante sa_sigaction zum Setzen unseres handlers
    sigact.sa_flags = SA_SIGINFO;
    // Setzt die Methode zum umgehen mit Signalen auf handel()
    sigact.sa_sigaction = &handel;
    // Die sigaction sigact soll benutzt werden um SIGUSR1 Signale zu handeln
    if (sigaction(SIGUSR1, &sigact, NULL) == -1) cout << errno << endl;
    // Wartet in einer Endlosschleife auf eingehende Signale
    while (true) {
        pause();
    }
}