#include "path_log.hpp"


namespace mngx
{

PathLog::PathLog()
{
  setDefault();
}


PathLog::PathLog(const std::string& path)
{
  setPath(path);
}


PathLog::PathLog(const PathLog& path)
{
  setPath(path);
}


PathLog&
PathLog::operator=(const std::string& path)
{
  setPath(path);
  return *this;
}


PathLog&
PathLog::operator=(const PathLog& path)
{
  setPath(path);
  return *this;
}


bool
PathLog::operator==(const PathLog& path) const
{
  return (this->path.directory.native() == path.directory.native() &&
      this->path.filename.native() == path.filename.native());
}


void
PathLog::setPath(const std::string& path) override
{
  namespace fs = boost::filesystem;

  auto assignFilename = [&](fs::path& inputPath)->fs::path
  {
    return (!fs::is_directory(inputPath))
      ? inputPath.filename()
      : FILENAME + EXTENSION;
  };

  auto assignDirectory = [](fs::path& inputPath)->fs::path
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
PathLog::setPath(const PathLog& path)
{
  this->path.directory = path.directory();
  this->path.filename = path.filename();
}


const std::string
PathLog::getPath() const
{
  if(path.directory.empty()){
    setDefault();
    return getPath();
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
PathConfig::defaultFilename() const
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