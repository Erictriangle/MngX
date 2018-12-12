#include "directory.h"


//=================
//==CONSTRUCTORS==
//===============


Directory::Directory(const std::string& input){
    set_input(input);
}


Directory::Directory(const Directory& dir){
    copy(dir);
}


//==============
//==OPERATORS==
//============


Directory&
Directory::operator=(const std::string& input){
    set_input(input);
    return *this;
}


Directory&
Directory::operator=(const Directory& dir){
    copy(dir);
    return *this;
}


//===========
//==PUBLIC==
//=========


void
Directory::set_input(const std::string& input){
    namespace fs = boost::filesystem;

    clear();
    fs::path input_path(input);
    
    if(input_path.is_absolute()){
        if(fs::is_regular_file(input_path)){ //absolute with filename
            path.file = input_path.filename();
            path.directory = input_path.remove_filename().native();
        }
        else{ //absolute without filename
            path.directory = input_path.native();
        }   
    }
    else{ 
        fs::path current = fs::current_path();
        current += input_path;
        if(fs::is_regular_file(input_path)){ //relative with filename
            path.file = input_path.filename();
            path.directory = current.native() + input_path.remove_filename().native();
        }
        else{ //relative without filename
            path.directory = current.native() + input_path.native();
        }
    }
}


void
Directory::copy(const Directory& dir){
    path = dir.path;
    username = dir.username;
}


const std::string
Directory::get_directory(){
    return path.directory.native();
}


const std::string
Directory::get_filename(){
    return path.file.native();
}


const std::string
Directory::get_path(){
    return path.directory.native() + path.file.native();
}


const std::string
Directory::get_username(){
    return username;
}



//============
//==PRIVATE==
//==========


void
Directory::clear(){
    path.directory.clear();
    path.file.clear();
}


bool
Directory::root(){
    if(getenv("USER") == "root")
        return 1;
    return 0;
}



