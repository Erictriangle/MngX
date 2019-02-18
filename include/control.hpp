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


namespace mngx{
class Control{
private:
  struct s_command{
    std::string flag;
    std::deque<std::string> arguments;
  };

  typedef std::deque<std::string> string_deq;
  typedef std::deque<s_command> command_deq;

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
  static bool execCommand(Control&);
  static void execConfigDefault();

private:
  static bool execHelp(const string_deq&);

  static bool execConfig(const string_deq&);
  static bool execConfigCreat(const string_deq&);
  static bool execConfigLoad(const string_deq&);
  static bool execConfigAddRow(const string_deq&);
  static bool execConfigRemoveRow(const string_deq&);
  static bool execConfigCreatPack(const string_deq&);
  static bool execConfigRemovePack(const string_deq&);
  static bool execConfigAddDirectory(const string_deq&);
  static bool execConfigRemoveDirectory(const string_deq&);

  static bool execArchive(const string_deq&, Config&);

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

  s_command command();
  bool command(const int argc, char** argv);
  bool command(const std::string& input);
  bool command(const Control& control);

  std::string incorrect();
  bool status() const;
  bool empty() const;
  void clear();

private:
  command_deq m_commands;
  std::string m_incorrect;

  void divideInput(const string_deq& input);
};
} //namespace mngs


#endif //CONTROL_HPP
