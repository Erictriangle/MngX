#ifndef TEXT_MODULE_H
#define TEXT_MODULE_H


#include "interface.h"


class Text_Module: public Interface{
    typedef boost::filesystem::path path;
    
    
public:
    Text_Module() = default;
    Text_Module(const std::vector<path>&);
    Text_Module(const Config&);
    ~Text_Module() = default;

    bool take_directories(const path&);
    bool take_directories(const std::vector<path>&);

private:
    std::vector<path> dir_vec;
    
};


#endif //TEXT_MODULE_H
