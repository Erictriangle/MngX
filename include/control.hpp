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

#include <boost/algorithm/string.hpp>


namespace mngx
{
class Control
{
private:
  struct s_command
  {
    std::string flag;
    std::deque<std::string> arguments;
  };

  typedef std::deque<std::string> string_deq;
  typedef std::deque<s_command> command_deq;

public:
  enum CTRL_COMMAND
  {
    //flag
    UNKNOWN_COMMAND = 0,
    HELP = 1,
    CONFIG = 2,


    //config command
    CREAT = 100,
    LOAD = 101,
    ADD_DIRECTORY = 102,
    REMOVE_DIRECTORY = 103
  };

private:
  static const std::map<std::string, CTRL_COMMAND> flagMap;
  static const std::map<std::string, CTRL_COMMAND> helpMap;
  static const std::map<std::string, CTRL_COMMAND> configMap;

public:
  static void execCommand(Control&, Config&);
  static void execConfigDefault();

private:
  static void execHelp(const string_deq&);
  static void execConfig(const string_deq&, Config&);
  static void execConfigCreat(const string_deq&, Config&);
  static void execConfigLoad(const string_deq&, Config&);
  static void execConfigAddDirectory(const string_deq&, Config&);
  static void execConfigRemoveDirectory(const string_deq&, Config&);

  template<class MAP>
  static CTRL_COMMAND key(const MAP&, const std::string&);

public:
  Control() = default;
  Control(const int argc, char** argv);
  Control(const std::string& input);
  Control(const Control& control);
  ~Control() = default;

  Control& operator=(const Control&);
  Control& operator=(const std::string&);
  Control& operator+=(const Control&);
  Control& operator+=(const std::string&);

  s_command command();
  bool command(const int, char**);
  bool command(const std::string&);
  bool command(const Control&);

  std::string incorrect();
  bool status() const;
  bool empty() const;
  void clear();

private:
  command_deq m_commands;
  string_deq m_incorrects;

  void divideInput(const string_deq&);


};
} //namespace mngs


#endif //CONTROL_HPP
