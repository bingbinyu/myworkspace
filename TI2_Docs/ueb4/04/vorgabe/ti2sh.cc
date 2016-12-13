#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

#include "parser.h"

using namespace std;

int main(){
    for (;;){
	struct command cmd = read_command_line();
	
	cout << "command: " << cmd.argv[0]
	     << ", background: " << (cmd.background ? "ja" : "nein") << endl;
	
	/* Hier muesste die Ausfuehrung stehen */
    }
    
    return 0;
}
