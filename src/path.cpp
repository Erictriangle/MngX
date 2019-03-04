#include "path.hpp"

namespace mngx
{

bool
Path::isFile(const std::string& file)
{
  return boost::filesystem::is_regular_file(file);
}


bool
Path::isFile(const Path& file)
{
  return boost::filesystem::is_regular_file(file.path());
}


bool
Path::isDirectory(const std::string& directory
){
  return boost::filesystem::is_directory(directory);
}


bool
Path::isDirectory(const Path& directory)
{
  return boost::filesystem::is_directory(directory.path());
}


void
Path::creatDirectory(const std::string& directory)
{
  boost::filesystem::create_directory(directory);
}


void
Path::creatDirectory(const Path& directory)
{
  boost::filesystem::create_directory(directory.path());
}


Path::Path(const std::string& path)
{
  setPath(path);
}


Path::Path(const std::string& path)
{
  setPath(path);
}


Path&
Path::operator=(const std::string& path)
{
  setPath(path);
  return *this;
}


Path&
Path::operator=(const Path& path)
{
  setPath(path);
  return *this;
}


bool
Path::operator==(const Path& path) const
{
  return (this->path.directory.native() == path.directory.native() &&
      this->path.filename.native() == path.filename.native());
}


void
Path::setPath(const std::string& path)
{
  namespace fs = boost::filesystem;

  auto assignFilename = [&](fs::path& inputPath)->fs::path{
    return (!fs::is_directory(input_path))
    ? inputPath.filename()
    : "";
  }

  auto assignDirectory = [&](fs::path& inputPath)->fs::path{
    return (fs::is_directory(inputPath))
    ? inputPath
    : inputPath.remove_filename();
  }

  clear();
  fs::path inputPath(path);

  if(inputPath.is_absolute()){
    this->path.filename = assignFilename(inputPath);
    this->path.directory = assignDirectory(inputPath);
  }
  else {
    fs::path currentPath = fs::current_path();
    currentPath += "/";
    currentPath += inputPath;
    this->path.filename = assignFilename(currentPath);
    this->path.directory = assignDirectory(currentPath);
  }
}


void
Path::setPath(const Path& path)
{
  this->path.directory = path.getDirectory();
  this->path.filename = path.getFilename();
}


const std::string
Path::getPath() const
{
  if(path.directory.empty()){
    return "";
  }

  return (path.directory.native().back() == '/')
    ? path.directory.native() + path.filename.native()
    : path.directory.native() + '/' + path.filename.native();
}


const std::string
Path::getDirectory() const
{
  return path.directory.native();
}


const std::string
Path::getFilename() const
{
  return path.filename.native();
}


const std::string
Path::getUsername() const
{
  return getenv("USER");
}


bool
Path::empty() const
{
  return path.directory.empty();
}


void
Path::clear()
{
  path.directory.clear();
  path.filename.clear();
}

} //namespace mngx
