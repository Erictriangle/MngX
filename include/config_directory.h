#ifndef CONFIG_DIRECTORY_H
#define CONFIG_DIRECTORY_H


#include "directory.h"


class Config_Directory : Directory{  
    const std::string _FOLDER = "/.mngx/";
    const std::string _FILENAME = "MngConfig.txt";
    const std::string _EXTENSION = ".txt";

    struct{
        boost::filesystem::path directory;
        boost::filesystem::path file;
    } default_path;

    std::string username;
public:
    Config_Directory();
    ~Config_Directory() = default;

    std::string take_default_path();
    
private:
    void set_default_path();
    void check_default_path();

    std::string add_filename(const boost::filesystem::path&);
    std::string change_extension(const boost::filesystem::path&);
};



#endif //CONFIG_DIRECTORY_H
