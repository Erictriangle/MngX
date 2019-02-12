#include "path_config.hpp"


namespace mngx{

PathConfig::PathConfig(){
  setDefault();
}


PathConfig::PathConfig(const std::string& n_path){
  setDefault();
  path(n_path);
}


PathConfig::PathConfig(const PathConfig& n_path){
  setDefault();
  path(n_path);
}


PathConfig&
PathConfig::operator=(const std::string& n_path){
  path(n_path);
  return *this;
}


PathConfig&
PathConfig::operator=(const PathConfig& n_path){
  m_path = n_path.m_path;
  return *this;
}


bool
PathConfig::operator==(const PathConfig& n_path) const{
  return (this->path().compare(n_path.path())) &&
    (this->defaultPath().compare(n_path.defaultPath()));
}


void
PathConfig::path(const std::string& n_path){
  namespace fs = boost::filesystem;

  auto assignFilename = [&](fs::path& inputPath)->fs::path{
    return (!fs::is_directory(inputPath))
      ? inputPath.filename()
      : FILENAME + EXTENSION;
  };

  auto assignDirectory = [](fs::path& inputPath)->fs::path{
    return (fs::is_directory(inputPath))
      ? inputPath
      : inputPath.remove_filename();
  };

  clear();
  fs::path inputPath(n_path);

  if(inputPath.is_absolute()){
    m_path.filename = assignFilename(inputPath);
    m_path.directory = assignDirectory(inputPath);
  }
  else{
    fs::path currentPath = fs::current_path();
    currentPath += "/";
    currentPath += inputPath;
    m_path.filename = assignFilename(currentPath);
    m_path.directory = assignDirectory(currentPath);
  }
}


void
PathConfig::path(const Path& n_path){
  m_path.directory = n_path.directory();
  m_path.filename = n_path.filename();
}


const std::string
PathConfig::path() const{
  if(m_path.directory.empty())
    return "";

  return (m_path.directory.native().back() == '/')
    ? m_path.directory.native() + m_path.filename.native()
    : m_path.directory.native() + '/' + m_path.filename.native();
}


const std::string
PathConfig::defaultPath() const{
  return m_defaultPath.directory.native() + "/" + m_defaultPath.filename.native();
}


const std::string
PathConfig::defaultDirectory() const{
  return m_defaultPath.directory.native();
}


const std::string
PathConfig::defaultFilename() const{
  return m_defaultPath.filename.native();
}


bool
PathConfig::empty() const{
  return m_path.directory.empty();
}


void
PathConfig::setDefault(){
  std::string username = getenv("USER");
  m_defaultPath.directory = "/home/" + username + "/" + FOLDER;
  m_defaultPath.filename = FILENAME + EXTENSION;
}

} //namespace mngx
