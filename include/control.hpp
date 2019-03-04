#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "path.hpp"
#include "path_config.hpp"
#include "config.hpp"
#include "screen.hpp"

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

  typedef std::deque<std::string> stringDeq;
  typedef std::deque<command> commandDeq;

public:
  enum CTRL_COMMAND{
    //flag
    UNKNOWN_COMMAND = 0,
    HELP = 1,
    CONFIG = 2,
    ARCHIVE = 3,

    //subcommand
    CREAT = 100,
    ADD = 101,
    REMOVE = 102,
    LOAD = 103,

    //config subcommand
    ADD_ROW = 200,
    REMOVE_ROW = 201,
    CREAT_PACK = 202,
    REMOVE_PACK = 203,
    ADD_DIRECTORY = 204,
    REMOVE_DIRECTORY = 205

    //archive subcommand

  };

private:
  static const std::map<std::string, CTRL_COMMAND> flagMap;
  static const std::map<std::string, CTRL_COMMAND> helpMap;
  static const std::map<std::string, CTRL_COMMAND> configMap;

public:
  static bool execCommand(Control& cmd);
  static void execConfigDefault();

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

  static bool execArchive(const stringDeq&, Config&);

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

  void divideInput(const stringDeq& input);
};
} //namespace mngs


#endif //CONTROL_HPP
