#include "config.hpp"


namespace mngx
{


const std::map<Config::SECTION, std::string> Config::sectionStringMap
{
  { GLOBAL, "GLOBAL" },
  { ARCHIVE, "ARCHIVE" },
};

const std::map<std::string, Config::SECTION> Config::stringSectionMap
{
  { "GLOBAL", GLOBAL },
  { "ARCHIVE", ARCHIVE },
};


Config*
Config::instance()
{
  static Config instance;
  return &instance;
}


bool
Config::creat()
{
  auto file = oFile();
  if(!file->is_open()){
    return 0;
  }

  for(auto ssm : sectionStringMap){
    *file << ssm.second << "\n";
  }

  return 1;
}


bool
Config::creat(const std::string& pathConfig)
{
  m_pathConfig = pathConfig;
  return creat();
}


bool
Config::load(const std::string& pathConfig)
{
  m_pathConfig = pathConfig;
  return 1;
}


bool
Config::addRow(const SECTION section, const std::string& row)
{
  auto sectionStr = sectionStringMap.find(section)->second;
  string_vec fileContent = readAllFile();
  if(rowIsRepeat(section, row, fileContent)){
    return 0;
  }

  auto file = oFile();
  if(!file->is_open()){
    return 0;
  }

  for(auto fc : fileContent){
    *file << fc << "\n";
    if(fc == sectionStr){
      *file << row << "\n";
    }
  }
  return 1;
}


bool
Config::removeRow(const SECTION section, const std::string& row)
{
  auto sectionStr = sectionStringMap.find(section)->second;
  string_vec fileContent = readAllFile();
  if(!rowIsRepeat(section, row, fileContent)){
    return 0;
  }

  auto file = oFile();
  if(!file->is_open()){
    return 0;
  }

  auto fc = fileContent.cbegin();
  while(*fc != sectionStr){
    write(file, fc, fileContent.cend());
  }
  write(file, fc, fileContent.cend());

  while(*fc != row && !stringSectionMap.count(*fc)) {
    write(file, fc, fileContent.cend());
  }

  if(*fc == row){
    fc++;
  }

  while(fc != fileContent.cend()){
    write(file, fc, fileContent.cend());
  }

  return 1;
}


bool
Config::creatPack(const std::string& packName){
  return addRow(ARCHIVE, PACK + packName);
}


bool
Config::removePack(const std::string& packName){
  string_vec fileContent = readAllFile();
  std::string sectionStr = sectionStringMap.find(ARCHIVE)->second;
  if(!packIsRepeat(ARCHIVE, packName, fileContent)){
    return 0;
  }

  auto file = oFile();
  if(!file->is_open()){
    return 0;
  }

  auto fc = fileContent.cbegin();
  while(*fc != sectionStr){
    write(file, fc, fileContent.cend());
  }
  write(file, fc, fileContent.cend());

  while(*fc != (PACK + packName) && !stringSectionMap.count(*fc)){
    write(file, fc, fileContent.cend());
  }

  if(*fc == (PACK + packName)){
    write(file, fc, fileContent.cend());
    while(fc->substr(0,5) != PACK && !stringSectionMap.count(*fc)){
      fc++;
    }
  }

  while(fc != fileContent.cend()){
    write(file, fc, fileContent.cend());
  }
  return 1;
}


bool
Config::addToPack(const std::string& packName,
  const std::string& path)
{
  string_vec fileContent = readAllFile();
  std::string sectionStr = sectionStringMap.find(ARCHIVE)->second;
  if(repeatInPack(ARCHIVE, packName, path, fileContent)){
    return 0;
  }

  auto file = oFile();
  if(!file->is_open()){
    return 0;
  }

  auto fc = fileContent.cbegin();
  while(*fc != sectionStr){
    write(file, fc, fileContent.cend());
  }
  write(file, fc, fileContent.cend());

  while(*fc != (PACK + packName) && !stringSectionMap.count(*fc)){
    write(file, fc, fileContent.cend());
  }

  if(*fc == (PACK + packName)){
    write(file, fc, fileContent.cend());
    *file << path << "\n";
  }

  while(fc != fileContent.cend()){
    write(file, fc, fileContent.cend());
  }
  return 1;
}


bool
Config::removeFromPack(const std::string& packName,
  const std::string& path)
{
  std::string sectionStr = sectionStringMap.find(ARCHIVE)->second;
  string_vec fileContent = readAllFile();
  if(!repeatInPack(ARCHIVE, packName, path, fileContent)){
    return 0;
  }

  auto file = oFile();
  if(!file->is_open()){
    return 0;
  }

  auto fc = fileContent.cbegin();
  while(*fc != sectionStr){
    write(file, fc, fileContent.cend());
  }
  write(file, fc, fileContent.cend());

  while(*fc != (PACK + packName) && !stringSectionMap.count(*fc)){
    write(file, fc, fileContent.cend());
  }

  if(*fc == (PACK + packName)){
    write(file, fc, fileContent.cend());
    while(*fc != path && !stringSectionMap.count(*fc) && fc->substr(0,5) != PACK){
      write(file, fc, fileContent.cend());
    }

    if(*fc == path){
      fc++;
    }
  }

  while(fc != fileContent.cend()){
    write(file, fc, fileContent.cend());
  }
  return 1;
}


Config::string_vec
Config::section(const SECTION section) const
{
  std::string sectionStr = sectionStringMap.find(section)->second;
  string_vec sectionContent;
  std::string buffer;
  auto file = iFile();

  while(*file >> buffer && buffer != sectionStr);
  while(*file >> buffer && !stringSectionMap.count(buffer)){
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

  while(*file >> buffer){
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


bool
Config::rowIsRepeat(const SECTION section, const std::string& row,
  const string_vec& fileContent) const
{
  auto fc = fileContent.cbegin();
  std::string sectionStr = sectionStringMap.find(section)->second;

  while(fc != fileContent.cend() && *fc != sectionStr){
    fc++;
  }

  if(fc != fileContent.cend()){
    fc++;
  }

  while(fc != fileContent.cend() && *fc != row &&
      !stringSectionMap.count(*fc)){
    fc++;
  }
  return(*fc == row) ? true : false;
}


bool
Config::packIsRepeat(const SECTION section, const std::string& packName,
    const string_vec& fileContent) const{
  auto fc = fileContent.cbegin();
  std::string sectionStr = sectionStringMap.find(section)->second;

  while(fc != fileContent.cend() && *fc != sectionStr){
    fc++;
  }

  if(fc != fileContent.cend()){
    fc++;
  }

  while(fc != fileContent.cend() && *fc != (PACK + packName) &&
    !stringSectionMap.count(*fc)){
    fc++;
  }
  return (*fc == (PACK + packName)) ? true : false;
}


bool
Config::repeatInPack(const SECTION section, const std::string& packName,
    const std::string& row, const string_vec& fileContent) const{
  if(!packIsRepeat(section, packName, fileContent))
    return 0;

  std::string sectionStr = sectionStringMap.find(section)->second;
  auto fc = fileContent.cbegin();

  while(fc != fileContent.cend() && *fc != sectionStr){
    fc++;
  }

  if(fc != fileContent.cend()){
    fc++;
  }

  while(fc != fileContent.cend() && *fc != (PACK + packName)){
    fc++;
  }

  if(fc != fileContent.cend()){
    fc++;
  }

  while(fc != fileContent.cend() && *fc != row &&
      !stringSectionMap.count(*fc) && fc->substr(0,5) != PACK){
    fc++;
  }
  return(*fc == row) ? true : false;
}


template<class FILE, class ITERATOR> void
Config::write(FILE& file, ITERATOR& it, const ITERATOR& end){
  if(it == end){
    return;
  }
  *file << *it << "\n";
  it++;
}


} //namespace mngx
