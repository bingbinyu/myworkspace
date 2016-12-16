#include <string.h>
#include <iostream>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char **argv){
    int fd_in, fd_out;
    struct stat *st;
    st = new struct stat;
    int filesize;
    long pagesize = sysconf(_SC_PAGESIZE);  

    printf("%lu\n", pagesize);

    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " source destination" << std::endl;
      return -1;
    }

    if ((fd_in = open(argv[1],O_RDONLY)) == -1){
      perror("open");
      return -1;
    }
    if(stat(argv[1], st) < 0) {
        close(fd_in);
        perror("couldnt stat file");
        return -1;
    }

    filesize = st->st_size;
    //debug     printf("filesize = %i\n", filesize);

    if ((fd_out = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
      close(fd_in);
      perror("open");
      return -1;
    }



    if(ftruncate(fd_out,filesize) == -1) {
        close(fd_in);
        perror("couldnt truncate dest file");
        return -1;
    }
     
    int staddr = 0; 
    while(staddr < filesize) {
        


        if(filesize - staddr < pagesize) {
            pagesize = filesize - staddr;
        }

        //debug printf("page starts this time at: %i\n", staddr);

        char* inm = (char*) mmap(NULL, pagesize, PROT_READ, MAP_SHARED, fd_in, staddr);
        if (inm == MAP_FAILED) {
            close(fd_in);
            close(fd_out);
            printf("inmap failed map %s\n", strerror(errno));
            return -1;
        }

        char* outm = (char*) mmap(NULL, pagesize, PROT_WRITE | PROT_READ, MAP_SHARED, fd_out, staddr);
        if (outm  == MAP_FAILED) {
            munmap(inm,pagesize);
            close(fd_in);
            close(fd_out);
            printf("outmap failed map %s\n", strerror(errno));    
            return -1;
        }

        memcpy(outm,inm ,pagesize);

        if (munmap(inm,pagesize) == -1) {
            close(fd_in);
            close(fd_out);
            printf("failed inmap unmap %s\n", strerror(errno));
            return -1;
        }

        if (munmap(outm,pagesize) == -1) {
            close(fd_in);
            close(fd_out);
            printf("failed outmap unmap %s\n", strerror(errno));
            return -1;
        }
        
        staddr += pagesize;
    }


    fsync(fd_out);
    close(fd_in);
    close(fd_out);
    
    return 0;
}
