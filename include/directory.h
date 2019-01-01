#ifndef DIRECTORY_H
#define DIRECTORY_H


#include <fstream>
#include <string>

#include <boost/filesystem.hpp>


/*!
 *\brief Manage directory and path
 *
 *Directory contain directory our directory and filename.
 *
 */


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

    void set_path(const std::string&); //!< change string on path and assign to directory out path
    void copy(const Directory&);

    const std::string get_directory(); //!< return path.directory
    const std::string get_filename(); //!< return path.file
    const std::string get_path(); //!< return path.directory + path.file
    const std::string get_username(); //!< return current username

    bool empty(); //!< return path.directory.empty() 
    bool is_file();
protected:
    void clear();
    bool root();

};



#endif //DIRECTORY_H
