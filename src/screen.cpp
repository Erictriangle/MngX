#include "screen.hpp"


namespace mngx
{

const std::string
screen::font(FONT number = RESET)
{
  return "\u001b[" + std::to_string(number) + "m";
}


const std::string
screen::counter(const int now, const int end)
{
  std::string hash('#', now);
  std::string dash('-', (end-now));
  return "[" + hash + dash + "]";
}


void
screen::status()
{
  std::cout << "  [ MngX ] \n";
  std::cout << "\n";
  std::cout << "Pre-alpha; \n\n";
  std::cout << "type [mgnx -h | --help] from more information.\n";
}


void
screen::help()
{
  std::cout << "usage: mngx [-f | --flag] <arg1 arg2 ...>\n";
  std::cout << "\n";
  std::cout << "\n";
  std::cout << "Flags:\n";
  std::cout << "  config    = manage config file;\n";
  std::cout << "  archive   = archive your data;\n";
  std::cout << "\n";
  std::cout << "-h | --help <flag> for more information.\n";
}


void
screen::helpConfig()
{
    std::cout << "usage: -c | --config <arg1 arg2 ...>\n";
    std::cout << "\n";
    std::cout << "Commands:\n";
    std::cout << "  creat <path>              = creat default our custom config file\n";
    std::cout << "  load <path>               = load existing config file;\n";
    std::cout << "  add-row <option value>    = add new option to config file;\n";
    std::cout << "  remove-row <option value> = remove existing option from you'r\n";
    std::cout << "                              config file;\n";
    std::cout << "  creat-pack <name>         = creat new pack if not exist;\n";
    std::cout << "  remove-pack <name>        = remove pack if exist;\n";
    std::cout << "  add-directory <pack path ...>\n";
    std::cout << "                            = add new directory to exist pack;\n";
    std::cout << "  remove-directory <pack path ...>\n";
    std::cout << "                            = remove directory from exist pack;\n";
    std::cout << "\n";
    std::cout << "\n";
}


void
screen::incorrectFlag(const std::string& flag)
{
    std::cout << font(screen::RED) << flag <<
      font() << " is incorrect flag.\n\n";
    std::cout << "Use -h | --help if you need help.\n";
    std::cout << "\n";
}


void
screen::wrongArgumentsNumber(const std::string& cmd)
{
    std::cout << "Wrong number of arguments for  " <<
      font(RED) << font(BOLD) << cmd << font() << " flag;\n\n";
    std::cout << "Use -h | --help <flag> if you need help.\n";
    std::cout << "\n";
}


void
screen::incorrectSubcommand(const std::string& flag, const std::string& cmd)
{
    std::cout << font(RED) << font(BOLD) << cmd << font()
      << " is wrong command for " << font(GREEN) << font(BOLD) << flag
      << font() << " flag.\n\n";
    std::cout << "Use -h | --help " << flag << " if you need help.\n";
    std::cout << "\n";
}

} //namespace mngx
