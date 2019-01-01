#ifndef CONTROL_H
#define CONTROL_H

#include "directory.h"
#include "config_directory.h"
#include "directory_structure.h"
#include "config.h"
#include "screen.h"

#include <string>
#include <deque>
#include <map>
#include <iterator>

#include <boost/algorithm/string.hpp> //boost::split boost::is_any_of


/*!
 *\brief Input and control flow managment
 *
 *Control class is created to manage chain of characters entered by the user.
 *The class object take parameters from the input stream, dvivide
 *them on commands(all commands have flag name and arguments)
 *and gather wrong form of input in incorrect flags container.
 *
 *Static class methods are used to execute features from this software.
*/



class Control{
private:
    struct command{
        std::string name;
        std::deque<std::string> arguments;
    };

    typedef std::deque<std::string> string_deq;
    typedef std::deque<command> command_deq;
    
public:
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

   
public:   
    //Collection for interpreter
    static const std::map<std::string, COMMAND_FLAG> flag_command_map;
    static const std::map<std::string, COMMAND_FLAG> help_map;
    static const std::map<std::string, COMMAND_FLAG> config_commands_map;

    //Static method
    static void exec_command(Control&, Config_Directory&); //!< choose other method for flag and pass arguments;

    
private:
    static void exec_help(string_deq&);
    static void exec_config(string_deq&, Config&, Config_Directory&);
    static bool exec_config_default(const string_deq&, Config&, Config_Directory&);
    static void exec_config_creat(const string_deq&, Config&);
    static void exec_config_load(const string_deq&, Config_Directory&);
    static void exec_config_add_row(string_deq&, Config&);
    static void exec_config_remove_row(string_deq&, Config&);


    template<class MAP>
    static COMMAND_FLAG take_key(const MAP&, const std::string&);

public:
    Control() = default;
    Control(const int, char**);  //!< manage input from stdin
    Control(const std::string&); 
    Control(const Control&); 
    ~Control() = default;

    Control& operator=(const Control&); 
    Control& operator=(const std::string&);
    Control& operator+=(const Control&); //!< add commands and incorrect_flags
    Control& operator+=(const std::string&); //!< add commands and incorrect_flags

    bool set_argv(const int, char**); //!< manage input from stdin
    bool set_input(const std::string&); 

    std::string get_incorrect_flag(); //!< return front and pop_front
    bool status() const; //!< return incorrect_flags.empty();
    bool empty() const; //!< return commands.empty();
    void clear(); //!< clear commands and incorrect_flags

    command get_command(); //!< return front and pop_front

 private:
    command_deq commands;
    string_deq incorrect_flags;

    bool check_flags(const string_deq&);
    bool divide_input(const string_deq&);
};


#endif //CONTROL_H
