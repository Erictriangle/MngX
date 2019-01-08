#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <vector>
#include <map>
#include <iterator>


/*!
 *\brief Manage config files
 *
 *
 *Config class should be initialize with path to config file.
 *For default path use a take_default_path() from a object of
 *Config_Directory class.
 *
 */


class Config{
    typedef std::vector<std::string> string_vec;

 public:
	 enum SECTION {
		 GLOBAL = 0,
		 MAJOR = 1,
		 SUB_CONFIG = 2,
		 ARCHIVE = 3
    };

private:
    static const std::map<SECTION, std::string> section_string_map;
    static const std::map<std::string, SECTION> string_section_map;
public:
    static const std::map<std::string, SECTION> input_section_map;

 public:
    Config();
    Config(const std::string&);
    ~Config();

    Config& operator=(const Config&);
    Config& operator=(const std::string&);
    
    void creat(); //!< create config file in assignment path
    void creat(const std::string&); //!< asssing path and creat config file
    bool add_row(const SECTION, const std::string&); //!< add one row in config file section
    bool remove_row(const SECTION, const std::string&); //!< remove one row in config file section

    string_vec get_section(const SECTION); //!< return section content from section

    void clear(); //!< clear assignment path
    bool status() const; //!< return file.name.empty()

 private:
    struct{
        std::fstream io;
        std::string name;
    } file;

    bool section_exist(const SECTION);
    bool is_repeat(const SECTION, const std::string&);
};


#endif //CONFIG_H
