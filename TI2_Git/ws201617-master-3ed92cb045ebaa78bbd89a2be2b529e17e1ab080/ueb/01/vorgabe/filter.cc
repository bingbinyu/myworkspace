#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

#include <iostream>

#include "filter.hh"

TypeMatcher::FileTypes TypeMatcher::filetypes = {
  { 's', S_IFSOCK },
  { 'l', S_IFLNK },
  { 'f', S_IFREG },
  { 'b', S_IFBLK },
  { 'd', S_IFDIR },
  { 'c', S_IFCHR },
  { 'p', S_IFIFO }
};

TypeMatcher::TypeMatcher(const std::string &t) {
  auto i = filetypes.find(t[0]);

  if (i != filetypes.end()) {
    ifmt = i->second;
  } else {
    std::cerr << "Unkown type specifier '" << t << "'" << std::endl;
    ifmt = 0;
  }

  good = ifmt != 0;
}

bool TypeMatcher::matches(const std::string &path) const {
  /* Eintrag fuer path mit ifmt vergleichen */
}

bool FilenameMatcher::matches(const std::string &path) const {
  /* Eintrag fuer path mit filename vergleichen */
}

NewerMatcher::NewerMatcher(const std::string &filename) {
  good = stat(filename.c_str(), &st) == 0;
}

bool NewerMatcher::matches(const std::string &path) const {
  /* Eintrag fuer path mit modification time in st vergleichen */
}

FindFilter::PredicateTypes FindFilter::types = {
  { "type", FindFilter::Type::TYPE },
  { "name", FindFilter::Type::NAME },
  { "suffix", FindFilter::Type::SUFFIX },
  { "newer", FindFilter::Type::NEWER }
};

FindFilter::~FindFilter() {
  for (auto *i : matchers) {
    delete i;
  }
}

bool FindFilter::add(const std::string &type, const std::string &name) {
  auto t = types.find(type);

  if (t != types.end()) {
    Matcher *matcher = NULL;
    switch (t->second) {
    case FindFilter::Type::TYPE:
      matcher = new (std::nothrow) TypeMatcher(name);
      break;
    case FindFilter::Type::NAME:
      matcher = new (std::nothrow) FilenameMatcher(name);
      break;
    case FindFilter::Type::SUFFIX:
      matcher = new (std::nothrow) SuffixMatcher(name);
      break;
    case FindFilter::Type::NEWER:
      matcher = new (std::nothrow) NewerMatcher(name);
      break;
    default: /* should not happen */
      std::cerr << "internal error: unhandled predicate '" << type << "'" << std::endl;
    }

    if (matcher) {
      matchers.push_back(matcher);
      return true;
    }
  }

  return false;
}

bool FindFilter::matches(const std::string &name) const {
  for (auto i : matchers) {
    if (!*i || !i->matches(name)) {
      return false;
    }
  }

  return true;
}
