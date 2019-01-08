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
	static bool is_file(const std::string&);
	static bool is_file(const Directory&);
	static bool is_directory(const std::string&);
	static bool is_directory(const Directory&);

public:
    Directory() = default;
    Directory(const std::string&);
    Directory(const Directory&);
    ~Directory() = default;

    Directory& operator=(const std::string&);
    Directory& operator=(const Directory&);

    void set_path(const std::string&); //!< change string on path and assign to directory out path
    void copy(const Directory&);

    const std::string get_directory() const; //!< return path.directory
    const std::string get_filename() const; //!< return path.file
    const std::string get_path() const; //!< return path.directory + path.file
    const std::string get_username() const; //!< return current username

    bool empty() const; //!< return path.directory.empty() 

protected:
    void clear();
    bool root();

};



#endif //DIRECTORY_H
