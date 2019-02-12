#ifndef PATH_BACKUP_HPP
#define PATH_BACKUP_HPP

#include "path.hpp"


namespace mngx{
class PathBackup : public Path{
public:
  PathBackup() = default;
  PathBackup(const std::string&);
  PathBackup(const PathBackup&);
  ~PathBackup() = default;

  virtual void path(const std::string&);
  virtual void path(const Path&);
  virtual const std::string path() const;

}; //class PathBackup
} //namespace mngx


#endif //PATH_BACKUP_HPP
