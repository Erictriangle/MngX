#include "path.hpp"

namespace mngx{

bool
Path::isFile(const std::string& file){
  return boost::filesystem::is_regular_file(file);
}


bool
Path::isFile(const Path& file){
  return boost::filesystem::is_regular_file(file.path());
}


bool
Path::isDirectory(const std::string& directory){
  return boost::filesystem::is_directory(directory);
}


bool
Path::isDirectory(const Path& directory){
  return boost::filesystem::is_directory(directory.path());
}


void
Path::creatDirectory(const std::string& n_directory){
  boost::filesystem::create_directory(n_directory);
}


void
Path::creatDirectory(const Path& n_directory){
  boost::filesystem::create_directory(n_directory.path());
}


Path&
Path::operator=(const std::string& n_path){
  path(n_path);
  return *this;
}


Path&
Path::operator=(const Path& n_path){
  path(n_path);
  return *this;
}


const std::string
Path::directory() const{
  return m_path.directory.native();
}


const std::string
Path::filename() const{
  return m_path.filename.native();
}


const std::string
Path::username() const{
  return getenv("USER");
}


bool
Path::empty() const{
  return m_path.directory.empty();
}


void
Path::clear(){
  m_path.directory.clear();
  m_path.filename.clear();
}

} //namespace mngx
