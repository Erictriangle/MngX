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
  typedef std::vector<std::string> string_vec;

  //const tar options
  const std::string TAR = "tar";
  const char CREAT    = 'c';  //creat archive file
  const char EXTRACT  = 'x';  //extract from archive
  const char FILE     = 'f';  //specify filename
  const char VIEW     = 't';  //show archive content
  const char ADD      = 'r';  //add file to archive
  const char UPDATE   = 'u';  //update file in archive
  const char COMPRESS = 'z';  //compress to .gz file

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
    bool creat(const std::string& destination,
      BeginIterator begin, EndIterator end);

  bool extract(const std::string& source, const std::string& destination);

  void clear();

private:
  string_vec m_source;

};
}


#endif //TAR_COMPRESS_HPP
