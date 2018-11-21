#include "control.h"


Control::Control(const int argc, char** argv)
{
    std::string input{};
    for(int i = 1; i < argc; i++){
        input += argv[i];
        input += " ";
    }
    input = input.substr(0, input.size()-1);

    set_input(input);
}


Control::Control(const std::string& input)
{
    string_deq temp;
    boost::split(temp, input, boost::is_any_of(" "));

    commands_list.clear();
    incorrect_commands.clear();

    if(check_commands(temp))
        divide_input(temp);
}


Control::Control(const Control& c2)
{
    commands_list = c2.commands_list;
    incorrect_commands = c2.incorrect_commands;
}


bool
Control::set_argv(const int argc, char** argv)
{
    std::string input{};
    for(int i = 1; i < argc; i++)
    {
        input += argv[i];
        input += " ";
    }
    input = input.substr(0, input.size()-1);

    return set_input(input);
}

bool
Control::set_input(const std::string& input)
{
    string_deq temp;
    boost::split(temp, input, boost::is_any_of(" "));

    commands_list.clear();
    incorrect_commands.clear();

    if(!check_commands(temp))
        return 0;

    return divide_input(temp);
}


Control::string_deq
Control::get_incorrect_commands()
{
    return incorrect_commands;
}


bool
Control::status()
{
  if(incorrect_commands.empty())
    return 1;

  return 0;
}


bool
Control::empty()
{
    return commands_list.empty();
}


Control::command
Control::front()
{
    return commands_list.front();
}

Control::command
Control::pop_front()
{
    Control::command temp = commands_list.front();
    commands_list.pop_front();

    return temp;
}



//=================
// Private section
//=================


bool
Control::check_commands(const string_deq& input)
{
  for(auto it = input.begin(); it != input.end(); it++)
    if((*it)[0] == '-' && !Control::commands_map.count(*it))
      incorrect_commands.push_back(*it);

  return incorrect_commands.empty();
}


bool
Control::divide_input(const string_deq& input)
{
  command cmd{};

  for(auto it = input.begin(); it != input.end(); it++)
  {
    if(commands_map.count(*it))
    {
      cmd.name = *it;
      it++;

      while(it != input.end() && !commands_map.count(*it))
      {
        cmd.arguments.push_back(*it);
        it++;
      }

      commands_list.push_back(cmd);
      cmd.name.clear();
      cmd.arguments.clear();
      it--;
    }
    else
    {
      incorrect_commands.push_back(*it);
      return 0;
    }
  }

  return 1;
}



//================================
//==Public section - exec_command
//==============================

void
Control::exec_command(const command& cmd)
{
    auto key = commands_map.find(cmd.name);
    switch(key->second)
    {
    case UNNKNOWN_COMMAND: 
        break;
        
    case HELP: 
        //TODO - screen::help(cmd.arguments);
        break;

    case CONFIG:
        config_exec_command(cmd.arguments);
        break;

    default:
        break;
    }
}


void
Control::config_exec_command(const string_deq& cmd)
{
    if(cmd.empty() && !config.set_path())
    {
        config.creat();
    }
    else if(cmd.size() < 2)
    {
        //TODO - screen::bad_arguments_number(CONFIG);
    }
    else
    {
        Config::SECTION section = Config::GLOBAL;
        
        auto key = config_commands_map.find(cmd.front());
        switch(key->second)
        {
        case UNNKNOWN_COMMAND:
            //TODO - screen::incorrect_subcommand(CONFIG, cmd.front());
            break;

        case CREAT: 
            for(auto it = cmd.begin()+1; it != cmd.end(); it++)
            {
                if(!config.set_path(*it))
                    config.creat();
                config.set_path();
                config.add_row(Config::SUB_CONFIG, *it);
            }
            break;

        case ADD_DIRECTORY:           
            for(auto it = cmd.begin()+1; it != cmd.end(); it++)
            {
                auto key = config_sections.find(*it);
                if(key != config_sections.end())
                {
                    section = key->second;
                    continue;
                }

                config.add_row(section, *it);
            }
            break;

        case REMOVE_DIRECTORY:
            for(auto it = cmd.begin()+1; it != cmd.end(); it++)
            {
                auto key = config_sections.find(*it);
                if(key != config_sections.end())
                {
                    section = key->second;
                    continue;
                }

                config.remove_row(section, *it);
            }
            break;

        default:
            //TODO - screen::incorrect_subcommend(CONFIG, cmd.front());
            break;
        }
    }
}





