#include "control.h"

#include <iostream>


int main(int argc, char** argv)
{
    Control control(argc, argv);
    Directory directory;
    Config config(directory.get_default_config_path());

    if(!directory.default_config_file_exist())
        config.creat();
    
    if(argc == 1){
        screen::status();
        return 0;
    }

    if(!control.status()){
        while(!control.status())
            screen::incorrect_flag(control.get_incorrect_flag());
        return 0;
    }

    while(!control.empty() && control.status())
        Control::exec_command(control, directory, config);

    
    return 0;
}


