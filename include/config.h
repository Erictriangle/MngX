#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <vector>
#include <map>
#include <iterator>


class Config{
    typedef std::vector<std::string> string_vec;

 public:
    enum SECTION{
        GLOBAL = 0,
        MAJOR = 1,
        SUB_CONFIG = 2
    };

private:
    const std::map<SECTION, std::string> section_string_map{
        { GLOBAL, ".mngx" },
        { MAJOR, ".major" },
        { SUB_CONFIG, ".sub-config"}
    };

    const std::map<std::string, SECTION> string_section_map{
        { ".mngx", GLOBAL },
        { ".major", MAJOR },
        { ".sub-config", SUB_CONFIG }
    };

 public:
    Config();
    Config(const std::string&);
    ~Config();

    Config& operator=(const Config&);
    Config& operator=(const std::string&);
    
    void creat();
    void creat(const std::string&);
    bool add_row(const SECTION, const std::string&);
    bool remove_row(const SECTION, const std::string&);

    string_vec get_section(const SECTION);
    std::string get_major();
    
    void clear();
    bool status() const;

 private:
    struct{
        std::fstream io;
        std::string name;
    } file;

    bool section_exist(const SECTION);
    bool is_repeat(const SECTION, const std::string&);
};


#endif //CONFIG_H
