#ifndef CONFIG_H
#define CONFIG_H


#include <fstream>
#include <vector>
#include <map>
#include <iostream> //std::cerr
#include <algorithm> //std::reverse std::find
#include <boost/filesystem.hpp>


namespace filesystem = boost::filesystem;


class Config
{
private:
    typedef std::vector<filesystem::path> path_vec;
    typedef std::vector<std::string> string_vec;
    
    struct
    {
        std::fstream io;
        filesystem::path dir;
        filesystem::path file;
        filesystem::path full;
    } path;

public:    
    enum SECTION
    {
        GLOBAL = 0,
        SUB_CONFIG = 1,
        TEXT_MODULE = 2
    };

    
    const std::map<SECTION, std::string> sections_map
    {
        { GLOBAL, ".mngx"},
        { SUB_CONFIG, ".sub_config" },
        { TEXT_MODULE, ".text_module" }
    };

    const std::map<std::string, SECTION> reverse_section_map
    {
        { ".mngx", GLOBAL },
        { ".sub_config", SUB_CONFIG },
        { ".text_module", TEXT_MODULE }
    };

private:
   

    
public:
    Config();
    ~Config();

    bool set_path();
    bool set_path(const std::string&);
    bool set_path(const filesystem::path&);

    bool creat();
    void add_row(const SECTION, const std::string&);
    void remove_row(const SECTION, const std::string&);

    void take_directories(const SECTION, path_vec&);
    
private:
    void manage_input(const filesystem::path&);
    filesystem::path default_dir();
    
    bool is_repeat(const std::string&, const std::string&);
    
    template<class Dir, class File = std::string>
        void assign_path(const Dir& dir, const File& file = "MNGConfig.txt")
    {
        path.dir = dir;
        path.file = file;
        path.full = path.dir;
        path.full += path.file;
    }
};



#endif //CONFIG_H
