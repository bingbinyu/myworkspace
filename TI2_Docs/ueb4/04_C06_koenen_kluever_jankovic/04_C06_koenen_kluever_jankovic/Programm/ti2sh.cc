#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>

#include "parser.h"

using namespace std;

int main()
{
    for (;;)
      {
	struct command cmd = read_command_line();
	
	if(strcmp(cmd.argv[0], "exit") == 0)
	  {
	     exit(EXIT_SUCCESS);
	  }	
	cout << "command: " << cmd.argv[0]
	     << ", background: " << (cmd.background ? "ja" : "nein") << endl;
	cout << endl;
	/* Hier muesste die Ausfuehrung stehen */
	
	pid_t pid;
	int status=0;
	bool neuerPro = false;
	
	pid=fork();
	
	if(pid == -1)
	  {
	    perror("Fehler!");
	  }
	else if (pid == 0)
	  {
	    char* command = getenv("PATH");
	    char* sub = strtok (command, ":");
	    while(sub != NULL)
	      {
		char s[200]= "";
		strcpy(s,sub);
		strcat(s,"/");
		strcat(s, cmd.argv[0]);
	        struct stat st;
		if( stat(s, &st) == 0)
		  {
		    neuerPro = true;
		    execv(s, cmd.argv);
		  }
		sub = strtok (NULL, ":");
	      }
	    if(!neuerPro)
	      {
		cout << "Sorry aber der Befehl ist Muell!!" << endl;
	      }
	    exit(EXIT_FAILURE);
	  }
	else
	  {
	    pid=wait(&status);
	    while(!WIFEXITED(status) && !WIFSIGNALED(status))
	      {
		pid=wait(0);
	      }
	  }
    }
    return 1;
}
