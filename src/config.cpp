#include "config.hpp"


//TODO - check fc is correct

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


Config::Config()
{
  if(!Path::isDirectory(pathConfig.getDefaultDirectory())){
    Path::creatDirectory(pathConfig.getDefaultDirectory());
  }

  if(!Path::isFile(pathConfig.getDefaultPath())){
    if(!creat()){
      BOOST_LOG(logger) << "-=[ ERROR ]=- Cannot creat default config file.";
      throw;
    }
  }
  else{
    readEntireFile();
  }
}


Config::~Config()
{
  save();
}


bool
Config::creat()
{
  if(Path::isFile(pathConfig.getPath())){
    BOOST_LOG(logger) << "Cannot creat " << pathConfig.getPath() 
        << " file. File currently exists.";
    return 0;
  }
  
  if(!creatDirectory(pathConfig.getDirectory())){
    return 0;
  }

  auto file = oFile();
  if(!fileIsOpen(*file)){
    return 0;
  }

  for(auto ssm : sectionStringMap){
    *file << ssm.second << "\n";
  }

  file->close();
  return readEntireFile();
}


bool 
Config::creat(const std::string& pathConfig)
{
  if(!save()){
    return 0;
  }

  this->pathConfig = pathConfig;
  return creat();
}


bool
Config::creat(const PathConfig& pathConfig)
{
  if(!save()){
    return 0;
  }

  this->pathConfig = pathConfig.getPath();
  return creat();
}


bool
Config::load(const std::string& pathConfig)
{
  if(!save()){
    return 0;
  }
  
  this->pathConfig = pathConfig;
  return readEntireFile();
}


bool 
Config::addRow(const SECTION section, const std::string& row)
{
  if(rowIsRepeat(section, row)){
    BOOST_LOG(logger) << row << " is repeat.";
    return 0;
  }

  auto fc = fileContent.cbegin();
  auto sectionStr = sectionStringMap.find(section)->second;

  while( *fc != sectionStr){
    fc++;
  }
  fileContent.insert(++fc, row);
  return 1;
}


bool
Config::removeRow(const SECTION section, const std::string& row)
{
  if(!rowIsRepeat(section, row)){
    BOOST_LOG(logger) << row << " didn't exist!";
    return 0;
  }

  auto fc = fileContent.cbegin();
  auto sectionStr = sectionStringMap.find(section)->second;

  while(*fc != sectionStr){
    fc++;
  }
  
  while(*fc != row){
    fc++;
  }
  fileContent.erase(fc);

  return 1;
}


bool 
Config::creatPack(const std::string& packName)
{
  if(rowIsRepeat(ARCHIVE, PACK + packName)){
    BOOST_LOG(logger) << packName << " currently exists.";
    return 0;
  }

  auto fc = fileContent.cbegin();
  auto sectionStr = sectionStringMap.find(ARCHIVE)->second;

  while(*fc != sectionStr){
    fc++;
  }
  fileContent.insert(++fc, PACK + packName);
  
  return 1;
}


bool
Config::removePack(const std::string& packName)
{
  if(!rowIsRepeat(ARCHIVE, PACK + packName)){
    BOOST_LOG(logger) << packName << " didn't exists.";
    return 0;
  }

  auto fc = fileContent.cbegin();
  auto current = fc;
  auto sectionStr = sectionStringMap.find(ARCHIVE)->second;

  while(*fc != sectionStr){
    fc++;
  }
  fc++;

  while(*fc != (PACK + packName)){
    fc++;
  }

  do{
    current = fc++;
    fileContent.erase(current);
  }
  while(fc != fileContent.cend() && (fc->substr(0,5) != PACK)
      && !stringSectionMap.count(*fc));
  
  return 1;
}


bool
Config::addToPack(const std::string& packName, const std::string& path)
{
  if(repeatInPack(packName, path)){
    BOOST_LOG(logger) << path << " in " << packName 
        << " currently exists.";
    return 0;
  }

  auto fc = fileContent.cbegin();
  auto sectionStr = sectionStringMap.find(ARCHIVE)->second;

  while(*fc != sectionStr){
    fc++;
  }

  while(*fc != (PACK + packName)){
    fc++;
  }
  fileContent.insert(++fc, path);
  return 1;
}


bool 
Config::removeFromPack(const std::string& packName, const std::string& path)
{
  if(!repeatInPack(packName, path)){
    BOOST_LOG(logger) << path << " in " << packName  
        << " didn't exists.";
    return 0;
  }

  auto fc = fileContent.cbegin();
  auto sectionStr = sectionStringMap.find(ARCHIVE)->second;

  while(*fc != sectionStr){
    fc++;
  }

  while(*fc != (PACK + packName)){
    fc++;
  }

  while(*fc != path){
    fc++;
  }
  fileContent.erase(fc);
  return 1;
}


Config::stringVec
Config::getSection(const SECTION section) const
{
  stringVec temp;
  auto fc = fileContent.cbegin();
  auto sectionStr = sectionStringMap.find(section)->second;
  
  while(*fc != sectionStr){
    fc++;
  }

  while(fc != fileContent.cend() && !stringSectionMap.count(*fc)){
    temp.push_back(*fc);
    fc++;
  }
  return temp;
}


Config::stringVec
Config::getPack(const std::string& packName) const
{
  stringVec temp;
  auto fc = fileContent.cbegin();
  auto sectionStr = sectionStringMap.find(ARCHIVE)->second;

  while(*fc != sectionStr){
    fc++;
  }

  while(*fc != (PACK + packName)){
    fc++;
  }

  while(fc != fileContent.cend() && fc->substr(0,5) != PACK 
      && stringSectionMap.count(*fc)){
    temp.push_back(*fc);
  }
  return temp;
}


bool
Config::readEntireFile()
{
  fileContent.clear();

  std::string buffer;
  auto file = isFile();
  if(!fileIsOpen(*file)){
    return 0;
  }

  while(*file >> buffer){
    fileContent.push_back(buffer);
  }

  if(fileContent.empty()){
    BOOST_LOG(logger) << "-=[ ERROR ]=- The loaded file is empty.";
    return 0;
  }

  return 1;
}


bool 
Config::save()
{
  auto file = oFile();
  if(!fileIsOpen(*file)){
    BOOST_LOG(logger) << "Cannot save file content.";
    return 0;
  }

  for(auto fc : fileContent){
    *file << fc << "\n";
  }
  return 1;
}


bool
Config::rowIsRepeat(const SECTION section, const std::string& row)
{
  auto fc = fileContent.cbegin();
  auto end = fileContent.cend();
  auto sectionStr = sectionStringMap.find(section)->second;

  while(fc != end && *fc != sectionStr){
    fc++;
  }

  if(*fc == sectionStr){
    fc++;
  }

  while(fc != end && *fc != row && !stringSectionMap.count(*fc)){
    fc++;
  }

  return (*fc == row)
    ? 1
    : 0;
}


bool
Config::repeatInPack(const std::string& packName, const std::string& path)
{
  auto fc = fileContent.cbegin();
  auto end = fileContent.cend();
  auto sectionStr = sectionStringMap.find(ARCHIVE)->second;

  while(fc != end && *fc != sectionStr){
    fc++;
  }

  if(*fc == sectionStr){
    fc++;
  }

  while(fc != end && *fc != (PACK + packName)
      && !stringSectionMap.count(*fc)){
    fc++;
  }

  if(*fc == (PACK + packName)){
    fc++;
    while(fc != end && *fc != path && fc->substr(0,5) != PACK 
        && !stringSectionMap.count(*fc)){
      fc++;
    }
    if(*fc == path){
      return 1;
    }
  }
  return 0;
}


std::unique_ptr<std::ofstream> 
Config::oFile()
{
  return std::make_unique<std::ofstream>(pathConfig.getPath(),
      std::ios::trunc);
}


std::unique_ptr<std::ifstream> 
Config::isFile()
{
  return std::make_unique<std::ifstream>(pathConfig.getPath());
}


template<class DIR> bool
Config::creatDirectory(const DIR& dir)
{
  Path::creatDirectory(dir);
  if(!Path::isDirectory(dir)){
    BOOST_LOG(logger) << "-=[ ERROR ]=- Cannot creat " << dir 
        << " directory.";
    return 0;
  }
  return 1;
}


template<class FILE> bool
Config::fileIsOpen(FILE& file)
{
  if(!file.is_open()){
    BOOST_LOG(logger) << "-=[ ERROR ]=- Cannot open/creat " 
        << pathConfig.getPath() << " file.";
    return 0;
  }
  return 1;
}


} //namespace mngx