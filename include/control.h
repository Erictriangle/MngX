#ifndef CONTROL_H
#define CONTROL_H

#include <string>
#include <boost/algorithm/string.hpp> //boost::split  boost::is_any_of
#include <deque>
#include <map>
#include <iterator>
#include "config.h"


class Control
{   
    typedef std::deque<std::string> string_deq;

public:
    struct command
    {
        std::string name;
        string_deq arguments;
    };

    enum COMMAND_FLAG
    {
        //commands_map
        UNNKNOWN_COMMAND = 0,
        HELP = 1,
        CONFIG = 2,

        //config_commands_map
        CREAT = 100,
        LOAD = 101,
        ADD_DIRECTORY = 102,
        REMOVE_DIRECTORY = 103
    };

    

private:
    const std::map<std::string, COMMAND_FLAG> commands_map
    {
        { "UNNKOWN COMMAND", UNNKNOWN_COMMAND},
        { "-h", HELP},
        { "--help", HELP},
        { "-c", CONFIG},
        { "--config", CONFIG}
    };


    const std::map<std::string, COMMAND_FLAG> config_commands_map
    {
        { "UNNKOWN COMMAND", UNNKNOWN_COMMAND},
        { "creat", CREAT},
        { "load", LOAD},
        { "add-directory", ADD_DIRECTORY},
        { "remove-directory", REMOVE_DIRECTORY}
    };


    const std::map<std::string, Config::SECTION> config_sections
    {
        { "global", Config::GLOBAL },
        { "text", Config::TEXT_MODULE }
    };
    

public:
    Control() = default;
    Control(const int, char**);
    Control(const std::string&);
    Control(const Control&);
    ~Control() = default;

    /* TODO
    Control operator=(const Control&);
    Control operator=(const std::string&);
    Control operator+=(const Control&);
    Control operator+=(const std::string&);
    */

    bool set_argv(const int, char**);
    bool set_input(const std::string&);

    string_deq get_incorrect_commands();
    bool status();
    bool empty();
    command front();
    command pop_front();

    void exec_command(const command&);
    void config_exec_command(const string_deq&);
    
private:
    std::deque<command> commands_list;
    string_deq incorrect_commands;
    Config config;

 
    bool check_commands(const string_deq&);
    bool divide_input(const string_deq&);

};


#endif // CONTROL_H
