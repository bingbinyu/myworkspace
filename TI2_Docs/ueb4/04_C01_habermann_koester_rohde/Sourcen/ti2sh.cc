//--debug--//
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include "parser.h"

using namespace std;

int main(){
    bool debug = false;


  for (;;){
    struct command cmd = read_command_line();


    cout << "command: " << cmd.argv[0]
         << ", background: " << (cmd.background ? "ja" : "nein") << endl;



    pid_t pid = fork();
    bool foldermode = false;
//--debug_end--//

//--foldermode--//
        if (pid < 0) {

            perror("!! ERROR while forking child process !!\n");
            std::_Exit(-1);

        } else {

            if (pid == 0) { //I'm a child

            std::string program = cmd.argv[0];
            std::size_t found = program.find("/");

            char * environment = (char*)"";
            char * current = (char*)"";

            if (found!=std::string::npos) {
                foldermode=true;
                } else {
                environment = getenv("PATH");
                current = strtok(environment, ":");
                }
//--foldermode_end--//

//--checkIfChild--//
            while(current != NULL)
             {
                if (debug) cout << ">>>>>>>>>>>>>> cDEBUG: Hello, I'm the child! My PID is " << pid << endl;

                const char* path;
                std::string target = cmd.argv[0];
                std::string slash = "/";
                if (!foldermode) {
                    std::string konkatenation = current + slash + target;
                    path = konkatenation.c_str();
                    } else {
                   path = target.c_str();
                    }
//--checkIfChild_end--//
//--initPath--//
                if(debug) cout << ">>>>>>>>>>>>>> cDEBUG: Foldermode is " << foldermode << endl;

                if(debug) cout << ">>>>>>>>>>>>>> cDEBUG: Looking for " << path << endl;

                current = strtok(NULL,":");

                int ret;

                ret = execv(path, cmd.argv);
                if (debug) cout << ">>>>>>>>>>>>>> cDEBUG: ret= "<< ret << endl;
                if (ret == -1) { //Execute succeeded
                    if (debug) cout << " >>>>>>>>>>>>>> cDebug: Execution failed: " << path << endl;
                   continue;
                } else {
                   if (debug) cout << " >>>>>>>>>>>>>> cDebug: Execution succeeded: " << path << endl;
                    break;
                }
               }
            } else { // I'm the parent
                if (debug)  cout << ">>>>>>> DEBUG: I'm the parent! Child's PID is " << pid << endl;
            if (cmd.background) {

                while(wait(0) != pid) {}

                }

            }



 }
}
}
//--initPath_end--//
