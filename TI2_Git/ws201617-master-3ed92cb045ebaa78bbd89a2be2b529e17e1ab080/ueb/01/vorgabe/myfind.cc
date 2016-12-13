#include <sys/types.h>
#include <dirent.h>

#include <cstring>
#include <iostream>
#include <string>

#include "filter.hh"

void process(const std::string &path, const FindFilter &filter) {
  /* Hier muesste von euch die die rekursive Abarbeitung des
   * Verzeichnisses Pfad unter Zuhilfenahme von filter erfolgen.
   */
}

/* Ab hier keine Aenderungen noetig. */
int main(int argc, char **argv) {
  const char *path = NULL;
  class FindFilter filter;

  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " path [predicate....]" << std::endl;
    return -1;
  }

  /* store pointer to path for later use */
  path = argv[1];

  /* Skip cmd name and first argument (path) */
  argc -= 2;
  argv += 2;

  /* parse arguments to create match structure */
  while (argc) {
    if (*argv[0] != '-') {
      std::cerr << "option '" << argv[0] << "' not allowed here." << std::endl;
      return -2;
    }

    if (argc < 2 || !filter.add(argv[0] + 1,  argv[1])) {
      std::cerr << "invalid predicate '" << argv[0] + 1 << "'" << std::endl;
      return -3;
    }

    argc -= 2;
    argv += 2;      
  }

  /* process filter recursively on given path and its subdirectories */
  process(path, filter);

  return 0;
}
