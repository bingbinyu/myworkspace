#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include "dirent.h"
#include <vector>

#include "parser.h"

using namespace std;

bool bg = false; 

inline bool is_in_dir(const char* p_dir, char* file_name)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (p_dir)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if(std::string(ent->d_name,strlen(ent->d_name)) == std::string(file_name,strlen(file_name)))
            {
                return true;
            }
        }
        closedir (dir);
    }
    return false;
}

inline int dirExists(const char *path)
{
    struct stat info;
    if(stat( path, &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}

inline std::vector<std::string> split_str(std::string p_str, char regex)
{
    std::vector<std::string> tmp;
    std::string var;
    for(int i = 0; i < p_str.length(); ++i)
    {
        if(p_str.at(i) == regex)
        {
            tmp.push_back(var);
            var.clear();
        }
        else
        {
            var += p_str[i];
        }
    }
    return tmp;
}

void signalHandler( int signum ) {
   if(wait(0) < 0 && bg ) {
     perror ("signalHandler: invalid PID of chlid process");
   }
   return;
}

int main(){
    for (;;){
    struct command cmd = read_command_line();

    // Exits ti2sh
    if(std::string(cmd.argv[0],strlen(cmd.argv[0])) == std::string("exit"))
    {
        std::cout << "Bye!" << std::endl;
        exit(0);
    }

    // Change dir
    if(std::string(cmd.argv[0],strlen(cmd.argv[0])) == std::string("cd"))
    {
        if(dirExists(cmd.argv[1]))
        {
            chdir(cmd.argv[1]);
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                std::cout << cwd << std::endl;
            continue;
        }
        else if(cmd.argv[1] == NULL)
        {
            char* home = getenv("HOME");
            if(home != NULL && dirExists(home))
            {
                chdir(home);
                char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) != NULL)
                    std::cout << cwd << std::endl;
                continue;
            }else
            {
                std::cerr << "Home \"" << home << "\" does not exist!" << std::endl;
            }
        }
        else
        {
            std::cerr << "Directory: " << cmd.argv[1] << " does not exists!" << std::endl;
            continue;
        }
    }

    cout << "command: " << cmd.argv[0]
         << ", background: " << (cmd.background ? "ja" : "nein") << endl;

    /* Hier muesste die Ausfuehrung stehen */
    if(cmd.background == 1) {
        bg = true;
    } else {
      bg = false;
    }

    std::string bin = "/usr/bin/";
    char* env_path = getenv("PATH");
    bool command_found = false;
    std::vector<std::string> paths = split_str(std::string(env_path,strlen(env_path)), ':');
    for(int i = 0; i < paths.size(); i++)
    {
        if(is_in_dir(paths.at(i).c_str(),cmd.argv[0]))
        {
            command_found = true;
            bin = paths.at(i) + "/";
            break;
        }
    }
    if(!command_found)
    {
        std::cerr << "Command not found!" << std::endl;
        continue;
    }
    // ========================
    std::string command = cmd.argv[0];
    std::string pathString = bin + command;
    const char* path = pathString.c_str();

    //nach https://docs.oracle.com/cd/E19455-01/806-4750/signals-7/index.html
    signal(SIGCHLD, signalHandler);
    switch (fork()) {
    case -1:
        perror ("main: fork");
        exit (0);
    case 0:
        return execv(path,cmd.argv);
        break;
    default:
        //child process runs not in background
        //parent process waits until child process finishes
        if(cmd.background == 0) {
            if(wait(0) < 0) {
               perror ("main: invalid PID of chlid process");
            }
        }
         break;
        }
    }
    return 0;
}


