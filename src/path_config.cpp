#include "path_config.hpp"


namespace mngx
{

PathConfig::PathConfig()
{
  setDefault();
}


PathConfig::PathConfig(const std::string& path)
{
  setPath(path);
}


PathConfig::PathConfig(const PathConfig& path)
{
  setPath(path);
}


PathConfig&
PathConfig::operator=(const std::string& path)
{
  setPath(path);
  return *this;
}


PathConfig&
PathConfig::operator=(const PathConfig& path)
{
  setPath(path);
  return *this;
}


void
PathConfig::setPath(const std::string& path)
{
  namespace fs = boost::filesystem;

  auto assignFilename = [&](fs::path& inputPath)->fs::path
  {
   if(inputPath.native().back() == '/'){
     return FILENAME + EXTENSION;
   }

    return (!fs::is_directory(inputPath))
      ? inputPath.filename()
      : FILENAME + EXTENSION;
  };

  auto assignDirectory = [&](fs::path& inputPath)->fs::path
  {
    return (fs::is_directory(inputPath))
      ? inputPath
      : inputPath.remove_filename();
  };

  clear();
  fs::path inputPath(path);

  if(inputPath.is_absolute()){
    this->path.filename = assignFilename(inputPath);
    this->path.directory = assignDirectory(inputPath);
  }
  else{
    fs::path currentPath = fs::current_path();
    currentPath += "/";
    currentPath += inputPath;
    this->path.filename = assignFilename(currentPath);
    this->path.directory = assignDirectory(currentPath);
  }
}


void
PathConfig::setPath(const Path& path)
{
  this->path.directory = path.getDirectory();
  this->path.filename = path.getFilename();
}


const std::string
PathConfig::getPath() const
{
  if(path.directory.empty()){
    return "";
  }

  return (path.directory.native().back() == '/')
    ? path.directory.native() + path.filename.native()
    : path.directory.native() + '/' + path.filename.native();
}


const std::string
PathConfig::getDefaultPath() const
{
  std::string username = getenv("USER");
  return HOME + username + "/" + FOLDER + "/" +
    FILENAME + EXTENSION;
}


const std::string
PathConfig::getDefaultDirectory() const
{
  std::string username = getenv("USER");
  return HOME + username + "/" + FOLDER;
}


const std::string
PathConfig::getDefaultFilename() const
{
  return FILENAME + EXTENSION;
}


bool
PathConfig::empty() const
{
  return path.directory.empty();
}


void
PathConfig::setDefault()
{
  std::string username = getenv("USER");
  path.directory = "/home/" + username + "/" + FOLDER;
  path.filename = FILENAME + EXTENSION;
}

} //namespace mngx
