#ifndef SCREEN_HPP
#define SCREEN_HPP


#include <iostream>
#include <string>


namespace mngx{
namespace screen{

enum FONT{
  RESET = 0,
  BOLD = 1,
  UNDERSCORE = 4,
  BLINKON = 5,
  NORMAL = 22,
  BLACK = 30,
  RED = 31,
  GREEN = 32,
  YELLOW = 33,
  BLUE = 34,
  MAGENTA = 35,
  CYAN = 36,
  WHITE = 37,
  BBLACK = 40,
  BRED = 41,
  BGREEN = 42,
  BYELLOW = 43,
  BBLUE = 44,
  BMAGENTA = 45,
  BCYAN = 46,
  BWHITE = 47
};

const std::string font(FONT);
const std::string counter(const int now, const int end);

void status();

void help();
void helpConfig();

void incorrectFlag(const std::string& flag);
void wrongArgumentsNumber(const std::string& cmd);
void incorrectSubcommand(const std::string &flag, const std::string& cmd);


} //namespace screen
} //namespace mngx


#endif //SCREEN_HPP
