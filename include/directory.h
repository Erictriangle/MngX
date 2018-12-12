#ifndef DIRECTORY_H
#define DIRECTORY_H


#include <fstream>
#include <string>

#include <boost/filesystem.hpp>


class Directory{
protected:
    struct{
        boost::filesystem::path directory;
        boost::filesystem::path file;
    } path;

    std::string username;

    
 public:
    Directory() = default;
    Directory(const std::string&);
    Directory(const Directory&);
    ~Directory() = default;

    Directory& operator=(const std::string&);
    Directory& operator=(const Directory&);

    void set_input(const std::string&);
    void copy(const Directory&);

    const std::string get_directory();
    const std::string get_filename();
    const std::string get_path();
    const std::string get_username();


protected:
    void clear();
    bool root();

};



#endif //DIRECTORY_H
