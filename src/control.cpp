#include "control.hpp"


namespace mngx{


const std::map<std::string, Control::CTRL_COMMAND> Control::flagMap{
  { "UNKNOWN COMMAND", UNKNOWN_COMMAND },
  { "-h", HELP },
  { "--help", HELP },
  { "-c", CONFIG },
  { "--config", CONFIG },
  { "-a", ARCHIVE },
  { "--archive", ARCHIVE }
};

const std::map<std::string, Control::CTRL_COMMAND> Control::helpMap{
  { "UNKNOWN COMMAND", UNKNOWN_COMMAND },
  { "config", CONFIG },
};

const std::map<std::string, Control::CTRL_COMMAND> Control::configMap{
  { "UNKNOWN COMMAND", UNKNOWN_COMMAND },
  { "creat", CREAT },
  { "load", LOAD },
  { "add-row", ADD_ROW },
  { "remove-row", REMOVE_ROW },
  { "creat-pack", CREAT_PACK },
  { "remove-pack", REMOVE_PACK},
  { "add-directory", ADD_DIRECTORY },
  { "remove-directory", REMOVE_DIRECTORY }
};


bool
Control::execCommand(Control& control){
  s_command cmd = control.command();
  auto flag = key(flagMap, cmd.flag);

  switch(flag){
  case UNKNOWN_COMMAND:
    return 0;

  case HELP:
    return execHelp(cmd.arguments);

  case CONFIG:
    return execConfig(cmd.arguments);

  case ARCHIVE:
    //TODO - return execArchive(cmd.arguments, config);

  default:
    throw " -=[ EXCEPTION ]=-  cotrol flow exceptions!";
  }
}


bool
Control::execHelp(const string_deq& cmd){
    if(cmd.empty()){
      screen::help();
      return 0;
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
    return 0;
}


bool
Control::execConfig(const string_deq& cmd){
    auto  subCmd = key(configMap, cmd.front());
    switch(subCmd){
    case CREAT:
      return execConfigCreat(cmd);

    case LOAD:
      return execConfigLoad(cmd);

    case ADD_ROW:
      return execConfigAddRow(cmd);

    case REMOVE_ROW:
      return execConfigRemoveRow(cmd);

    case CREAT_PACK:
      return execConfigCreatPack(cmd);

    case REMOVE_PACK:
      return execConfigRemovePack(cmd);

    case ADD_DIRECTORY:
      return execConfigAddDirectory(cmd);

    case REMOVE_DIRECTORY:
      return execConfigRemoveDirectory(cmd);

    default:
      screen::incorrectSubcommand("-c | --config", cmd.front());
      return 0;
    }
}


void
Control::execConfigDefault(){
  mngx::PathConfig pathConfig;
  mngx::Config* config = Config::instance();
  if(!mngx::Path::isDirectory(pathConfig.defaultDirectory()))
      mngx::Path::creatDirectory(pathConfig.defaultDirectory());

  if(!mngx::Path::isFile(pathConfig.defaultPath()))
    config->creat();
}


bool
Control::execConfigCreat(const string_deq& cmd){
  if(cmd.size() != 2){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  Config* config = Config::instance();
  return config->creat(cmd[1]);
}


bool
Control::execConfigLoad(const string_deq& cmd){
  if(cmd.size() != 2){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  Config* config = Config::instance();
  return config->load(cmd[1]);
}


bool
Control::execConfigAddRow(const string_deq& cmd){
  if(cmd.size() != 3){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  Config* config = Config::instance();
  return config->addRow(Config::GLOBAL, cmd[1] + "=" + cmd[2]);
}


bool
Control::execConfigRemoveRow(const string_deq& cmd){
  if(cmd.size() != 3){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  Config* config = Config::instance();
  return config->removeRow(Config::GLOBAL, cmd[1] + "=" + cmd[2]);
}


bool
Control::execConfigCreatPack(const string_deq& cmd){
  if(cmd.size() != 2){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  Config* config = Config::instance();
  return config->creatPack(cmd[1]);
}


bool
Control::execConfigRemovePack(const string_deq& cmd){
  if(cmd.size() != 2){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  Config* config = Config::instance();
  return config->removePack(cmd[1]);
}


bool
Control::execConfigAddDirectory(const string_deq& cmd){
  if(cmd.size() < 3){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  Config* config = Config::instance();
  for(auto it = cmd.cbegin()+2; it != cmd.cend(); it++){
    if(!config->addToPack(cmd[1], *it))
      return 0;
  }
  return 1;
}


bool
Control::execConfigRemoveDirectory(const string_deq& cmd){
  if(cmd.size() < 3){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  Config* config = Config::instance();
  for(auto it = cmd.cbegin()+2; it != cmd.cend(); it++){
    if(!config->removeFromPack(cmd[1], *it))
      return 0;
  }
  return 1;
}



template<class MAP> Control::CTRL_COMMAND
 Control::key(const MAP& map, const std::string& key){
  return map.find(key)->second;
}


Control::Control(const int argc, char** argv){
  command(argc, argv);
}


Control::Control(const std::string& input){
  command(input);
}


Control::Control(const Control& control){
   command(control);
}


Control&
Control::operator=(const Control& control){
  command(control);
  return *this;
}


Control&
Control::operator=(const std::string& cmd){
  command(cmd);
  return *this;
}


Control&
Control::operator+=(const Control& control){
  for(auto c : control.m_commands)
    m_commands.push_back(c);

  for(auto i : control.m_incorrect)
    m_incorrect.push_back(i);

  return *this;
}


Control&
Control::operator+=(const std::string& cmd){
  Control control(cmd);
  for(auto c : control.m_commands)
    m_commands.push_back(c);

  for(auto i : control.m_incorrect)
    m_incorrect.push_back(i);

  return *this;
}


Control::s_command
Control::command(){
  s_command temp = m_commands.front();
  m_commands.pop_front();
  return temp;
}

bool
Control::command(const int argc, char** argv){
  std::string input;

  for(int i = 1; i < argc; i++){
    input += argv[i];
    input += " ";
  }
  input.pop_back();

  return command(input);
}


bool
Control::command(const std::string& input){
  string_deq temp;
  boost::split(temp, input, boost::is_any_of(" "));

  this->clear();
  divideInput(temp);
  return !m_incorrect.empty();
}

bool
Control::command(const Control& control){
  m_commands = control.m_commands;
  m_incorrect = control.m_incorrect;
  return m_incorrect.empty();
}


std::string
Control::incorrect(){
  return m_incorrect;
}


bool
Control::status() const{
  return m_incorrect.empty();
}


bool
Control::empty() const{
  return m_commands.empty();
}


void
Control::clear(){
  m_commands.clear();
  m_incorrect.clear();
}


void
Control::divideInput(const string_deq& input){
    s_command cmd{};

    for(auto it = input.cbegin(); it != input.cend(); it++){
      if(flagMap.count(*it)){
        cmd.flag = *it;
        it++;

        while(it != input.cend() && !flagMap.count(*it)){
          cmd.arguments.push_back(*it);
          it++;
        }

        m_commands.push_back(cmd);
        cmd.flag.clear();
        cmd.arguments.clear();
        it--;
      }
      else{
        m_incorrect = *it;
        return;
      }
  }
}


} //namespace mngx
