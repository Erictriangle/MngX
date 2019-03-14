#include "tar_compress.hpp"

namespace mngx
{

TarCompress::TarCompress(const TarCompress& tarCompress)
  : source(tarCompress.source)
{
}


TarCompress::TarCompress(const std::string& source)
{
  this->source.push_back(source);
}


TarCompress&
TarCompress::operator=(const TarCompress& tarCompress)
{
  this->source = tarCompress.source;
  return *this;
}


TarCompress&
TarCompress::operator=(const std::string& source)
{
  this->source.clear();
  this->source.push_back(source);
  return *this;
}


void
TarCompress::add(const std::string& source)
{
  this->source.push_back(source);
}


template<class BeginIterator, class EndIterator> void
TarCompress::add(BeginIterator begin, EndIterator end)
{
  std::for_each(begin, end, [&](const std::string& str){
    source.push_back(str);
  });
}


bool
TarCompress::creat(const std::string& destination)
{
  std::string command{ TAR + " " + CREAT + FILE + " "
    + destination + " "};

  for(auto src : source){
    command += src + " ";
  }
  std::system(command.c_str());

  //TODO - check creat archive is done
  return 1;
}


bool
TarCompress::extract(const std::string& source)
{
  std::string command{ TAR  + " -" + EXTRACT + FILE + " " + source
    + " -" + DESTINATION + "/" };

  std::system(command.c_str());

  //TODO - check extract is done
  return 1;
}


void
TarCompress::clear()
{
  source.clear();
}


} //namespace mngx
