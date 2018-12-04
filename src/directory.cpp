#include "directory.h"


//================
//==CONSTRUCTORS==
//==============


Directory::Directory(){
    set_default_config_path();
}


Directory::Directory(const std::string& input){
    set_default_config_path();
    set_config_path(input);
}


void
Directory::set_default_config_path(){
    using namespace boost::filesystem;
    
    username = getenv("USER");
    default_config.directory = "/home/" + username + "/.mngx";
    default_config.path += default_config.directory + FILENAME;

    path default_directory(default_config.directory);
    if(!is_directory(default_directory))
        if(!create_directory(default_directory))
            throw "Cannot creat default directory exception"; //TODO - exception handle
}

    
//==============
//==OPERATORS==
//============


Directory&
Directory::operator=(const Directory& directory){
    username = directory.username;
    default_config = directory.default_config;
    config = directory.config;

    return *this;
}


Directory&
Directory::operator=(const std::string& directory){
    set_config_path(directory);
    
    return *this;
}


//===========
//==PUBLIC==
//=========


void
Directory::set_config_path(const std::string& input){
    using namespace boost::filesystem;

    path input_path(input);

    //absolute path
    if(input_path.is_absolute()){ 
        if(input_path.native().back() == '/'){  //withou filename
            config.directory = input_path.native();
            config.path = add_filename(input_path);
        }
        else if(input_path.extension() != ".txt"){ //bad extension
            config_path = change_extension(input_path);
        }
        else
            config_path = input_path.native();
        
        return;
    }

    //relative path
    config_path = current_path().native() + '/';
    if(input_path.native().back() == '/') //without filename
        config_path += add_filename(input_path);
    else if(input_path.extension() != ".txt") //bad extension
        config_path += change_extension(input_path);
    else
        config_path += input_path.native();

    return;
}


const std::string
Directory::get_default_config_path(){
    return default_config_path;
}


const std::string
Directory::get_config_path(){
    return config_path;
}


bool
Directory::default_config_file_exist(){
    return boost::filesystem::is_regular_file(default_config_path);
}


//============
//==PRIVATE==
//==========


bool
Directory::is_root(){
    if(getenv("USER") == "root")
        return 1;
    return 0;
}


std::string
Directory::add_filename(const path& input){
    return input.native() + "/MngConfig.txt";
}


std::string
Directory::change_extension(const path& input){
    return input.native().substr(
        0, input.native().size() - input.extension().size())
        + ".txt";
}

