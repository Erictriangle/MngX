#include "tar_compress.hpp"

namespace mngx
{

TarCompress::TarCompress(const TarCompress& tarCompress)
  :m_source(tarCompress.m_source)
{
}


TarCompress::TarCompress(const std::string& source)
{
  m_source.push_back(source);
}


template<class BeginIterator, class EndIterator>
TarCompress::TarCompress(BeginIterator begin, EndIterator end)
{
  std::for_each(begin, end, [&](const std::string& str){
    m_source.push_back(str);
  });
}


TarCompress&
TarCompress::operator=(const TarCompress& tarCompress)
{
  m_source = tarCompress.m_source;
  return *this;
}


TarCompress&
TarCompress::operator=(const std::string& source)
{
  m_source.clear();
  m_source.push_back(source);
  return *this;
}


void
TarCompress::add(const std::string& source)
{
  m_source.push_back(source);
}


template<class BeginIterator, class EndIterator> void
TarCompress::add(BeginIterator begin, EndIterator end)
{
  std::for_each(begin, end, [&](const std::string& str){
    m_source.push_back(str);
  });
}


bool
TarCompress::creat(const std::string& destination)
{
  std::string command{ TAR + " " + CREAT + FILE + " "
    + destination + " "};

  for(auto src : m_source){
    command += src + " ";
  }
  std::system(command.c_str());

  //TODO - check creat archive is done
  return 1;
}


template<class BeginIterator, class EndIterator> bool
TarCompress::creat(const std::string& destination,
  BeginIterator begin, EndIterator end)
{
  clear();
  add(begin, end);

  std::string command{ TAR + " " + CREAT + FILE + " "
   + destination + " "};
   
  for(auto src : m_source){
    command += src + " ";
  }
  std::system(command.c_str());

  //TODO - check creat archive is done
  return 1;
}


bool
TarCompress::extract(const std::string& source,
  const std::string& destination = "")
{
  std::string command{ TAR  + " " + EXTRACT + FILE + " " + source
    + " " + destination};

  std::system(command.c_str());

  //TODO - check extract is done
  return 1;
}


void
TarCompress::clear()
{
  m_source.clear();
}


} //namespace mngx
