#include <sys/stat.h>

#include <string>
#include <map>
#include <vector>

class Matcher {
protected:
  bool good = true;
public:
  virtual ~Matcher() {}
  virtual bool matches(const std::string &path) const = 0;
  operator bool() const { return good; };
};

class TypeMatcher : public Matcher {
  typedef std::multimap<char, mode_t> FileTypes;
  static FileTypes filetypes;

  mode_t ifmt;
public:
  TypeMatcher(const std::string &);
  virtual bool matches(const std::string &path) const;
};

class FilenameMatcher : public Matcher {
protected:
  std::string filename;
  char separator;
public:
  FilenameMatcher(const std::string &f, char sep = '/') : filename(f), separator(sep) {}
  virtual bool matches(const std::string &path) const;
};

class SuffixMatcher : public FilenameMatcher {
public:
  SuffixMatcher(const std::string &f) : FilenameMatcher(f, '.') {}
};

class NewerMatcher : public Matcher {
  struct stat st;
public:
  NewerMatcher(const std::string &);
  virtual bool matches(const std::string &path) const;
};




class FindFilter {
  enum class Type { TYPE, NAME, SUFFIX, NEWER };
  typedef std::multimap<std::string, Type> PredicateTypes;
  static PredicateTypes types;

  std::vector<Matcher *> matchers;
public:
  bool add(const std::string &type, const std::string &name);
  bool matches(const std::string &name) const;
  ~FindFilter();
};

