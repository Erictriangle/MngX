#include "log.hpp"
#include "path_log.hpp"




namespace mngx
{
void log::init()
{
  PathLog pathLog;

  logging::add_file_log(
  keywords::file_name = pathLog.getDefaultPath(),
  keywords::rotation_size = 10 * 1024 * 1024,
  keywords::format = "[%TimeStamp%]: %Message%"   
  );

  logging::add_console_log(
    std::cout, boost::log::keywords::format = ">> %Message%"
  );
}
}