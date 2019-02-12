#include "path_backup.hpp"


namespace mngx{

PathBackup::PathBackup(const std::string& n_path){
  path(n_path);
}


PathBackup::PathBackup(const PathBackup& n_path){
  path(n_path);
}


void
PathBackup::path(const std::string& n_path){
  namespace fs = boost::filesystem;

  auto assignFilename = [&](fs::path& inputPath)->fs::path{
    return (!fs::is_directory(inputPath))
      ? inputPath.filename()
      : "";
  };

  auto assignDirectory = [&](fs::path& inputPath)->fs::path{
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
PathBackup::path(const Path& n_path){
  m_path.directory = n_path.directory();
  m_path.filename = n_path.filename();
}


const std::string
PathBackup::path() const{
  if(m_path.directory.empty())
    return "";

  return (m_path.directory.native().back() == '/')
    ? m_path.directory.native() + m_path.filename.native()
    : m_path.directory.native() + '/' + m_path.filename.native();
}


} //namespace mngx
