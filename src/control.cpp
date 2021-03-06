#include "control.hpp"


namespace mngx{


const std::map<std::string, Control::CTRL_COMMAND> Control::flagMap
{
  { "UNKNOWN COMMAND", UNKNOWN_COMMAND },
  { "-h", HELP },
  { "--help", HELP },
  { "-c", CONFIG },
  { "--config", CONFIG },
  { "-a", ARCHIVE },
  { "--archive", ARCHIVE },
  { "-n", NETWORK },
  { "--network", NETWORK}
};

const std::map<std::string, Control::CTRL_COMMAND> Control::helpMap
{
  { "UNKNOWN COMMAND", UNKNOWN_COMMAND },
  { "config", CONFIG },
};

const std::map<std::string, Control::CTRL_COMMAND> Control::configMap
{
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


const std::map<std::string, Control::CTRL_COMMAND> Control::archiveMap
{
  { "UNKNOWN COMMAND", UNKNOWN_COMMAND },
  { "creat", CREAT },
  { "extract", EXTRACT }
};


const std::map<std::string, Control::CTRL_COMMAND> Control::networkMap
{
  { "UNKNOWN COMMAND", UNKNOWN_COMMAND },
  { "send", SEND },
  { "download", DOWNLOAD },
  { "check", CHECK }
};


bool
Control::execCommand(Control& control)
{
  command cmd = control.getCommand();
  auto flag = key(flagMap, cmd.flag);

  switch(flag){
  case UNKNOWN_COMMAND:
    return 0;

  case HELP:
    return execHelp(cmd.arguments);

  case CONFIG:
    return execConfig(cmd.arguments);

  case ARCHIVE:
    return execArchive(cmd.arguments);

  case NETWORK:
    return execNetwork(cmd.arguments);
    return 0;

  default:
    throw " -=[ EXCEPTION ]=-  cotrol flow exceptions!";
  }
}


bool
Control::execHelp(const stringDeq& cmd)
{
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
Control::execConfig(const stringDeq& cmd)
{
    auto  subCmd = key(configMap, cmd.front());
    switch(subCmd){
    case UNKNOWN_COMMAND:
      return 0;

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


bool
Control::execConfigCreat(const stringDeq& cmd)
{
  if(cmd.size() != 2){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  return Config::instance()->creat(cmd[1]);
}


bool
Control::execConfigLoad(const stringDeq& cmd)
{
  if(cmd.size() != 2){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  return Config::instance()->load(cmd[1]);
}


bool
Control::execConfigAddRow(const stringDeq& cmd)
{
  if(cmd.size() != 3){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  return Config::instance()->addRow(Config::GLOBAL, cmd[1] + "=" + cmd[2]);
}


bool
Control::execConfigRemoveRow(const stringDeq& cmd)
{
  if(cmd.size() != 3){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  return Config::instance()->removeRow(Config::GLOBAL, cmd[1] + "=" + cmd[2]);
}


bool
Control::execConfigCreatPack(const stringDeq& cmd)
{
  if(cmd.size() != 2){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  return Config::instance()->creatPack(cmd[1]);
}


bool
Control::execConfigRemovePack(const stringDeq& cmd)
{
  if(cmd.size() != 2){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }
  return Config::instance()->removePack(cmd[1]);
}


bool
Control::execConfigAddDirectory(const stringDeq& cmd)
{
  if(cmd.size() < 3){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }

  Config* config = Config::instance();
  Path path;

  for(auto it = cmd.cbegin()+2; it != cmd.cend(); it++){
    path = *it;
    if(!config->addToPack(cmd[1], path.getPath())){
      return 0;
    }
  }
  return 1;
}


bool
Control::execConfigRemoveDirectory(const stringDeq& cmd)
{
  if(cmd.size() < 3){
    mngx::screen::wrongArgumentsNumber("-c | --config");
    return 0;
  }

  Config* config = Config::instance();
  Path path;

  for(auto it = cmd.cbegin()+2; it != cmd.cend(); it++){
    path = *it;
    if(!config->removeFromPack(cmd[1], path.getPath())){
      return 0;
    }
  }
  return 1;
}


bool 
Control::execArchive(const stringDeq& cmd)
{
  auto subCmd = key(archiveMap, cmd.front());
  switch(subCmd){
  case UNKNOWN_COMMAND:
    return 0;

  case CREAT:
    return execArchiveCreat(cmd);

  case EXTRACT:
    return execArchiveExtract(cmd);

  default:
    screen::incorrectSubcommand("-a | --archive", cmd.front());
    return 0;
  }
}


bool 
Control::execArchiveCreat(const stringDeq& cmd)
{
  TarCompress tarCompress;
  stringVec pack;
  Config *config = Config::instance();

  switch(cmd.size()){
  case 1:
    screen::wrongArgumentsNumber("-a | --archive");
    return 0;

  case 2:
    pack = config->getPack(cmd[1]);
    return tarCompress.creat(
      PathConfig::getDefaultDirectory(), cmd[1],
      pack.begin(), pack.end()
    );

  case 3:
    pack = config->getPack(cmd[1]);
    return tarCompress.creat(
      cmd[1], cmd[2], pack.begin(), pack.end()
    );

  default:
    screen::wrongArgumentsNumber("-a | --archive");
    return 0;
  }
}


bool
Control::execArchiveExtract(const stringDeq& cmd)
{
  if(cmd.size() != 2){
    screen::wrongArgumentsNumber("-a | --archive");
    return 0;
  }
  TarCompress tarCompress;
  Path path = PathConfig::getDefaultDirectory() + cmd[1] + ".tar";
  return tarCompress.extract(path.getPath());
}


bool
Control::execNetwork(const stringDeq& cmd)
{
  auto subCmd = networkMap.find(cmd[0])->second;
  switch(subCmd){
  case UNKNOWN_COMMAND:
    screen::incorrectSubcommand("-n | --network", cmd.front());
    return 0;

  case DOWNLOAD:
    return execNetworkDownload(cmd);

  default:
    screen::incorrectSubcommand("-n | --network", cmd.front());
    return 0;
  }
}


bool
Control::execNetworkDownload(const stringDeq& cmd)
{
  if(cmd.size() != 3){
    screen::wrongArgumentsNumber("-n | --network");
    return 0;
  }
  Network network(cmd[1]);
  network.download(cmd[2]);
  return 1;
}


template<class MAP> Control::CTRL_COMMAND
 Control::key(const MAP& map, const std::string& key)
 {
  return map.find(key)->second;
}


Control::Control(const int argc, char** argv)
{
  setCommand(argc, argv);
}


Control::Control(const std::string& input)
{
  setCommand(input);
}


Control::Control(const Control& control)
{
   setCommand(control);
}


Control&
Control::operator=(const Control& control)
{
  setCommand(control);
  return *this;
}


Control&
Control::operator=(const std::string& cmd)
{
  setCommand(cmd);
  return *this;
}


Control&
Control::operator+=(const Control& control)
{
  for(auto c : control.cmdDeq){
    cmdDeq.push_back(c);
  }

  for(auto i : control.incorrect){
    incorrect.push_back(i);
  }

  return *this;
}


Control&
Control::operator+=(const std::string& cmd)
{
  Control control(cmd);
  for(auto c : control.cmdDeq){
    cmdDeq.push_back(c);
  }

  for(auto i : control.incorrect){
    incorrect.push_back(i);
  }

  return *this;
}


Control::command
Control::getCommand()
{
  command temp = cmdDeq.front();
  cmdDeq.pop_front();
  return temp;
}

bool
Control::setCommand(const int argc, char** argv)
{
  std::string input;

  for(int i = 1; i < argc; i++){
    input += argv[i];
    input += " ";
  }

  return setCommand(input.substr(0, input.size()-1));
}


bool
Control::setCommand(const std::string& input)
{
  stringDeq temp;
  boost::split(temp, input, boost::is_any_of(" "));

  this->clear();
  divideInput(temp);
  return !incorrect.empty();
}

bool
Control::setCommand(const Control& control)
{
  cmdDeq = control.cmdDeq;
  incorrect = control.incorrect;
  return incorrect.empty();
}


std::string
Control::getIncorrect()
{
  return incorrect;
}


bool
Control::status() const
{
  return incorrect.empty();
}


bool
Control::empty() const
{
  return cmdDeq.empty();
}


void
Control::clear()
{
  cmdDeq.clear();
  incorrect.clear();
}


void
Control::divideInput(const stringDeq& input)
{
    command cmd{};

    for(auto it = input.cbegin(); it != input.cend(); it++){
      if(flagMap.count(*it)){
        cmd.flag = *it;
        it++;

        while(it != input.cend() && !flagMap.count(*it)){
          cmd.arguments.push_back(*it);
          it++;
        }

        cmdDeq.push_back(cmd);
        cmd.flag.clear();
        cmd.arguments.clear();
        it--;
      }
      else{
        incorrect = *it;
        return;
      }
  }
}


} //namespace mngx
