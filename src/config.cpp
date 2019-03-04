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
    log->report("Cannot open " + pathConfig.getPath() + "file.");
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
  this->pathConfig = pathConfig;
  return creat();
}


bool
Config::load(const std::string& pathConfig)
{
  this->pathConfig = pathConfig;
  return 1;
}


bool
Config::addRow(const SECTION section, const std::string& row)
{
  auto sectionStr = sectionStringMap.find(section)->second;
  stringVec fileContent = readAllFile();

  if(rowIsRepeat(section, row, fileContent)){
    log->report(row + " in section: " + sectionStr + " is repeat.");
    return 0;
  }

  auto file = oFile();
  if(!file->is_open()){
    log->report("Cannot open " + pathConfig.getPath() + "file.");
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
  stringVec fileContent = readAllFile();

  if(!rowIsRepeat(section, row, fileContent)){
    log->report(row + "does not exist in: " + sectionStr + ".");
    return 0;
  }

  auto file = oFile();
  if(!file->is_open()){
    log->report("Cannot open " + pathConfig.getPath() + "file.");
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
  stringVec fileContent = readAllFile();
  std::string sectionStr = sectionStringMap.find(ARCHIVE)->second;
  
  
  if(!packIsRepeat(ARCHIVE, packName, fileContent)){
    log->report(packName + " does not exist.");
    return 0;
  }

  auto file = oFile();
  if(!file->is_open()){
    log->report("Cannot open " + pathConfig.getPath() + "file.");
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
    fc++;
    while(fc != fileContent.cend() && fc->substr(0,5) != PACK
        && !stringSectionMap.count(*fc)){
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
  stringVec fileContent = readAllFile();
  std::string sectionStr = sectionStringMap.find(ARCHIVE)->second;

  if(repeatInPack(ARCHIVE, packName, path, fileContent)){
    log->report(path + " exist in pack: " + packName + ".");
    return 0;
  }

  auto file = oFile();
  if(!file->is_open()){
    log->report("Cannot open " + pathConfig.getPath() + "file.");
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
  stringVec fileContent = readAllFile();

  if(!repeatInPack(ARCHIVE, packName, path, fileContent)){
    log->report(path + " does not exist in pack: " + packName + ".");
    return 0;
  }

  auto file = oFile();
  if(!file->is_open()){
    log->report("Cannot open " + pathConfig.getPath() + "file.");
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


Config::stringVec
Config::section(const SECTION section) const
{
  std::string sectionStr = sectionStringMap.find(section)->second;
  stringVec sectionContent;
  std::string buffer;
  auto file = iFile();

  while(*file >> buffer && buffer != sectionStr);
  while(*file >> buffer && !stringSectionMap.count(buffer)){
    sectionContent.push_back(buffer);
  }
  return sectionContent;
}


Config::stringVec
Config::readAllFile()
{
  std::string buffer;
  stringVec fileContent;
  auto file = iFile();

  while(*file >> buffer){
    fileContent.push_back(buffer);
  }

  return fileContent;
}



std::unique_ptr<std::ofstream>
Config::oFile()
{
  return std::make_unique<std::ofstream>(pathConfig.getPath(),
    std::ios::trunc);
}


std::unique_ptr<std::ifstream>
Config::iFile() const
{
  return std::make_unique<std::ifstream>(pathConfig.getPath());
}


bool
Config::rowIsRepeat(const SECTION section, const std::string& row,
  const stringVec& fileContent) const
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
    const stringVec& fileContent) const{
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
    const std::string& row, const stringVec& fileContent) const{
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
