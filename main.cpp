#include "control.h"

#include <iostream>
#include <memory>


int main(int argc, char** argv){
	try {
		if(argc == 1){
			screen::status();
			return 0;
		}

		Control control(argc, argv);
		Config_Directory config_directory;
		Config config(config_directory.get_path());

		//creat default config file if doesn't exist.
		Control::exec_config_default(config, config_directory); 

		while(!control.empty() && control.status())
			Control::exec_command(control, config, config_directory);
	}
	catch(const std::system_error& e){
		std::cout << e.what() << std::endl;
	}
	catch(const std::string e){
	std::cerr << "Do zrobienia: " << e << std::endl;
	}
    
	return 0;
}


