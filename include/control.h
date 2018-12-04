#ifndef CONTROL_H
#define CONTROL_H

#include "directory.h"
#include "config.h"
#include "screen.h"

#include <string>
#include <deque>
#include <map>
#include <iterator>

#include <boost/algorithm/string.hpp> //boost::split boost::is_any_of


class Control{
public:
    struct command{
        std::string name;
        std::deque<std::string> arguments;
    };

    enum COMMAND_FLAG{
        //flags
        UNKNOWN_COMMAND = 0,
        HELP = 1,
        CONFIG = 2,
        
        //config command
        CREAT = 100,
        LOAD = 101,
        ADD_DIRECTORY = 102,
        REMOVE_DIRECTORY = 103
    };
    
    //Collection for interpreter
    static const std::map<std::string, COMMAND_FLAG> flag_command_map;
    static const std::map<std::string, COMMAND_FLAG> help_map;
    static const std::map<std::string, COMMAND_FLAG> config_commands_map;

    //Static method
    static void exec_command(Control&, Directory&, Config&);
    static void exec_help(std::deque<std::string>&);
    static void exec_config(std::deque<std::string>&, Config&);

private:
    typedef std::deque<std::string> string_deq;
    typedef std::deque<command> command_deq;
    
public:
    Control() = default;
    Control(const int, char**);
    Control(const std::string&);
    Control(const Control&);
    ~Control() = default;

    Control& operator=(const Control&);
    Control& operator=(const std::string&);
    Control& operator+=(const Control&);
    Control& operator+=(const std::string&);

    //manage input 
    bool set_argv(const int, char**);
    bool set_input(const std::string&);

    //object status
    std::string get_incorrect_flag();
    bool status() const;
    bool empty() const;
    void clear();


    //manage output
    command get_command();

 private:
    command_deq commands;
    string_deq incorrect_flags;

    bool check_flags(const string_deq&);
    bool divide_input(const string_deq&);
};


#endif //CONTROL_H
