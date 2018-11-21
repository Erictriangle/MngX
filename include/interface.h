#ifndef INTERFACE_H
#define INTERFACE_H


#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>


class Config;


class Interface
{
    typedef boost::filesystem::path path;
    
public:
    enum FLAGS
    {
     GLOBAL = 0,
     TEXT = 1,
    };


    virtual bool take_directories(const path&);
    virtual bool take_directories(const std::vector<path&>);
};



#endif //ifndef INTERFACE_H
