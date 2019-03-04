#ifndef PATH_CONFIG_HPP
#define PATH_CONFIG_HPP

#include "path.hpp"


namespace mngx
{
class PathConfig : public Path
{
private:
  const std::string HOME = "/home/";
  const std::string FOLDER = ".mngx";
  const std::string FILENAME = "MngConfig";
  const std::string EXTENSION = ".txt";

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

  const std::string getDefaultPath() const;
  const std::string getDefaultDirectory() const;
  const std::string getDefaultFilename() const;

  bool empty() const;

private:
  void setDefault();

}; //PathConfig
} //namespace mngx


#endif //PATH_CONFIG_HPP
