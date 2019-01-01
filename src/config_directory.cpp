#include "config_directory.h"


//=================
//==CONSTRUCTORS==
//===============


Config_Directory::Config_Directory(){
    set_default_path();
    check_default_path();
}


Config_Directory::Config_Directory(const std::string& input){
    set_default_path();
    check_default_path();
    set_path(input);
}


//===========
//==PUBLIC==
//=========


void
Config_Directory::set_path(const std::string& input){
    Directory::set_path(input);

    if(path.file.empty())
        path.file = _FILENAME;
    else if(path.file.extension() != _EXTENSION)
        path.file = change_extension(path.file);
}


std::string
Config_Directory::take_default_path(){
    return default_path.directory.native() + "/" + default_path.file.native();
}


//============
//==PRIVATE==
//==========


void
Config_Directory::set_default_path(){
    username = getenv("USER");
    default_path.directory = "/home/" + username + _FOLDER;
    default_path.file = _FILENAME;
}


void
Config_Directory::check_default_path(){
    namespace fs = boost::filesystem;

    if(!fs::is_directory(default_path.directory))
        if(!fs::create_directory(default_path.directory))
            throw " -=[ EXCEPTIONS ]=-  Cannot creat default directory!";
}


std::string
Config_Directory::add_filename(const boost::filesystem::path& input_path){
    return input_path.native() + _FILENAME;
}

std::string
Config_Directory::change_extension(const boost::filesystem::path& input_path){
    return input_path.native().substr(0,input_path.native().size()
                                      -input_path.extension().size()) + _EXTENSION;
}
