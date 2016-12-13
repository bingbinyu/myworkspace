#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include "parser.h"
#include <string.h>
using namespace std;


/*
 * Die Methode die bestimmt wie mit den Signalen umgegangen wird.
 * Sie sollen nur gesammelt werden, es braucht nichts anderes getan werden.
 * @param int - Signalnummer, wird hier nicht benoetigt
 */
static void handel(int){}


/*
 * Gibt den Pfad zu dem uebergebenen Kommando zurueck.
 * @param command - Kommando zu dem der Pfad ermittelt werden soll
 * @return std::string - Pfad zum Kommando, falls das Kommando nicht existiert
 *  wird "" zurueckgegeben.
 */
static string findPathToCommand(char* command){
    // Beginnt das mit Kommando mit '.' oder '/' ist es eine Pfadangabe
    if(command[0] == '.' || command [0] == '/')
        return command;
    else{
        //Holt den Inhalt der environment variable PATH
        char* path = getenv("PATH");
        //Position in path
        int ppos = 0;
        while (path[ppos]){

            //Ist das aktuelle Zeichen in path kein '/' ist
            //dieser Eintrag ungueltig und die Schleife kann enden.
            if(path[ppos] != '/') break;

            //String indem der Pfad zum Kommando aufgebaut wird
            string temp = "";
            //position in temp
            int tpos = 0;


            //Solange path nicht am Ende ist und das aktuelle Zeichen nicht das
            // Trennzeichen ':' ist, koennen wir temp weiter aufbauen.
            while(path[ppos] && path[ppos] != ':'){
                temp += path [ppos];
                ppos++;
                tpos++;
            }
            //Es muss noch hinter das ':' gesprungen werden
            ppos +=1;

            //in temp steht jetzt der Path zu einem Directory in der PATH
            DIR* dirStream = opendir(temp.c_str());

            struct dirent* dir;
            //Dieses gilt es jetzt nach unserem kommando zu durchsuchen
            while (((dir = readdir(dirStream))!= NULL)){
                char* dname = dir->d_name;
                //Gibt es dieses kann '/' und das Kommando an temp gehangen
                //werden und wir erhalten unseren Pfad zum Kommando
                if (strcmp(dname, command)== 0){
                    temp += '/';
                    temp += command;
                    closedir(dirStream);
                    return temp;
                }
            }

        }
        //Das Kommando existiert nicht
        return "";
    }
}


/*
 * Setzt den Signalhandler
 */
static void setUpSigHandler() {
    // Legt unsere sigaction an
    struct sigaction sigact;
    // Setzt die Methode zum umgehen mit Signalen auf handel()
    sigact.sa_handler = &handel;
    // Setzt den SA_Restart flag
    sigact.sa_flags = SA_RESTART;
    // Die sigaction sigact soll benutzt werden um SIGCHLD Signale zu handeln
    if (sigaction(SIGCHLD, &sigact, NULL) == -1) perror("sigaction: ");
}


int main(){
    setUpSigHandler();
    for (;;){
        struct command cmd = read_command_line();
        cout << "command: " << cmd.argv[0]
	     << ", background: " << (cmd.background ? "ja" : "nein") << endl;
        //Der Pfad zu unserem Kommando
        string path = findPathToCommand(cmd.argv[0]);
        // Ab jetzt brauchen wir Kind- und Vaterprozess
        pid_t pid;
        if ((pid = fork()) == -1){
            perror("fork :");
        }
        if(pid > 0){
            //Der Vaterprozess muss auf die Terminierung seines Kindes warten,
            //falls dieses nicht im Hintergrund ausgefuehrt werden soll.
            if(cmd.background==0){pause();}

        } else if (pid == 0){
            //Der Kindprozess muss nur noch das Kommando ausfuehren
            if ((execv(path.c_str(), cmd.argv)) == -1){
                perror("execv: ");
            }
        } else {
            cerr << "Fork failed!" << endl;
        }
    }
}