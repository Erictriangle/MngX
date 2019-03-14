#ifndef PATH_CONFIG_HPP
#define PATH_CONFIG_HPP

#include "path.hpp"


namespace mngx
{
class PathConfig : public Path
{
private:
  static const std::string HOME;
  static const std::string FOLDER;
  static const std::string FILENAME;
  static const std::string EXTENSION;

public:
  static const std::string getDefaultPath();
  static const std::string getDefaultDirectory();
  static const std::string getDefaultFilename();

public:
  PathConfig();
  PathConfig(const std::string& path);
  PathConfig(const PathConfig& path);
  ~PathConfig() = default;

  PathConfig& operator=(const std::string& path);
  PathConfig& operator=(const PathConfig& path);
  bool operator==(const PathConfig& path) const;

  virtual void setPath(const std::string& path) override;
  virtual void setPath(const Path& path) override;
  virtual const std::string getPath() const override;

  bool empty() const;

private:
  void setDefault();

}; //PathConfig
} //namespace mngx


#endif //PATH_CONFIG_HPP
