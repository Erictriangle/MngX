#include "directory_structure.h"


//==================
//==CONSTRUCTORES==
//================


Directory_Structure::Directory_Structure(const std::string& dir){
    map_directory(dir);
}


//===========
//==PUBLIC==
//=========


void
Directory_Structure::map_directory(const std::string& dir){
    namespace fs = boost::filesystem;

    fs::recursive_directory_iterator it(dir);
    fs::recursive_directory_iterator end;

    while(it != end){
        if(fs::is_directory(it->path()))
            directories.push_back(it->path().native());
        else
            files.push_back(it->path().native());
        it++;
    }
}
