#include <iostream>
#include "control.h"



int main(int argc, char** argv)
{
    Control control(argc, argv);
    
    if(argc == 1)
    {
        //TODO - screen::status();
        return 0;
    }

    if(!control.status())
    {
        //TODO - screen::incorrect_input();
        return 0;
    }

    Control::command cmd;
    while(!control.empty() && control.status())
    {
        cmd = control.pop_front();
        control.exec_command(cmd);
    }
    
    return 0;
}


