#include "control.hpp"


namespace mngx
{

const std::map<std::string, Control::CTRL_COMMAND> Control::flagMap
{
  { "UNKNOWN COMMAND", UNKNOWN_COMMAND },
  { "-h", HELP },
  { "--help", HELP },
  { "-c", CONFIG },
  { "--config", CONFIG },
};

const std::map<std::string, Control::CTRL_COMMAND> Control::helpMap
{
  { "UNKNOWN COMMAND", UNKNOWN_COMMAND },
  { "config", CONFIG },
};

const std::map<std::string, Control::CTRL_COMMAND> Control::configMap
{
  { "UNKNOWN COMMAND", UNKNOWN_COMMAND},
  { "creat", CREAT},
  { "load", LOAD},
  { "add-directory", ADD_DIRECTORY},
  { "remove-directory", REMOVE_DIRECTORY}
};


void
Control::execCommand(Control& control, Config& config)
{
  s_command cmd = control.command();
  auto flag = key(flagMap, cmd.flag);

  switch(flag)
  {
  case UNKNOWN_COMMAND:
    break;

  case HELP:
    execHelp(cmd.arguments);
    break;

  case CONFIG:
    execConfig(cmd.arguments, config);
    break;

  default:
    throw " -=[ EXCEPTION ]=-  cotrol flow exceptions!";
  }
}


void
Control::execHelp(const string_deq& cmd)
{
    if(cmd.empty())
    {
      screen::help();
      return;
    }

    auto subCmd = key(helpMap, cmd.front());
    switch(subCmd){
    case CONFIG:
      screen::helpConfig();
      break;

    default:
      screen::incorrectSubcommand("-h | --help", cmd.front());
      break;
    }
}


void
Control::execConfig(const string_deq& cmd, Config& config){
    auto  subCmd = key(configMap, cmd.front());
    switch(subCmd){
    case CREAT:
      execConfigCreat(cmd, config);
      break;

    case LOAD:
      execConfigLoad(cmd, config);
      break;

    case ADD_DIRECTORY:
      execConfigAddDirectory(cmd, config);
      break;

    case REMOVE_DIRECTORY:
      execConfigRemoveDirectory(cmd, config);
      break;

    default:
      screen::incorrectSubcommand("-c | --config", cmd.front());
      break;
    }
}


void
Control::execConfigDefault()
{
  mngx::PathConfig pathConfig;
  mngx::Config config;
  if(!mngx::Path::isDirectory(pathConfig.defaultDirectory()))
      mngx::Path::creatDirectory(pathConfig.defaultDirectory());

  if(!mngx::Path::isFile(pathConfig.defaultPath()))
    config.creat();

}


void
Control::execConfigCreat(const string_deq& cmd, Config& config)
{
  if(cmd.size() != 2)
  {
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return;
  }
  config.creat(cmd[1]);
}


void
Control::execConfigLoad(const string_deq& cmd, Config& config)
{
  if(cmd.size() != 2)
  {
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return;
  }
  config = cmd[1];
}


void
Control::execConfigAddDirectory(const string_deq& cmd, Config& config)
{
  auto section = Config::GLOBAL;
  for(auto it = cmd.cbegin()+1; it != cmd.cend(); it++)
  {
    if(Config::stringSectionMap.count(*it))
      section = Config::stringSectionMap.find(*it)->second;
    else
      config.addRow(section, *it);
  }
}


void
Control::execConfigRemoveDirectory(const string_deq& cmd, Config& config)
{
  auto section = Config::GLOBAL;
  for(auto it = cmd.cbegin()+1; it != cmd.cend(); it++)
  {
    if(Config::stringSectionMap.count(*it))
      section = Config::stringSectionMap.find(*it)->second;
    else
      config.removeRow(section, *it);
  }
}


template<class MAP> Control::CTRL_COMMAND
 Control::key(const MAP& map, const std::string& key)
{
  return map.find(key)->second;
}


Control::Control(const int argc, char** argv)
{
  command(argc, argv);
}


Control::Control(const std::string& input)
{
  command(input);
}


Control::Control(const Control& control)
{
   command(control);
}


Control&
Control::operator=(const Control& control)
{
  command(control);
  return *this;
}


Control&
Control::operator=(const std::string& cmd)
{
  command(cmd);
  return *this;
}


Control&
Control::operator+=(const Control& control)
{
  for(auto c : control.m_commands)
  {
    m_commands.push_back(c);
  }
  for(auto i : control.m_incorrects)
  {
    m_incorrects.push_back(i);
  }
  return *this;
}


Control&
Control::operator+=(const std::string& cmd)
{
  Control control(cmd);
  for(auto c : control.m_commands)
  {
    m_commands.push_back(c);
  }
  for(auto i : control.m_incorrects)
  {
    m_incorrects.push_back(i);
  }
  return *this;
}


Control::s_command
Control::command()
{
  s_command temp = m_commands.front();
  m_commands.pop_front();
  return temp;
}

bool
Control::command(const int argc, char** argv)
{
  std::string input;

  for(int i = 1; i < argc; i++)
  {
    input += argv[i];
    input += " ";
  }
  input.pop_back();

  return command(input);
}


bool
Control::command(const std::string& input)
{
  string_deq temp;
  boost::split(temp, input, boost::is_any_of(" "));

  this->clear();
  divideInput(temp);
  return !m_incorrects.empty();
}

bool
Control::command(const Control& control)
{
  m_commands = control.m_commands;
  m_incorrects = control.m_incorrects;
  return m_incorrects.empty();
}


std::string
Control::incorrect()
{
  std::string temp;
  return (m_incorrects.empty())
    ? ""
    : temp;
}


bool
Control::status() const
{
  return m_incorrects.empty();
}


bool
Control::empty() const
{
  return m_commands.empty();
}


void
Control::clear()
{
  m_commands.clear();
  m_incorrects.clear();
}


void
Control::divideInput(const string_deq& input)
{
    s_command cmd{};

    for(auto it = input.cbegin(); it != input.cend(); it++)
    {
      if(flagMap.count(*it))
      {
        cmd.flag = *it;
        it++;

        while(it != input.cend() && !flagMap.count(*it))
        {
          cmd.arguments.push_back(*it);
          it++;
        }

        m_commands.push_back(cmd);
        cmd.flag.clear();
        cmd.arguments.clear();
        it--;
      }
      else
      {
        m_incorrects.push_back(*it);
        return;
      }
    }
}

} //namespace mngx
