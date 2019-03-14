#ifndef TAR_COMPRESS_HPP
#define TAR_COMPRESS_HPP

#include <cstdlib>

#include <vector>
#include <string>
#include <iterator>
#include <algorithm>


namespace mngx
{
class TarCompress
{
private:
  typedef std::vector<std::string> stringVec;

  //const tar options
  const std::string TAR = "tar";
  const char CREAT    = 'c';  //creat archive file
  const char EXTRACT  = 'x';  //extract from archive
  const char FILE     = 'f';  //specify filename
  //const char VIEW     = 't';  //show archive content
  //const char ADD      = 'r';  //add file to archive
  //const char UPDATE   = 'u';  //update file in archive
  //const char COMPRESS = 'z';  //compress to .gz file
  const char DESTINATION = 'C';
  const std::string EXTENSION = ".tar";

public:
  //constructors and destructor
  TarCompress() = default;
  TarCompress(const TarCompress& tarCompress);
  TarCompress(const std::string& source);
  ~TarCompress() = default;

  template<class BeginIterator, class EndIterator>
    TarCompress(BeginIterator begin, EndIterator end);

  //assignments
  TarCompress& operator=(const TarCompress& tarCompress);
  TarCompress& operator=(const std::string& source);

  //add
  void add(const std::string& source);

  template<class BeginIterator, class EndIterator>
    void add(BeginIterator begin, EndIterator end);

  //archive method
  bool creat(const std::string& destination);

  template<class BeginIterator, class EndIterator>
    bool creat(const std::string& destination, const std::string& packName,
      BeginIterator begin, EndIterator end);

  bool extract(const std::string& source);

  void clear();

private:
  stringVec source;

};


template<class BeginIterator, class EndIterator>
TarCompress::TarCompress(BeginIterator begin, EndIterator end)
{
  std::for_each(begin, end, [&](const std::string& str){
    source.push_back(str);
  });
}


template<class BeginIterator, class EndIterator> bool 
TarCompress::creat(
    const std::string& destination, const std::string& packName,
    BeginIterator begin, EndIterator end)
{
  clear();
  std::for_each(begin, end, [&](const std::string& str){
    source.push_back(str);
  });

  std::string command{ TAR + " -" + CREAT + FILE + " "
   + destination + "/" + packName + EXTENSION + " "};
   
  for(auto src : source){
    command += src + " ";
  }
  std::system(command.c_str());

  //TODO - check creat archive is done
  return 1;
}


}


#endif //TAR_COMPRESS_HPP
