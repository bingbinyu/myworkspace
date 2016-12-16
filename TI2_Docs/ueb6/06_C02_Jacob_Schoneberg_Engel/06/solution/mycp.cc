#include <iostream>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

//own includes
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int fd_in, fd_out;

void signalHandler(int signum) {
    //mapping can no be deleted because size of mapping is unknown. 
    //just close the File Descriptors 
    close(fd_in);
    close(fd_out);

    std::cerr<< signum << " Error in mmap" << std::endl; 
    
    exit(-1); 
}

int main(int argc, char **argv){
  
  //handle Signals from mmap 
  //nach https://docs.oracle.com/cd/E19455-01/806-4750/signals-7/index.html
  signal(SIGSEGV, signalHandler);
  signal(SIGBUS, signalHandler); 
    
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " source destination" << std::endl;
    return -1;
  }
  
  if(strcmp(argv[1],argv[2]) == 0) {
    std::cerr << "source and destination can not be the same" << std::endl;
    return -1;
  }

  //try to open source file
  if ((fd_in = open(argv[1],O_RDONLY)) == -1){
    perror("open fd_in");
    return -1;
  }

  //try to open destination file with Read and Write Permission. 
  // if File does not exits create it
  // if File exits overwrite it 
  if ((fd_out = open(argv[2],O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) == -1){
    close(fd_in);
    perror("open fd_out");
    return -1;
  }
    
  //try to get size of source file
  struct stat attr; 
  if(fstat(fd_in, &attr) == -1) {	
    close(fd_in);
    close(fd_out);
    perror("fstat");
    return -1; 
  }

  int in_size = attr.st_size;
  if(in_size == 0) {
    close(fd_in);
    close(fd_out);
    return 0; 
  }
  
  //try to get size of one Page
  long pagesize = sysconf(_SC_PAGESIZE);
  if(pagesize == -1) {
  	close(fd_in); 
  	close(fd_out);
  	perror("pagesize"); 
  	return -1; 
  }  
     
   //https://gist.github.com/sanmarcos/991042
  // stretch the file size to the size of the (mmapped) array of char 
  // in_size -1 because an additional Nul Char will be added in the next step   
  if (lseek(fd_out, in_size-1, SEEK_SET) == -1) {
      close(fd_out);
      close(fd_in);
      perror("Error calling lseek() to 'stretch' the file");
      return -1;
  }
    
   //https://gist.github.com/sanmarcos/991042
    /* Something needs to be written at the end of the file to
   * have the file actually have the new size.
   * Just writing an empty string at the current file position will do.
   *
   * Note:
   *  - The current position in the file is at the end of the stretched 
   *    file due to the call to lseek().
   *  - An empty string is actually a single '\0' character, so a zero-byte
   *    will be written at the last byte of the file.
   */
  if (write(fd_out, "", 1) == -1) {
      close(fd_out);
      close(fd_in);
      perror("Error writing last byte of the file");
      return -1;
  }
   
  int bytesToWrite = in_size;

  //while not all Bytes have been written
  for(int i = 0; bytesToWrite > 0; i++) {

    //offset needs to be a multiple of the page size 
    int offset = pagesize*i; 
      
    if(bytesToWrite >= pagesize) {
      bytesToWrite -= pagesize; 
    } else {

    	//bytesToWrite < pagesize
    	//not a whole page need to be mapped. 
    	pagesize = bytesToWrite;

    	//bytesToWrite = 0; for loop will be left 
    	bytesToWrite -= bytesToWrite;	
    }
      
    //try to map source file
    char *inmmap = (char*) mmap(NULL,pagesize, PROT_READ, MAP_SHARED, fd_in,offset);
    if(inmmap == MAP_FAILED) {
      close(fd_in); 
      close(fd_out);
      perror("inmmap"); 
      return -1; 
    }

    //try to map destination file
    char *outmmap  = (char*) mmap(NULL, pagesize, PROT_WRITE | PROT_READ, MAP_SHARED, fd_out,offset);
    if(outmmap == MAP_FAILED) {
    	munmap(inmmap,pagesize); 
    	close(fd_in); 
    	close(fd_out);
    	perror("outmmap"); 
    	return -1; 
    }
   
    //do the actual copy
    //for(int j = 0; j<pagesize; j++) {
    //  outmmap[j] =  inmmap[j];
    //}
    memcpy(outmmap, inmmap, pagesize); 
          
    //try to unmap source file
    if(munmap(inmmap, pagesize) ==-1) {
    	munmap(outmmap, pagesize);
    	close(fd_in); 
    	close(fd_out); 
    	perror("unmmap inmmap"); 
    	return -1; 
    } 
      
    //try to unmap destination file
    if(munmap(outmmap, pagesize) ==-1) {
    	munmap(inmmap, pagesize); 
    	close(fd_in); 
    	close(fd_out);
    	perror("unmmap outmmap"); 
    	return -1; 
    } 
  }
   
  //try to sync destination File Descriptor
  if(fsync(fd_out) == -1) {
    close(fd_in); 
    close(fd_out);
    perror("fsync"); 
    return -1; 
  }
  //try to close source File Descriptor
  if(close(fd_in) == -1) {
    close(fd_out);
    perror("close fd_in"); 
    return -1; 
  }
  
  //try to close destination File Descriptor
  if(close(fd_out) == -1) {
    perror("close fd_out"); 
    return -1; 
  }

  return 0;
}
