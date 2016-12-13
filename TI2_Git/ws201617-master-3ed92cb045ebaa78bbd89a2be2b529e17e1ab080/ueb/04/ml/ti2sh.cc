#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

#include "parser.h"

using namespace std;

/* name of the environment variable that stores the PATH */
#define ENV_PATH   "PATH"

/* a single character used in ENV_PATH as separator */
#define PATH_DELIM ':'

/* pid of a foreground process (the value 0 means that no forground
 * process is being executed */
pid_t fg_child = 0;

/* signal handler function for SIGCHLD. This function checks if the
 * signal was really SIGCHLD and then collects the terminated child
 * process by invoking wait(). When the forground processes has
 * finished, the variable fg_child is reset to zero.
 */
void handle_sigchld(int num,
                    siginfo_t *info,
                    void *context __attribute__((unused))) {
  if (num == SIGCHLD && info->si_code == CLD_EXITED) {
    if (wait(0) == fg_child) {
      fg_child = 0;
    }
  }
}

int main(){
  struct sigaction act;

  /* block SIGTSTP and SIGCONT while handling SIGCHLD */
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_SIGINFO | SA_RESTART;
  act.sa_sigaction = handle_sigchld;

  /* install our own signal handler or exit with error */
  if (sigaction(SIGCHLD, &act, NULL) < 0) {
    std::cerr << "sigaction: cannot set signal handler for SIGCHLD" << std::endl;
    exit(EXIT_FAILURE);
  }

  /* stop running by issuing ^D */
  while (true) {
        command cmd = read_command_line();

        pid_t pid = fork();

	if (pid < 0) {		/* reached on all errors */
	  std::cerr << "fork: " << strerror(errno) << std::endl;
	  continue;
	} else if (pid == 0) { 	/* child process */

	  /* check for absolute path, and give it priority over the
	   * content of PATH */
	  if (strchr(cmd.argv[0],'/')) {
	    execv(cmd.argv[0], cmd.argv);
	  } else {
	    /* only we we didn't get a absolute one try executing a
	     * binary in the search path */

	    char *p = getenv(ENV_PATH);
	    std::string path(p ? p : "");

	    /* used to create the full path of a possible command on the fly */
	    std::string cmd_path;
	    
	    size_t pos = 0, oldpos;

	    do {
	      oldpos = pos;
	      pos = path.find_first_of(PATH_DELIM, oldpos);

	      if (pos == std::string::npos) {
		cmd_path = path.substr(oldpos, pos) + '/' + cmd.argv[0];
	      } else {
		cmd_path = path.substr(oldpos, pos - oldpos) + '/' + cmd.argv[0];
		pos++;
	      }
	      
	      execv(cmd_path.c_str(), cmd.argv);
	      
	    } while (pos != std::string::npos);
	    
          }
	    
	  /* if we reach here, execv() failed for all cases to execute
	   * the command. we reach here _after_ the fork(). so we
	   * should hurry to commit suicide, to prevent doubled-shells
	   * littering around */

	  std::cerr << "execv: " << strerror(errno) << std::endl;
	  exit(EXIT_FAILURE);
	  
	  /* never reached */

	} else {		/* parent process */

	  /* treat foreground process: */
	  if (!cmd.background) {
	    fg_child = pid;

	    /* wait for foreground process to be terminated */
	    while (fg_child) {
	      pause();
	    }
	  } else {
	    fg_child = 0;
	  }
	}
    }

    exit(EXIT_SUCCESS);
}
