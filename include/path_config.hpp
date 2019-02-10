#ifndef PATH_CONFIG_HPP
#define PATH_CONFIG_HPP

#include "path.hpp"


namespace mngx
{
class PathConfig : public Path
{
private:
  struct
  {
    boost::filesystem::path directory;
    boost::filesystem::path filename;
  } m_defaultPath;

  const std::string FOLDER = ".mngx";
  const std::string FILENAME = "MngConfig";
  const std::string EXTENSION = ".txt";


public:
  PathConfig();
  PathConfig(const std::string&);
  PathConfig(const PathConfig&);
  ~PathConfig() = default;

  PathConfig& operator=(const std::string&);
  PathConfig& operator=(const PathConfig&);
  bool operator==(const PathConfig&) const;

  virtual void path(const std::string&);
  virtual void path(const Path&);
  virtual const std::string path() const;

  const std::string defaultPath() const;
  const std::string defaultDirectory() const;
  const std::string defaultFilename() const;

  bool empty() const;

private:
  void setDefault();

}; //PathConfig
} //namespace mngx


#endif //PATH_CONFIG_HPP
