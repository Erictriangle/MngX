#ifndef DIRECTORY_STRUCTURE_H
#define DIRECTORY_STRUCTURE_H

#include "directory.h"

#include <vector>


class Directory_Structure : Directory{
private:
    typedef std::vector<std::string> string_vec;

    string_vec files;
    string_vec directories;
    
public:
    Directory_Structure() = default;
    Directory_Structure(const std::string&);
    ~Directory_Structure() = default;


    void map_directory(const std::string&);
};


#endif //DIRECTORY_STRUCTURE_H
