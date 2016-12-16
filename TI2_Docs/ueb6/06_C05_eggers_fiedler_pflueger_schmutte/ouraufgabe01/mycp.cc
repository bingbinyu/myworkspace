#include <iostream>
#include <cerrno>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>


#define PAGESIZE sysconf(_SC_PAGESIZE)
using namespace std;
int main(int , char **argv){
    //Legt Variablen an die wir brauchen
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    struct stat stat_in;
    //Oeffnet einzulesendes File
    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    //Holt Stat von eingelsesender Datei um groesse zu haben
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        close(fd_in);
        return -1;
    }


    //Oeffnet inzuschreibende Datei
    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        close(fd_in);
        return -1;
    }
    //Wenn eingelesene Datei leer ist, kann jetzt beendet werden.
    if (stat_in.st_size == 0){
        close(fd_in);
        close(fd_out);
        return 0;
    }

    // Macht inzuschreibende Datei beschreibbar
    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_in);
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_in);
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    cout << "Anzahl Bytes: " << stat_in.st_size << endl;
    //Wenn offset groesser ist als Datei sind wir fertig
    while (offset < stat_in.st_size) {
        // mapped eingelesene Datei in HS
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED,
                                    fd_in, offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }

            return -1;
        }
        // mapped inzuschreibende Datei in HS
        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ |
                PROT_WRITE, MAP_SHARED, fd_out, offset)) == MAP_FAILED) {
            perror("mmap out");

            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            //nach while wird geclosed
            break;
        }
        // Kopiert Inhalt der eingelesenen Datei in inzuschreibende.
        for (int j = 0; map_in[j] && j < PAGESIZE; ++j) {
            map_out[j] = map_in[j];
        }
        // eingelesene Datei kann unmapped werde.
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
            //nach while wird geclosed
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_out, PAGESIZE) == -1){
                perror("munmap out");
            }
            return -1;
        }
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
            //nach while wird geclosed
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            return -1;
        }
        // offset muss um die Pagegroesse erhoeht werden.
        offset += PAGESIZE;
    }

    //Dateien muesson noch geschlossen werden
    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}