#ifndef LOG_HPP
#define LOG_HPP

#include "path_log.hpp"

#include <iostream>

#include <boost/move/utility_core.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/logger.hpp>


BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(mngLog, boost::log::sources::logger_mt)


namespace mngx
{
namespace log
{
namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

void init();

} //namespace log
} //namespace mngx

#endif //LOG_HPP