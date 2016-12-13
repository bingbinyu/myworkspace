#include <iostream>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const long page_size = sysconf(_SC_PAGE_SIZE);

int main(int argc, char **argv){
    int fd_in, fd_out;
    bool ok = true;
    struct stat st;

    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " source destination" << std::endl;
      return -1;
    }

    if ((fd_in = open(argv[1],O_RDONLY)) == -1){
      perror("open");
      return -1;
    }

    if (fstat(fd_in, &st) == -1) {
      perror("fstat");
      close(fd_in);
      return -1;
    }
    if(posix_fadvise(fd_in, 0, 0, POSIX_FADV_SEQUENTIAL)) {
      perror("posix_fadvise");
      return -1;
    }
    
    if (((fd_out = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) < 0)
        || lseek(fd_out, st.st_size - 1, SEEK_SET) < 0) {
      close(fd_in);
      perror("open");
      return -1;
    }
    write(fd_out, "", 1);
    off_t offset = 0;
    while (ok && st.st_size > 0) {
      const size_t length = (st.st_size < page_size) ? st.st_size : page_size;
      void *addr = mmap(nullptr, length, PROT_READ, MAP_PRIVATE, fd_in, offset);
      if (addr == MAP_FAILED) {
        perror("mmap");
        break;
      }

      void *addw = mmap(nullptr, length, PROT_WRITE, MAP_SHARED, fd_out, offset);
      if (addw == MAP_FAILED) {
        munmap(addr, length);
        perror("mmap2");
        break;
      }

      memcpy(addw, addr, length);

      st.st_size -= length;
      munmap(addr, length);
      munmap(addw, length);
      offset += length;
    }
    

    fsync(fd_out);
    close(fd_in);
    close(fd_out);
    
    return 0;
}
