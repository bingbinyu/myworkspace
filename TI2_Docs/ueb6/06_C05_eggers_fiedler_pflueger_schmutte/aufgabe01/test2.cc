#include <iostream>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
int main(int argc, char **argv){
    int fd_in, fd_out;
    char buf[1024];
    ssize_t szr;
    bool ok = true;

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

    while (ok && ((szr = read(fd_in, buf, sizeof(buf))) > 0)) {
      ssize_t szw = 0;
      while (szw < szr) {
        if ((szw = write(fd_out, buf, szr)) < 0) {
          perror("write");
          ok = false;
          break;
        } else {
          szr -= szw;
        }
      }
    }

    fsync(fd_out);
    close(fd_in);
    close(fd_out);

    return 0;
}
