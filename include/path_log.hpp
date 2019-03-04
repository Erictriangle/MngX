#ifndef PATH_LOG_HPP
#define PATH_LOG_HPP

#include "path.hpp"


namespace mngx
{
class PathLog : public Path
{
private:
  const std::string HOME = "/home/";
  const std::string FOLDER = ".mngx";
  const std::string FILENAME = "MngLog";
  const std::string EXTENSION = ".txt";

public:
  PathLog();
  PathLog(const std::string& path);
  PathLog(const PathLog& path);
  ~PathLog() = default;

  PathLog& operator=(const std::string& path);
  PathLog& operator=(const PathLog& path);
  bool operator==(const PathLog& path) const;

  virtual void setPath(const std::string& path) override;
  virtual void setPath(const Path& path) override;
  virtual const std::string getPath() const override;

  const std::string getDefaultPath() const;
  const std::string getDefaultDirectory() const;
  const std::string getDefaultFilename() const;
  
  bool empty() const;
    
private:
  void setDefult();
};
} //namespace mngx


#endif //PATH_LOG_HPP