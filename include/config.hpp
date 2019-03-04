#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "path_config.hpp"
#include "log.hpp"

#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <memory>
#include <algorithm>


namespace mngx
{
class Config
{
private:
  typedef std::vector<std::string> stringVec;

  const std::string PACK{"PACK-"};

public:
  enum SECTION
  {
    GLOBAL = 0,
    ARCHIVE = 1,
  };

  static const std::map<SECTION, std::string> sectionStringMap;
  static const std::map<std::string, SECTION> stringSectionMap;

private:
  Config() = default;
  ~Config() = default;

public:
  static Config* instance();

  bool creat();
  bool creat(const std::string& pathConfig);
  bool load(const std::string& pathConfig);
  bool addRow(const SECTION section, const std::string& row);
  bool removeRow(const SECTION section, const std::string& row);

  bool creatPack(const std::string& packName);
  bool removePack(const std::string& packName);
  bool addToPack(const std::string& packName, const std::string& path);
  bool removeFromPack(const std::string& packName, const std::string& path);

  stringVec section(const SECTION section) const;

private:
  PathConfig pathConfig;
  Log *log = Log::instance();

  stringVec readAllFile();
  std::unique_ptr<std::ofstream> oFile();
  std::unique_ptr<std::ifstream> iFile() const;

  bool rowIsRepeat(const SECTION section, const std::string& row,
    const stringVec& fileContent) const;
  bool packIsRepeat(const SECTION section, const std::string& packName,
    const stringVec& fileContent) const;
  bool repeatInPack(const SECTION section, const std::string& packName,
    const std::string& row, const stringVec& fileContent) const;

  template<class FILE, class ITERATOR>
    void write(FILE& file, ITERATOR& it, const ITERATOR& end);
};
} //namespace mngx


#endif //CONFIG_HPP
