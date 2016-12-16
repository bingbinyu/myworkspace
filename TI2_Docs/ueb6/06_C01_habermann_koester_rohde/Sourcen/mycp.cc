#include <iostream>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

//--getFileSize--//
// Check the files size to be abled to read 100 percent
size_t getFilesize(const char* filename) {
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}
//--getFileSize_end--//
//--main--//
int main(int argc, char **argv){
    int fd_in, fd_out;
    size_t offset=0;
    void *data;
    static size_t pagesize = sysconf(_SC_PAGESIZE);

    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " source destination" << std::endl;
      return -1;
    }

    if ((fd_in = open(argv[1],O_RDONLY)) == -1){
      perror("open");
      return -1;
    }

    if ((fd_out = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1){
      close(fd_in);
      perror("open");
      return -1;
    }
//--main_end--//
//--while--//
   size_t filesize = getFilesize(argv[1]);

   while(offset < filesize) {
     if ((filesize-offset) < pagesize) {
            pagesize = filesize-offset;
        }

//--while_end--//
//--load--//
        data=mmap(NULL, pagesize, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd_in, offset);
        if (data == MAP_FAILED)  perror("Mapping failed while mapping");
            write(fd_out, data, pagesize);

        int closed = munmap(data,pagesize);  
            if (closed != 0) perror("unMapping failed");

      offset += pagesize;

    }
//--load_end--//
    fsync(fd_out);
    close(fd_in);
    close(fd_out);

    return 0;
}

