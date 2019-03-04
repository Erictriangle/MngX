#ifndef LOG_HPP
#define LOG_HPP

#include "path_log.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <deque>


namespace mngx
{
class Log
{
private:
  typedef std::deque<std::string> stringDeq;

private:
  Log() = default;
  ~Log() = default;

public:
  static Log* instance();

  friend std::ostream& operator<<(std::ostream& os, Log log);

  void report(const std::string& log);
  void report(const char* log ...);
  const std::string getReport();
  
  void setPath(const std::string& path);

  bool empty();

private:
  stringDeq log;
  PathLog path;
};
}


#endif //LOG_HPP
