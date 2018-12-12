#include "control.h"


//==============
//==INPUT_MAP==
//============


const std::map<std::string, Control::COMMAND_FLAG> Control::flag_command_map{
    { "UNKNOWN COMMAND", UNKNOWN_COMMAND },
    { "-h", HELP },
    { "--help", HELP },
    { "-c", CONFIG },
    { "--config", CONFIG }
};


const std::map<std::string, Control::COMMAND_FLAG> Control::help_map{
    { "UNKNOWN COMMAND", UNKNOWN_COMMAND },
    { "config", CONFIG },
};


const std::map<std::string, Control::COMMAND_FLAG> Control::config_commands_map{
    { "UNKNOWN COMMAND", UNKNOWN_COMMAND},
    { "creat", CREAT},
    { "load", LOAD},
    { "add-directory", ADD_DIRECTORY},
    { "remove-directory", REMOVE_DIRECTORY}
};


//===========
//==STATIC==
//=========


void
Control::exec_command(Control& control, Config_Directory& config_directory){
    Config config(config_directory.take_default_path());
    command cmd = control.get_command();

    auto key = flag_command_map.find(cmd.name);

    switch(key->second){
    case UNKNOWN_COMMAND:
        break;

    case HELP:
        exec_help(cmd.arguments);
        break;

    case CONFIG:
        exec_config(cmd.arguments, config, config_directory);
        break;

    default:
        throw " -=[ EXCEPTION ]=-  exec_command exceptions!"; 
    }
}


void
Control::exec_help(string_deq& cmd){
    if(cmd.empty()){
        screen::help();
        return;
    }

    auto key = help_map.find(cmd.front());
    if(key == help_map.end()){
        screen::incorrect_subcommand("-h | --help", cmd.front());
        return;
    }

    switch(key->second){
    case UNKNOWN_COMMAND:
        break;

    case CONFIG:
        screen::help_config();
        break;
        
    default:
        throw " -=[ EXCEPTION ]=-  exec_help exception!";
    }
}


void
Control::exec_config(string_deq& cmd, Config& config, Config_Directory& config_directory){
    if(cmd.empty()){
        screen::bad_arguments_number("-c | --config");
        return;
    }

    Config::SECTION section = Config::GLOBAL;
    auto key = config_commands_map.find(cmd.front());
    if(key == config_commands_map.end()){
        screen::incorrect_subcommand("-c | --config", cmd.front());
        return;
    }

    switch(key->second){
    case UNKNOWN_COMMAND:
        break;

    case CREAT:
        
        
        
    default:
        throw " -=[ EXCEPTION ]=-  exec_config exception!";
    }
}


//=================
//==CONSTRUCTORS==
//===============


Control::Control(const int argc, char** argv){
    set_argv(argc, argv);
}

    
Control::Control(const std::string& input){
    set_input(input);
}


Control::Control(const Control& control){
    commands = control.commands;
    incorrect_flags = control.incorrect_flags;
}


//==============
//==OPERATORS==
//============


Control&
Control::operator=(const Control& control){
    this->clear();
    commands = control.commands;
    incorrect_flags = control.incorrect_flags;
    return *this;
}


Control&
Control::operator=(const std::string& input){
    this->clear();
    set_input(input);
    return *this;
}


Control&
Control::operator+=(const Control& control){
    for(auto c : control.commands)
        commands.push_back(c);
    for(auto ic : control.incorrect_flags)
        incorrect_flags.push_back(ic);
    
    return *this;
}


Control&
Control::operator+=(const std::string& input){
    set_input(input);
    return *this;
}


//===========
//==PUBLIC==
//=========


bool
Control::set_argv(const int argc, char** argv){
    std::string input;

    for(int i = 1; i < argc; i++){
        input += argv[i];
        input += " ";
    }
    input = input.substr(0, input.size()-1); //kill last space char

    return set_input(input);
}


bool
Control::set_input(const std::string& input){
    string_deq temp;
    boost::split(temp, input, boost::is_any_of(" "));

    this->clear();

    if(!check_flags(temp))
        return 0;

    return divide_input(temp);
}


std::string
Control::get_incorrect_flag(){
    std::string temp = incorrect_flags.front();
    incorrect_flags.pop_front();

    return temp;
}


bool
Control::status() const{
    if(incorrect_flags.empty())
        return 1;
    return 0;
}


bool
Control::empty() const{
    return commands.empty();
}


void
Control::clear(){
    commands.clear();
    incorrect_flags.clear();
}


Control::command
Control::get_command(){
    Control::command temp = commands.front();
    commands.pop_front();

    return temp;
}


//============
//==PRIVATE==
//==========


bool
Control::check_flags(const string_deq& input){
    for(auto i : input)
        if(i.front() == '-' && !Control::flag_command_map.count(i))
            incorrect_flags.push_back(i);

    return incorrect_flags.empty();
}


bool
Control::divide_input(const string_deq& input){
    command cmd{};

    for(auto it = input.begin(); it != input.end(); it++){
        if(flag_command_map.count(*it)){
            cmd.name = *it;
            it++;
            
            while(it != input.end() && !flag_command_map.count(*it)){
                cmd.arguments.push_back(*it);
                it++;
            }
                    
            commands.push_back(cmd);
            cmd.name.clear();
            cmd.arguments.clear();
            it--;
        }
        else{
            incorrect_flags.push_back(*it);
            return 0;
        }
    }
    
    return 1;
}
