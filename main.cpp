#include "control.hpp"

//TODO - exceptions handling for all class

int main(int argc, char** argv)
{
	try
	{
		if(argc == 1)
		{
			mngx::screen::status();
			return 0;
		}

		mngx::Control control(argc, argv);
		mngx::Control::execConfigDefault();

		while(!control.empty() && control.status() &&
			mngx::Control::execCommand(control));

		if(!control.status())
			mngx::screen::incorrectFlag(control.incorrect());

	}
	catch(const std::system_error& e)
	{
		std::cout << e.what() << "\n";
	}
	catch(const char* e)
	{
		std::cout << e << "\n";
	}

	return 0;
}
