#include "config.h"


//===============
//==STATIC_MAP==
//=============


const std::map<Config::SECTION, std::string> Config::section_string_map{
    { GLOBAL, ".mngx" },
    { MAJOR, ".major" },
    { SUB_CONFIG, ".sub-config"}
};


const std::map<std::string, Config::SECTION> Config::string_section_map{
    { ".mngx", GLOBAL },
    { ".major", MAJOR },
    { ".sub-config", SUB_CONFIG }
};


const std::map<std::string, Config::SECTION> Config::input_section_map{
    { "global", GLOBAL },
    { "major", MAJOR },
    { "sub-config", SUB_CONFIG }
}; 


//=================
//==CONSTRUCTORS==
//===============


Config::Config(){
    file.io.exceptions( std::fstream::badbit);
}


Config::Config(const std::string& file_name){
    file.name = file_name;
    file.io.exceptions( std::fstream::badbit);
}


Config::~Config(){
    if(file.io.is_open())
        file.io.close();
}


//==============
//==OPERATORS==
//============


Config&
Config::operator=(const Config& config){
    if(file.io.is_open())
        file.io.close();

    file.name = config.file.name;
    return *this;
}


Config&
Config::operator=(const std::string& input){
    if(file.io.is_open())
        file.io.close();

    file.name = input;
    return *this;
}


//===========
//==PUBLIC==
//=========


void
Config::creat(){
    if(!status())
        throw "Config not init exception!"; //TODO - exception handling
    
    file.io.open(file.name, std::ios::out | std::ios::trunc);
    for(auto ssm : section_string_map)
        file.io << ssm.second << "\n";
    file.io.close();

}


void
Config::creat(const std::string& filename){
    file.io.open(filename, std::ios::out | std::ios::trunc);
    for(auto ssm : section_string_map)
        file.io << ssm.second << "\n";
    file.io.close();
}


bool
Config::add_row(const SECTION section, const std::string& input){
    if(!status())
        throw "Config not init exceptions"; //TODO - exception handling
    
    if(is_repeat(section, input))
        return 0;
    
    auto key = section_string_map.find(section);
    string_vec temp_vec;
    std::string buffer;

    file.io.open(file.name, std::ios::in, ); //file -> vector
    while(file.io >> buffer)
        temp_vec.push_back(buffer);
    file.io.close();

    file.io.open(file.name, std::ios::out | std::ios::trunc); //vector + input -> file
    for(auto it = temp_vec.cbegin(); it != temp_vec.cend(); it++){
        file.io << *it << '\n';
        if(*it == key->second)
            file.io << input << '\n'; 
    }
    file.io.close();

    return 1;
}


bool
Config::remove_row(const SECTION section, const std::string& input){
    if(!status())
        throw "Config not init exception"; // TODO - exception handling
    
    if(!is_repeat(section, input))
        return 0;
    
    auto key = section_string_map.find(section);
    string_vec temp_vec;
    std::string buffer;

    file.io.open(file.name, std::ios::in); //file -> vector
    while(file.io >> buffer){
        temp_vec.push_back(buffer);
    }
    file.io.close();

    file.io.open(file.name, std::ios::out | std::ios::trunc); //vector - input -> file
    for(auto it = temp_vec.cbegin(); it != temp_vec.cend(); it++){
        if(*it == key->second){
            while(*it != input){
                file.io << *it << '\n';
                it++;
            }
            continue;
        }
        file.io << *it << '\n';
    }
    file.io.close();

    return 1;
}


Config::string_vec
Config::get_section(const SECTION section){
    if(!status())
        throw "Config not init exception"; // TODO - exception handling
    
    string_vec temp_vec;
    std::string buffer;
    auto key = section_string_map.find(section);
    
    file.io.open(file.name, std::ios::in); //file section -> vector
    while(file.io >> buffer && buffer != key->second);
    while(file.io >> buffer && !string_section_map.count(buffer))
        temp_vec.push_back(buffer);
    file.io.close();

    return temp_vec;
}


void
Config::clear(){
    file.name.clear();
    if(file.io.is_open())
        file.io.close();
}


bool
Config::status() const{
    if(file.name.empty())
        return 0;
    return 1;
}


//============
//==PRIVATE==
//==========


bool
Config::section_exist(const SECTION section){
    std::string buffer;
    auto key = section_string_map.find(section);

    while(file.io >> buffer)
        if(buffer == key->second)
            return 1;
    return 0;
}


bool
Config::is_repeat(const SECTION section, const std::string& input){
    std::string buffer;
    auto key = section_string_map.find(section);

    file.io.open(file.name, std::ios::in);
    while(file.io >> buffer)
        if(buffer == key->second)
            while((file.io >> buffer) && !string_section_map.count(buffer))
                if(buffer == input){
                    file.io.close();
                    return 1;
                }
    file.io.close();

    return 0;
}

