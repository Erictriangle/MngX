#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <string>


namespace screen{
    
    void status();
    
    //=========
    //==HELP==
    //=======
    
    void help();
    void help_config();
    

    //==========
    //==INPUT==
    //========
    
    void incorrect_flag(const std::string& flag);
    void bad_arguments_number(const std::string& cmd);
    void incorrect_subcommand(const std::string& flag, const std::string& cmd);

};


#endif //SCREEN_H
