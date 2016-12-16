#include <iostream>
#include <cerrno>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void close_fd(int fd) {
  if ( close(fd) == -1 ) {
    perror("closing file descriptor failed");
    exit(1);
  }
}

int main(int argc, char **argv) {
  //Get the system page size
  int page_size = sysconf(_SC_PAGESIZE);
  
  //needed for mmap
  char *buf = NULL;

  //stat struct (needed for file size)
  struct stat source;

  if ( argc > 3 ) {
    std::cout << "Wrong Input" << std::endl;
    std::cout << "Usage: mycp sourceFile destinationFile" << std::endl;
    exit(1);
  }

  //Open the source file
  int source_file;
  if ( (source_file = open(argv[1], O_RDONLY)) == -1 ) {
    perror("open the source file failed");
    exit(1);
  }

  //stat the source file (we need the file size for mapping)
  if ( fstat(source_file, &source) == -1 ) {
    perror("fstat failed");
    close_fd(source_file);
    exit(1);
  }

  //Open the destination file
  int destination_file;
  if ( (destination_file = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR |
				S_IWUSR)) == -1) {
    perror("open the destination file failed");
    close_fd(source_file);
    exit(1);
  }
  
  //Get the file size
  int file_size = source.st_size;

  int bytes_written = 0;


  //store the offset (where mapping should begin from source file)
  int offset = 0;

  //Repeat until we've mapped the whole file
  while ( file_size > 0 ) {

    //Map the file into the  memory
    buf = (char *)mmap(NULL, (size_t)page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE,
		       source_file, offset);

    //Error handling
    if ( buf == MAP_FAILED ) {
      perror("mmap failed");
      close_fd(destination_file);
      close_fd(source_file);
      exit(1);
    }
    
    //write the block of bytes mapped in buf
    bytes_written = write(destination_file, buf, page_size);

    if ( bytes_written == -1 ) {
      perror("writing to destination file failed");
      close_fd(destination_file);
      close_fd(source_file);
      exit(1);
    }

  //substract the block size from the file size (cause we wrote them already)
  file_size = file_size - page_size;

  //add block size to the offset, so we get the remaining bytes
  offset = offset + page_size;
  
  }

  //Close file descriptors
  close_fd(destination_file);
  close_fd(source_file);

  //Unmap the memory
  if ( munmap(buf, page_size) == -1 ) {
    perror("munmap failed");
    exit(1);
  }
  
  return 0;
}
