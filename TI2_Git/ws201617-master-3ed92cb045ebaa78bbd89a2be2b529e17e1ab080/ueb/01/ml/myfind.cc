#include <sys/types.h>
#include <dirent.h>

#include <cstring>
#include <iostream>
#include <string>
#include <set>

#include "filter.hh"

void process(const std::string &path, const FindFilter &filter) {
  struct stat st;
  static std::set<ino_t> seen;

  if (filter.matches(path)) {
    std::cout << path << std::endl;
  }

  if ((stat(path.c_str(), &st) != 0)
      || !S_ISDIR(st.st_mode)
      || (seen.find(st.st_ino) != seen.end())) {
    return;
  }

  DIR *dir = opendir(path.c_str());
  
  if (!dir) {
    if (errno != ENOTDIR) {
      std::cerr << "opendir: " << strerror(errno) << std::endl;
    }

    return;
  }
  seen.insert(st.st_ino);

  /* have valid dir entry */
  struct dirent *entry;

  errno = 0;
  while ((entry = readdir(dir)) != NULL) {
    /* do not process . and .. as these will lead to endless loops */
    if (entry->d_name[0] == '.') {
      switch (entry->d_name[1]) {
      case '\0': continue;
      case '.': if (entry->d_name[2] == '\0') continue;
      default: ;
      }
    }

    process(path + "/" + entry->d_name, filter);
  }

  closedir(dir);
  seen.erase(st.st_ino);
}
  
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
