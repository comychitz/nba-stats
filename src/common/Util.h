#ifndef __NBA_UTIL_H__
#define __NBA_UTIL_H__

#include <string>
#include <sstream>

namespace nba {

namespace Util {

  template<typename T>
    static std::string toStr(T val) {
      std::stringstream ss;
      ss << val;
      return ss.str();
    }

  static unsigned long strToULong(const std::string &str) {
    std::stringstream ss(str);
    unsigned long val = 0;
    ss >> val;
    return val;
  }

  static std::vector<std::string> tokenize(const std::string &str, 
                                           const std::string &delim) {
    std::vector<std::string> tokens;
    size_t pos = 0, pos2 = std::string::npos;
    while ((pos2 = str.find(delim, pos)) != std::string::npos) {
      tokens.push_back(str.substr(pos, pos2-pos)); 
      pos = pos2+1;
    }
    tokens.push_back(str.substr(pos, pos2-pos));
    return tokens;
  }

};

};

#endif
