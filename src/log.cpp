#include "log.hpp"


namespace mngx
{

Log*
Log::instance()
{
  static Log instance;
  return &instance;
}


std::ostream&
operator<<(std::ostream& os, Log& log)
{
  while(!log.empty()){
    os << log.getReport() << "\n";
  }
  return os;
}


const std::string 
Log::getReport()
{
  std::string temp;
  if(!log.empty()){
    temp = log.back();
    log.pop_back();
    return temp;
  }
  return "";
}


void
Log::report(const std::string& log)
{
  this->log.push_back(log);

  std::ofstream file(path.getPath(), std::ios::ate);
  file << this->log.back() << "\n";
}


void
Log::setPath(const std::string& path)
{
  this->path = path;
}


bool 
Log::empty()
{
  return log.empty();
}


} //namespace mngx
