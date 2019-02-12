#ifndef PATH_HPP
#define PATH_HPP

#include <string>

#include <boost/filesystem.hpp>


namespace mngx{
class Path{
protected:
  struct{
    boost::filesystem::path directory;
    boost::filesystem::path filename;
  } m_path;

public:
  static bool isFile(const std::string&);
  static bool isFile(const Path&);
  static bool isDirectory(const std::string&);
  static bool isDirectory(const Path&);

  static void creatDirectory(const std::string&);
  static void creatDirectory(const Path&);

public:
  Path() = default;
  virtual ~Path() = default;

  Path& operator=(const std::string&);
  Path& operator=(const Path&);

  virtual void path(const std::string&) = 0;
  virtual void path(const Path&) = 0;
  virtual const std::string path() const = 0;

  const std::string directory() const;
  const std::string filename() const;
  const std::string username() const;

  bool empty() const;

protected:
  void clear();

}; //class Path
} //namespace mngx


#endif //PATH_HPP
