#ifndef PATH_HPP
#define PATH_HPP

#include <string>

#include <boost/filesystem.hpp>


namespace mngx
{
class Path
{
protected:
  struct
  {
    boost::filesystem::path directory;
    boost::filesystem::path filename;
  } path;

public:
  static bool isFile(const std::string& file);
  static bool isFile(const Path& file);
  static bool isDirectory(const std::string& directory);
  static bool isDirectory(const Path& directory);

  static void creatDirectory(const std::string& directory);
  static void creatDirectory(const Path& directory);

public:
  Path() = default;
  Path(const std::string& path);
  Path(const Path& path);
  ~Path() = default;

  Path& operator=(const std::string& path);
  Path& operator=(const Path& path);
  bool operator==(const Path& path) const;

  virtual void setPath(const std::string& path);
  virtual void setPath(const Path& path);
  virtual const std::string getPath() const;

  const std::string getDirectory() const;
  const std::string getFilename() const;
  const std::string getUsername() const;

  bool empty() const;

protected:
  void clear();

}; //class Path
} //namespace mngx


#endif //PATH_HPP
