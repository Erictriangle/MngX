#include "screen.h"


void
screen::status(){
    std::cout << "  [ MngX ] \n";
    std::cout << "\n";
    std::cout << "Pre-alpha; \n";
}


//=========
//==HELP==
//=======


void
screen::help(){
    std::cout << "usage: mngx [-h | --help <flag>] [-c | --config <command>]\n";
    std::cout << "            [work in progres]\n"; //In progress
    std::cout << "\n";
    std::cout << "Flags:\n";
    std::cout << "  help      = show help for flag our his commands;\n";
    std::cout << "  config    = manage config file;";
    std::cout << "\n";
}


void
screen::help_config(){
    std::cout << "usage: -c | --config [creat <dir>] [load <dir>] [add-directory <dir>]\n";
    std::cout << "                     [remove-directory <dir>]\n";
    std::cout << "\n";
    std::cout << "Commands:\n";
    std::cout << "  creat            = creat custom config file our creat new;\n";
    std::cout << "  load             = load existing config file;\n";
    std::cout << "  add-directory    = add new directory to config file.\n";
    std::cout << "                     You can choose where directory is stored:\n";
    std::cout << "                       global(default) | text"; //In progres
    std::cout << "  remove-directory = remove directory from config file.\n";
    std::cout << "                     You can choose where directory is stored\n";
    std::cout << "                     (look add-directory).\n";
    std::cout << "\n";
    std::cout << "You must load config file manualy for now.\n";
    std::cout << "You use last config file you load.";
    std::cout << "\n";
}


//==========
//==INPUT==
//========

    
void
screen::incorrect_flag(const std::string& flag){
    std::cout << flag << " is wrong flag.\n";
    std::cout << "Use -h | --help if you need help.\n";
    std::cout << "\n";
}


void
screen::wrong_arguments_number(const std::string& cmd){
    std::cout << "Wrong number of arguments for  " << cmd << " flag;\n";
    std::cout << "Use -h | --help <flag> if you need help.\n";
    std::cout << "\n";
}
    
    
void
screen::incorrect_subcommand(const std::string& flag, const std::string& cmd){
    std::cout << cmd << " is wrong command for " << flag << " flag.\n";
    std::cout << "Use -h | --help " << flag << " if you need help.\n";
    std::cout << "\n";
}
