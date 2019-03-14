#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "path_config.hpp"
#include "log.hpp"
#include "screen.hpp"

#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <iterator>
#include <memory>
#include <algorithm>
#include <iostream>

//TODO - consistency of the file

namespace mngx
{
class Config
{
private:
  typedef std::list<std::string> strList;
  typedef std::vector<std::string> stringVec;
  const std::string PACK{"PACK-"};

public:
  enum SECTION
  {
    GLOBAL,
    ARCHIVE
  };

  static const std::map<SECTION, std::string> sectionStringMap;
  static const std::map<std::string, SECTION> stringSectionMap;

private:
  Config();
  ~Config();

public:
  static Config* instance();

  bool creat();
  bool creat(const std::string& pathConfig);
  bool creat(const PathConfig& pathConfig);
  bool load(const std::string& pathConfig);
  bool addRow(const SECTION section, const std::string& row);
  bool removeRow(const SECTION section, const std::string& row);

  bool creatPack(const std::string& packName);
  bool removePack(const std::string& packName);
  bool addToPack(const std::string& packName, const std::string& path);
  bool removeFromPack(const std::string& packName, 
      const std::string& path);

  stringVec getSection(const SECTION section) const;
  stringVec getPack(const std::string& packName) const;

private:
  PathConfig pathConfig;
  strList fileContent;
  log::src::logger_mt& logger = mngLog::get();

private:
  bool readEntireFile();
  bool save();

  bool rowIsRepeat(const SECTION section, const std::string& row) const;
  bool repeatInPack(const std::string& packName, const std::string& path) const;

  std::unique_ptr<std::ofstream> oFile();
  std::unique_ptr<std::ifstream> isFile();

  template<class DIR>
   bool creatDirectory(const DIR& dir);
  
  template<class FILE>
    bool fileIsOpen(FILE& file);
  
};


} //namespace mngx


#endif //CONFIG_HPP