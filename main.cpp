#include "log.hpp"
#include "control.hpp"



int main(int argc, char** argv)
{
  try
  {
    if(argc == 1){
	    mngx::screen::status();
	    return 0;
	  }

	mngx::Control control(argc, argv);
  mngx::log::init();
  mngx::Config * config = mngx::Config::instance(); //only for creating defaul path

	while(!control.empty() && control.status() 
      && mngx::Control::execCommand(control));

    
  }
  catch(const std::system_error& e)
  {
    std::cout << e.what() << "\n";
  }
  catch(const char* e)
  {
  }

  return 0;
}
