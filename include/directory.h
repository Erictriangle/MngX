#ifndef DIRECTORY_H
#define DIRECTORY_H


#include <fstream>

#include <boost/filesystem.hpp>


class Directory{
    typedef boost::filesystem::path path;

    //Data
    const std::string FILENAME = "MngConfig.txt";

    struct{
        std::string directory;
        std::string path;
    } config, default_config;

    std::string username;

    //Constructors
 public:
    Directory();
    Directory(const std::string&);
    ~Directory() = default;
private:
    void set_default_config_path();

    //Operators
public:
    Directory& operator=(const Directory&);
    Directory& operator=(const std::string&);

    //Method
public:
    void set_config_path(const std::string&);
    
    const std::string get_default_config_path();
    const std::string get_config_path();

    bool default_config_file_exist();
    
private:
    bool is_root();
    std::string add_filename(const path&);
    std::string change_extension(const path&);

};


#endif //DIRECTORY_H
