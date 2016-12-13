#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>

#include "parser.h"

using namespace std;

/**
 * In dieser Funktion wird die Umgebungsvariable PATH mittels strtok()
 * in Token aufgeteilt um anschließend in den einzelnen Verzeichnissen 
 * nach dem auszuführenden Kommando zu suchen.
 * Wenn das Kommando gefunden wurde wird es mittels der Bibliotheksfunktion 
 * excev() ausgeführt. 
 *
 */
void process(struct command c) {
          struct command cmd = c;
	  if (strcmp(cmd.argv[0], "cd") == 0) {//kommando cd -> Bibliotheksfunktion
	                                       //chdir() um Arbeitsverzeichnis zu wechseln 
	    if ( chdir(cmd.argv[1] ? cmd.argv[1] : "") == 0) {
	    return;
	  } else {
	    perror("cd failed");
	    return;
	  }
	}
          DIR *directory;
	  struct dirent *file;
	  char *env = getenv("PATH");
	  if (env == NULL) {
	    perror("getenv() failed");
	    exit(1);
	  }
	  char delim = ':';
	  char *paths = strtok(env, &delim);
	  bool executed = false;
	  while ( paths != NULL ) {
	    directory = opendir(paths);

	    while ( (file = readdir(directory)) != NULL) {
	      if (strcmp(file->d_name, cmd.argv[0]) == 0) {
		char slash = '/';
		strncat(paths, &slash, 1);
		strcat(paths, cmd.argv[0]);
		if ( execv(paths, cmd.argv) == -1) {// Kommando ausführen
		  perror("excev() failed");
		  exit(1);
		}
		executed = true;
		break;
	      }

	    }
	    if (executed) {
	      if ( closedir(directory) == -1) {
		perror("closedir() failed");
		exit(1);
	      }
	      break;
	    }
	    paths = strtok(NULL, &delim);
	  }
}

/**
 * Diese Funktion prüft den Zustand der Kindprozesse und sammelt diese ein, wenn sie
 * terminiert sind. Dies geschieht mittels der Systembibliotheksfunktion waitpid() und 
 * der Option WNOHANG (sammle irgendeinen Kindprozess ein).
 */
void check_child_status() {
  while (true) {
    pid_t pid = 0;

    pid = waitpid(-1, 0, WNOHANG);

    if (pid <= 0) {
      break;
    }
  }

}

int main(){
    for (;;){
	struct command cmd = read_command_line();

	if (strcmp(cmd.argv[0], "exit") == 0) {//Wenn exit eingetippt wird,
	                                      //beende das Programm
	  exit(0);
	}
		
	cout << "command: " << cmd.argv[0]
		  << ", background: " << (cmd.background ? "ja" : "nein") << endl;
       
	check_child_status(); //sammle Kindprozesse ein
	
	pid_t pid = fork(); //Kindprozess erzeugen
	
	if (pid == 0) { //Kindprozess
	 
	  process(cmd);
	    
	  
	} else if (pid > 0) { //Vaterprozess

	  if (cmd.background) { //Wenn Kommando in Vordergrund -> Warte auf
	                       //den Kindprozess (Shell blockieren), sonst
	                      //warte nicht (Shell wird nicht blockiert)
	    continue;
	  } else {
	    wait(0);
	  }
	 
	  
	} else { //Fehlerbehandlung
	  perror("fork() Failed");
	  exit(1);
	}
    }
       return 0;
 }



