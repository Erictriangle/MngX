#include "config.hpp"


namespace mngx
{

const std::map<Config::SECTION, std::string> Config::sectionStringMap
{
  { GLOBAL, "GLOBAL" }
};

const std::map<std::string, Config::SECTION> Config::stringSectionMap
{
  { "GLOBAL", GLOBAL }
};


Config::Config(const std::string& n_pathConfig)
{
  m_pathConfig = n_pathConfig;
}


Config&
Config::operator=(const std::string& n_pathConfig)
{
  m_pathConfig = n_pathConfig;
  return *this;
}


Config&
Config::operator=(const PathConfig& n_pathConfig)
{
  m_pathConfig = n_pathConfig;
  return *this;
}


void
Config::creat()
{
  auto file = oFile();

  for(auto ssm : sectionStringMap)
  {
    *file << ssm.second << "\n";
  }
}


void
Config::creat(const std::string& n_path)
{
  m_pathConfig = n_path;
  creat();
}


void
Config::addRow(const SECTION section, const std::string& row)
{
  auto sectionStr = sectionStringMap.find(section)->second;
  string_vec fileContent = readAllFile();
  auto file = oFile();

  for(auto fc : fileContent)
  {
    if(fc == sectionStr)
      *file << row;
    *file << fc;
  }
}


void
Config::removeRow(const SECTION section, const std::string& row)
{
  auto sectionStr = sectionStringMap.find(section)->second;
  string_vec fileContent = readAllFile();
  auto file = oFile();

  for(auto it = fileContent.cbegin(); it != fileContent.cend(); it++)
  {
    if(*it == sectionStr)
    {
      while(*it != row)
      {
        *file << *it << '\n';
        it++;
      }
      continue;
    }
    *file << *it << '\n';
  }
}


Config::string_vec
Config::section(const SECTION section) const
{
  auto sectionStr = sectionStringMap.find(section)->second;
  string_vec sectionContent;
  std::string buffer;
  auto file = iFile();

  while(*file >> buffer && buffer != sectionStr);
  while(*file >> buffer && !stringSectionMap.count(buffer))
  {
    sectionContent.push_back(buffer);
  }
  return sectionContent;
}


Config::string_vec
Config::readAllFile()
{
  std::string buffer;
  string_vec fileContent;
  auto file = iFile();

  while(*file >> buffer)
  {
    fileContent.push_back(buffer);
  }
  return fileContent;
}


std::unique_ptr<std::ofstream>
Config::oFile()
{
  return (!m_pathConfig.empty())
    ? std::make_unique<std::ofstream>(m_pathConfig.path(),
        std::ios::trunc)
    : std::make_unique<std::ofstream>(m_pathConfig.defaultPath(),
        std::ios::trunc);
}


std::unique_ptr<std::ifstream>
Config::iFile() const
{
  return (!m_pathConfig.empty())
    ? std::make_unique<std::ifstream>(m_pathConfig.path())
    : std::make_unique<std::ifstream>(m_pathConfig.defaultPath());
}


} //namespace mngx
