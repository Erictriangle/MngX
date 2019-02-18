#include "tar_compress.hpp"

namespace mngx{

TarCompress::TarCompress(const TarCompress& n_tarCompress)
  :m_source(n_tarCompress.m_source){}


TarCompress::TarCompress(const std::string& n_source){
  m_source.push_back(n_source);
}


template<class BeginIterator, class EndIterator>
TarCompress::TarCompress(BeginIterator begin, EndIterator end){
  std::for_each(begin, end, [&](const std::string& str){
    m_source.push_back(str);
  });
}


TarCompress&
TarCompress::operator=(const TarCompress& n_tarCompress){
  m_source = n_tarCompress.m_source;
  return *this;
}


void
TarCompress::add(const std::string& n_source){
  m_source.push_back(n_source);
}


template<class BeginIterator, class EndIterator> void
TarCompress::add(BeginIterator begin, EndIterator end){
  std::for_each(begin, end, [&](const std::string& str){
    m_source.push_back(str);
  });
}


bool
TarCompress::creat(const std::string& n_destination){
  std::string command{ TAR + " " + CREAT + FILE + " "
   + n_destination + " "};
  for(auto src : m_source)
    command += src + " ";
  std::system(command.c_str());

  //TODO - check creat archive is done
  return 1;
}


template<class BeginIterator, class EndIterator> bool
TarCompress::creat(const std::string& n_destination,
  BeginIterator begin, EndIterator end){
  clear();
  add(begin, end);

  std::string command{ TAR + " " + CREAT + FILE + " "
   + n_destination + " "};
  for(auto src : m_source)
    command += src + " ";
  std::system(command.c_str());

  //TODO - check creat archive is done
  return 1;
}


bool
TarCompress::extract(const std::string& n_source,
  const std::string& n_destination = ""){
  std::string command{ TAR  + " " + EXTRACT + FILE + " " + n_source
    + " " + n_destination};

  std::system(command.c_str());

  //TODO - check extract is done
  return 1;
}


void
TarCompress::clear(){
  m_source.clear();
}


} //namespace mngx
