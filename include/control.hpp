#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "log.hpp"
#include "path.hpp"
#include "path_config.hpp"
#include "config.hpp"
#include "screen.hpp"
#include "tar_compress.hpp"
#include "network.hpp"

#include <string>
#include <deque>
#include <map>
#include <iterator>
#include <algorithm>

#include <boost/algorithm/string.hpp>


namespace mngx
{
class Control
{
private:
  struct command
  {
    std::string flag;
    std::deque<std::string> arguments;
  };

  typedef std::vector<std::string> stringVec;
  typedef std::deque<std::string> stringDeq;
  typedef std::deque<command> commandDeq;

public:
  enum CTRL_COMMAND{
    //flag
    UNKNOWN_COMMAND,
    HELP,
    CONFIG,
    ARCHIVE,
    NETWORK,

    //subcommand
    CREAT,
    ADD,
    REMOVE,
    LOAD,

    //config subcommand
    ADD_ROW,
    REMOVE_ROW,
    CREAT_PACK,
    REMOVE_PACK,
    ADD_DIRECTORY,
    REMOVE_DIRECTORY,

    //archive subcommand
    EXTRACT,
    UPDATE,

    //network subcommand
    SEND,
    DOWNLOAD,
    CHECK
  };

private:
  static const std::map<std::string, CTRL_COMMAND> flagMap;
  static const std::map<std::string, CTRL_COMMAND> helpMap;
  static const std::map<std::string, CTRL_COMMAND> configMap;
  static const std::map<std::string, CTRL_COMMAND> archiveMap;
  static const std::map<std::string, CTRL_COMMAND> networkMap;

public:
  static bool execCommand(Control& cmd);

private:
  static bool execHelp(const stringDeq& cmd);

  static bool execConfig(const stringDeq& cmd);
  static bool execConfigCreat(const stringDeq& cmd);
  static bool execConfigLoad(const stringDeq& cmd);
  static bool execConfigAddRow(const stringDeq& cmd);
  static bool execConfigRemoveRow(const stringDeq& cmd);
  static bool execConfigCreatPack(const stringDeq& cmd);
  static bool execConfigRemovePack(const stringDeq& cmd);
  static bool execConfigAddDirectory(const stringDeq& cmd);
  static bool execConfigRemoveDirectory(const stringDeq& cmd);

  static bool execArchive(const stringDeq& cmd);
  static bool execArchiveCreat(const stringDeq& cmd);
  static bool execArchiveExtract(const stringDeq& cmd);
  static bool execArchiveUpdate(const stringDeq& cmd);

  static bool execNetwork(const stringDeq& cmd);
  static bool execNetworkDownload(const stringDeq& cmd);

  template<class MAP>
  static CTRL_COMMAND key(const MAP& map, const std::string& key);

public:
  Control() = default;
  Control(const int argc, char** argv);
  Control(const std::string& input);
  Control(const Control& control);
  ~Control() = default;

  Control& operator=(const Control& control);
  Control& operator=(const std::string& cmd);
  Control& operator+=(const Control& control);
  Control& operator+=(const std::string& cmd);

  command getCommand();
  bool setCommand(const int argc, char** argv);
  bool setCommand(const std::string& input);
  bool setCommand(const Control& control);

  std::string getIncorrect();
  bool status() const;
  bool empty() const;
  void clear();

private:
  commandDeq cmdDeq;
  std::string incorrect;
  log::src::logger_mt& logger = mngLog::get();

  void divideInput(const stringDeq& input);
};
} //namespace mngs


#endif //CONTROL_HPP
