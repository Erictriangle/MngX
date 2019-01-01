#include "control.h"


//==============
//==STATIC_MAP==
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
    Config config;
    
    if(config_directory.empty())
        config = config_directory.take_default_path();
    else
        config = config_directory.get_path();
  
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

    auto key = take_key(help_map, cmd.front());
    switch(key){
    case UNKNOWN_COMMAND:
        screen::incorrect_subcommand("-h | --help", cmd.front());
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
    if(exec_config_default(cmd, config, config_directory)) //creat default config file if dont exist
        return;

    auto key = take_key(config_commands_map, cmd.front());
    switch(key){
    case UNKNOWN_COMMAND:
        screen::incorrect_subcommand("-c | --config", cmd.front());
        break;

    case CREAT:
        exec_config_creat(cmd, config);
        break;

    case LOAD:
        exec_config_load(cmd, config_directory);
        break;

    case ADD_DIRECTORY:
        exec_config_add_row(cmd, config);
        break;
        
    case REMOVE_DIRECTORY:
        exec_config_remove_row(cmd, config);
        break;
       
    default:
        throw " -=[ EXCEPTION ]=-  exec_config exception! \n"; //TODO - exception handling
    }
}
    


bool
Control::exec_config_default(const string_deq& cmd, Config& config,
                             Config_Directory& config_directory){
    if(!cmd.empty())
        return 0;
    else if(config_directory.is_file())
        return 1;
    else
        config.creat(config_directory.take_default_path());
    return 1;
}


void
Control::exec_config_creat(const string_deq& cmd, Config& config){
    if(cmd.size() != 2)
        screen::wrong_arguments_number("-c | --config");
    else{
        Config_Directory cd(cmd[1]);
        config.creat(cd.get_path());
    }
}


void
Control::exec_config_load(const string_deq& cmd, Config_Directory& config_directory){
    if(cmd.size() != 2)
        screen::wrong_arguments_number("-c | --config");
    else
        config_directory.set_path(cmd[1]);
}


void
Control::exec_config_add_row(string_deq& cmd, Config& config){
    Config::SECTION section = Config::GLOBAL;
    cmd.pop_front(); //first is add_directory

    while(!cmd.empty()){
        if(Config::input_section_map.find(cmd.front()) != Config::input_section_map.end())
            section = Config::input_section_map.find(cmd.front())->second;
        else
            config.add_row(section, cmd.front());
        cmd.pop_front();
    }
}


void
Control::exec_config_remove_row(string_deq& cmd, Config& config){
    Config::SECTION section = Config::GLOBAL;;
    cmd.pop_front(); //first is add_directory

    while(!cmd.empty()){
        if(Config::input_section_map.find(cmd.front()) != Config::input_section_map.end())
            section = Config::input_section_map.find(cmd.front())->second;
            else
                config.remove_row(section, cmd.front());
            cmd.pop_front();
    }
}


//==============
//==TEAMPLATE==
//============


template<class MAP>
Control::COMMAND_FLAG Control::take_key(const MAP& map, const std::string& input){
    auto key = map.find(input);
    if(key == map.end())
        return Control::UNKNOWN_COMMAND;
    return key->second;
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
    return incorrect_flags.empty();

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
