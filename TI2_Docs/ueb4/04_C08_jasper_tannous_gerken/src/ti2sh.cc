#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "string.h"
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

#include "parser.h"

using namespace std;

/*
Diese Methode kriegt einen command namen
und sucht durch PATH nach dem entsprechenden Programm ab 
und gibt den absoluten Pfad zum Programm zurueck
   */
char* getPathToExec(const char* cmdname) {

    char *path = getenv("PATH"); 
    char* pathtok = strtok(path, ":");
    char* patharr[100]; 
    int k=0;
    while(pathtok != NULL) {
        pathtok = strtok(NULL, ":");
        patharr[k] = pathtok;
        k++;
    }
    char* finalpath;

    for(int i=0; i< (sizeof(patharr)/sizeof(patharr[0])); ++i ) { 
         asprintf(&finalpath,"%s%s%s", patharr[i], "/",cmdname);
         if(access(finalpath,X_OK) == 0) {
            printf("%s", finalpath);
            return finalpath;
         }
    }
    printf("no command with this name");
    return NULL;
}


void handle_sigchld(int signum, siginfo_t *siginfo, void*) {
    int temp_errno = errno;
    while(waitpid((pid_t)(-1), 0, WNOHANG) > 0) {}
    errno = temp_errno;
}

int main(){
    for (;;){
	struct command cmd = read_command_line();
	cout << "command: " << cmd.argv[0]
	     << ", background: " << (cmd.background ? "ja" : "nein") << endl;
       pid_t pid; 

       //signal handler
       struct sigaction sigact;
       sigact.sa_flags = SA_RESTART;
       sigact.sa_sigaction = &handle_sigchld;



       switch( pid=fork() ) { //fork erzeugt kopie des Prozesses. 
           case -1:
               printf("Fehler bei fork()\n");
               fflush(stdout);
               break;
           case 0: // im Kindprozess
               {
                   const char* completecmd = getPathToExec(cmd.argv[0]);
                   execv(completecmd,cmd.argv); //fuehrt das Programm completecmd im Kindprozess aus
                   fflush(stdout);
                   break;
               }
           default: // im Elternprozess
               if(cmd.background == 0)
                   wait(0);
               else if (sigaction(SIGCHLD, &sigact, NULL) == -1) {
                   perror("Error, cannot handle");
                   exit(1);
               }
               fflush(stdout);
               break;
       }
    }
    return 0;
}



