#ifndef TAR_COMPRESS_HPP
#define TAR_COMPRESS_HPP

#include <cstdlib>

#include <vector>
#include <string>
#include <iterator>
#include <algorithm>


namespace mngx{
class TarCompress{
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
  TarCompress(const TarCompress&);
  TarCompress(const std::string&);
  ~TarCompress() = default;

  template<class BeginIterator, class EndIterator>
    TarCompress(BeginIterator, EndIterator);

  //assignments
  TarCompress& operator=(const TarCompress&);
  TarCompress& operator=(const std::string&);

  //add
  void add(const std::string&);

  template<class BeginIterator, class EndIterator>
    void add(BeginIterator, EndIterator);

  //archive method
  bool creat(const std::string&);

  template<class BeginIterator, class EndIterator>
    bool creat(const std::string&, BeginIterator, EndIterator);

  bool extract(const std::string&, const std::string&);

  void clear();

private:
  string_vec m_source;

};
}


#endif //TAR_COMPRESS_HPP
