#include "control.h"

#include <iostream>
#include <memory>


int main(int argc, char** argv)
{
    if(argc == 1){
        screen::status();
        return 0;
    }

    try{
        Control control(argc, argv);
        Config_Directory config_directory;

        
        
        while(!control.empty() && control.status()){
            Control::exec_command(control, config_directory);
        }
    }
    catch(const std::string e){
        std::cerr << "Do zrobienia: " << e << std::endl;
    }
    
    return 0;
}


