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
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    char buf[PAGESIZE];
    struct stat stat_in;

    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        return -1;
    }



    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        return -1;
    }

    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    while (offset < stat_in.st_size) {
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED, fd_in,
                                   offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }

        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out,
                                    offset)) == MAP_FAILED) {
            perror("mmap out");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }
        for (int j = 0; map_in[j]; ++j) {
            map_out[j] = map_in[j];
        }
        /*for (int k = 0; buf[k]; ++k) {
            map_out[k] = buf[k];
        }*/
        cout<< map_out<< endl;
        for (int l = 0; map_in[l] && map_out[l] ; ++l) {
            if (map_in[l] != map_out[l]){
                cout << "false" << endl;
            }
        }
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
        }
        msync(map_out, stat_in.st_size, MS_SYNC);
        memset(buf, 0, sizeof(buf));
        offset += PAGESIZE;
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
        }

    }


    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}
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
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    char buf[PAGESIZE];
    struct stat stat_in;

    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        return -1;
    }



    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        return -1;
    }

    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    while (offset < stat_in.st_size) {
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED, fd_in,
                                   offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }

        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out,
                                    offset)) == MAP_FAILED) {
            perror("mmap out");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }
        for (int j = 0; map_in[j]; ++j) {
            map_out[j] = map_in[j];
        }
        /*for (int k = 0; buf[k]; ++k) {
            map_out[k] = buf[k];
        }*/
        cout<< map_out<< endl;
        for (int l = 0; map_in[l] && map_out[l] ; ++l) {
            if (map_in[l] != map_out[l]){
                cout << "false" << endl;
            }
        }
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
        }
        msync(map_out, stat_in.st_size, MS_SYNC);
        memset(buf, 0, sizeof(buf));
        offset += PAGESIZE;
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
        }

    }


    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}
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
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    char buf[PAGESIZE];
    struct stat stat_in;

    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        return -1;
    }



    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        return -1;
    }

    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    while (offset < stat_in.st_size) {
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED, fd_in,
                                   offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }

        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out,
                                    offset)) == MAP_FAILED) {
            perror("mmap out");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }
        for (int j = 0; map_in[j]; ++j) {
            map_out[j] = map_in[j];
        }
        /*for (int k = 0; buf[k]; ++k) {
            map_out[k] = buf[k];
        }*/
        cout<< map_out<< endl;
        for (int l = 0; map_in[l] && map_out[l] ; ++l) {
            if (map_in[l] != map_out[l]){
                cout << "false" << endl;
            }
        }
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
        }
        msync(map_out, stat_in.st_size, MS_SYNC);
        memset(buf, 0, sizeof(buf));
        offset += PAGESIZE;
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
        }

    }


    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}
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
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    char buf[PAGESIZE];
    struct stat stat_in;

    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        return -1;
    }



    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        return -1;
    }

    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    while (offset < stat_in.st_size) {
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED, fd_in,
                                   offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }

        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out,
                                    offset)) == MAP_FAILED) {
            perror("mmap out");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }
        for (int j = 0; map_in[j]; ++j) {
            map_out[j] = map_in[j];
        }
        /*for (int k = 0; buf[k]; ++k) {
            map_out[k] = buf[k];
        }*/
        cout<< map_out<< endl;
        for (int l = 0; map_in[l] && map_out[l] ; ++l) {
            if (map_in[l] != map_out[l]){
                cout << "false" << endl;
            }
        }
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
        }
        msync(map_out, stat_in.st_size, MS_SYNC);
        memset(buf, 0, sizeof(buf));
        offset += PAGESIZE;
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
        }

    }


    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}
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
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    char buf[PAGESIZE];
    struct stat stat_in;

    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        return -1;
    }



    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        return -1;
    }

    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    while (offset < stat_in.st_size) {
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED, fd_in,
                                   offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }

        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out,
                                    offset)) == MAP_FAILED) {
            perror("mmap out");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }
        for (int j = 0; map_in[j]; ++j) {
            map_out[j] = map_in[j];
        }
        /*for (int k = 0; buf[k]; ++k) {
            map_out[k] = buf[k];
        }*/
        cout<< map_out<< endl;
        for (int l = 0; map_in[l] && map_out[l] ; ++l) {
            if (map_in[l] != map_out[l]){
                cout << "false" << endl;
            }
        }
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
        }
        msync(map_out, stat_in.st_size, MS_SYNC);
        memset(buf, 0, sizeof(buf));
        offset += PAGESIZE;
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
        }

    }


    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}
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
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    char buf[PAGESIZE];
    struct stat stat_in;

    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        return -1;
    }



    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        return -1;
    }

    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    while (offset < stat_in.st_size) {
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED, fd_in,
                                   offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }

        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out,
                                    offset)) == MAP_FAILED) {
            perror("mmap out");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }
        for (int j = 0; map_in[j]; ++j) {
            map_out[j] = map_in[j];
        }
        /*for (int k = 0; buf[k]; ++k) {
            map_out[k] = buf[k];
        }*/
        cout<< map_out<< endl;
        for (int l = 0; map_in[l] && map_out[l] ; ++l) {
            if (map_in[l] != map_out[l]){
                cout << "false" << endl;
            }
        }
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
        }
        msync(map_out, stat_in.st_size, MS_SYNC);
        memset(buf, 0, sizeof(buf));
        offset += PAGESIZE;
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
        }

    }


    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}
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
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    char buf[PAGESIZE];
    struct stat stat_in;

    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        return -1;
    }



    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        return -1;
    }

    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    while (offset < stat_in.st_size) {
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED, fd_in,
                                   offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }

        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out,
                                    offset)) == MAP_FAILED) {
            perror("mmap out");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }
        for (int j = 0; map_in[j]; ++j) {
            map_out[j] = map_in[j];
        }
        /*for (int k = 0; buf[k]; ++k) {
            map_out[k] = buf[k];
        }*/
        cout<< map_out<< endl;
        for (int l = 0; map_in[l] && map_out[l] ; ++l) {
            if (map_in[l] != map_out[l]){
                cout << "false" << endl;
            }
        }
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
        }
        msync(map_out, stat_in.st_size, MS_SYNC);
        memset(buf, 0, sizeof(buf));
        offset += PAGESIZE;
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
        }

    }


    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}
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
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    char buf[PAGESIZE];
    struct stat stat_in;

    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        return -1;
    }



    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        return -1;
    }

    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    while (offset < stat_in.st_size) {
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED, fd_in,
                                   offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }

        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out,
                                    offset)) == MAP_FAILED) {
            perror("mmap out");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }
        for (int j = 0; map_in[j]; ++j) {
            map_out[j] = map_in[j];
        }
        /*for (int k = 0; buf[k]; ++k) {
            map_out[k] = buf[k];
        }*/
        cout<< map_out<< endl;
        for (int l = 0; map_in[l] && map_out[l] ; ++l) {
            if (map_in[l] != map_out[l]){
                cout << "false" << endl;
            }
        }
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
        }
        msync(map_out, stat_in.st_size, MS_SYNC);
        memset(buf, 0, sizeof(buf));
        offset += PAGESIZE;
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
        }

    }


    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}
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
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    char buf[PAGESIZE];
    struct stat stat_in;

    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        return -1;
    }



    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        return -1;
    }

    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    while (offset < stat_in.st_size) {
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED, fd_in,
                                   offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }

        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out,
                                    offset)) == MAP_FAILED) {
            perror("mmap out");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }
        for (int j = 0; map_in[j]; ++j) {
            map_out[j] = map_in[j];
        }
        /*for (int k = 0; buf[k]; ++k) {
            map_out[k] = buf[k];
        }*/
        cout<< map_out<< endl;
        for (int l = 0; map_in[l] && map_out[l] ; ++l) {
            if (map_in[l] != map_out[l]){
                cout << "false" << endl;
            }
        }
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
        }
        msync(map_out, stat_in.st_size, MS_SYNC);
        memset(buf, 0, sizeof(buf));
        offset += PAGESIZE;
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
        }

    }


    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}
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
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    char buf[PAGESIZE];
    struct stat stat_in;

    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        return -1;
    }



    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        return -1;
    }

    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    while (offset < stat_in.st_size) {
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED, fd_in,
                                   offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }

        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out,
                                    offset)) == MAP_FAILED) {
            perror("mmap out");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }
        for (int j = 0; map_in[j]; ++j) {
            map_out[j] = map_in[j];
        }
        /*for (int k = 0; buf[k]; ++k) {
            map_out[k] = buf[k];
        }*/
        cout<< map_out<< endl;
        for (int l = 0; map_in[l] && map_out[l] ; ++l) {
            if (map_in[l] != map_out[l]){
                cout << "false" << endl;
            }
        }
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
        }
        msync(map_out, stat_in.st_size, MS_SYNC);
        memset(buf, 0, sizeof(buf));
        offset += PAGESIZE;
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
        }

    }


    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}
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
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    char buf[PAGESIZE];
    struct stat stat_in;

    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        return -1;
    }



    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        return -1;
    }

    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    while (offset < stat_in.st_size) {
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED, fd_in,
                                   offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }

        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out,
                                    offset)) == MAP_FAILED) {
            perror("mmap out");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }
        for (int j = 0; map_in[j]; ++j) {
            map_out[j] = map_in[j];
        }
        /*for (int k = 0; buf[k]; ++k) {
            map_out[k] = buf[k];
        }*/
        cout<< map_out<< endl;
        for (int l = 0; map_in[l] && map_out[l] ; ++l) {
            if (map_in[l] != map_out[l]){
                cout << "false" << endl;
            }
        }
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
        }
        msync(map_out, stat_in.st_size, MS_SYNC);
        memset(buf, 0, sizeof(buf));
        offset += PAGESIZE;
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
        }

    }


    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}
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
    int offset = 0;
    int fd_in, fd_out;
    char* map_in, *map_out;
    char buf[PAGESIZE];
    struct stat stat_in;

    if((fd_in = open(argv[1], O_RDONLY)) == -1){
        perror("open in");
        return -1;
    }
    if (fstat(fd_in, &stat_in) == -1){
        perror("fstat");
        return -1;
    }



    if((fd_out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
        perror("open out");
        return -1;
    }

    if (lseek(fd_out, stat_in.st_size-1, SEEK_SET) == -1){
        close(fd_out);
        perror("lseek");
        return -1;
    }

    if (write(fd_out, "", 1)!= 1){
        close(fd_out);
        perror("write");
        return -1;
    }

    if (lseek(fd_out, 0, SEEK_SET) == -1){
        perror("lseek");
    }

    while (offset < stat_in.st_size) {
        if ((map_in = (char *) mmap(NULL, PAGESIZE, PROT_READ, MAP_SHARED, fd_in,
                                   offset)) == MAP_FAILED) {
            perror("mmap in");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }

        if ((map_out = (char *) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out,
                                    offset)) == MAP_FAILED) {
            perror("mmap out");
            if (close(fd_in) == -1) {
                perror("close in");
            }
            if (close(fd_out) == -1) {
                perror("close out");
            }
            if (munmap(map_in, PAGESIZE) == -1){
                perror("munmap in");
            }
            return -1;
        }
        for (int j = 0; map_in[j]; ++j) {
            map_out[j] = map_in[j];
        }
        /*for (int k = 0; buf[k]; ++k) {
            map_out[k] = buf[k];
        }*/
        cout<< map_out<< endl;
        for (int l = 0; map_in[l] && map_out[l] ; ++l) {
            if (map_in[l] != map_out[l]){
                cout << "false" << endl;
            }
        }
        if (munmap(map_in, PAGESIZE) == -1){
            perror("munmap in");
        }
        msync(map_out, stat_in.st_size, MS_SYNC);
        memset(buf, 0, sizeof(buf));
        offset += PAGESIZE;
        if (munmap(map_out,PAGESIZE)== -1){
            perror("munmap out");
        }

    }


    if (close(fd_in) == -1) {
        perror("close in");
    }
    if (close(fd_out) == -1) {
        perror("close out");
    }
    return 0;
}

