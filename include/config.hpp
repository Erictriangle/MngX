#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "path_config.hpp"

#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <memory>
#include <algorithm>


namespace mngx{
class Config{
private:
  typedef std::vector<std::string> string_vec;

public:
  enum SECTION{
    GLOBAL = 0
  };

  static const std::map<SECTION, std::string> sectionStringMap;
  static const std::map<std::string, SECTION> stringSectionMap;

public:
  Config() = default;
  Config(const std::string&);
  Config(Config&) = delete;
  ~Config() = default;

  Config& operator=(const std::string&);
  Config& operator=(const PathConfig&);

  void creat();
  void creat(const std::string&);
  void addRow(const SECTION, const std::string&);
  void removeRow(const SECTION, const std::string&);

  string_vec section(const SECTION) const;


private:
  PathConfig m_pathConfig;

  string_vec readAllFile();
  std::unique_ptr<std::ofstream> oFile();
  std::unique_ptr<std::ifstream> iFile() const;

};
} //namespace mngx


#endif //CONFIG_HPP
