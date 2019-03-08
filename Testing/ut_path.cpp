#define BOOST_TEST_MODULE ut_path
#include <boost/test/unit_test.hpp>

#include "path.hpp"
#include "path_config.hpp"
#include "path_log.hpp"


BOOST_AUTO_TEST_SUITE( ut_Path )

std::string currentPath = boost::filesystem::current_path().native();
std::string username = getenv("USER");

BOOST_AUTO_TEST_CASE( constructors )
{
  mngx::Path empty;
  mngx::Path absolute("/bin");
  mngx::Path absoluteSlash("/bin/");
  mngx::Path absoluteFile("/bin/mkdir");
  mngx::Path relativeSlash("src/");
  mngx::Path relativeDirectoryFile("src/control.cpp");
  mngx::Path relativeFile("CMakeLists.txt");

  BOOST_TEST(empty.empty());
  BOOST_TEST(absolute.getPath() == "/bin/");
  BOOST_TEST(absoluteSlash.getPath() == "/bin/");
  BOOST_TEST(absoluteFile.getPath() == "/bin/mkdir");
  BOOST_TEST(relativeSlash.getPath() == (currentPath + "/src/"));
  BOOST_TEST(relativeDirectoryFile.getPath() == (currentPath + "/src/control.cpp"));
  BOOST_TEST(relativeFile.getPath() == (currentPath + "/CMakeLists.txt"));
}

BOOST_AUTO_TEST_CASE( methods )
{
  mngx::Path example1("/bin/");
  mngx::Path example2("src/control.cpp");

  BOOST_TEST(example1.getDirectory() == "/bin/");
  BOOST_TEST(example2.getDirectory() == (currentPath + "/src"));

  BOOST_TEST(example1.getUsername() == username);
  BOOST_TEST(example2.getUsername() == username);

  BOOST_TEST(example1.getFilename().empty());
  BOOST_TEST(example2.getFilename() == "control.cpp");
}

BOOST_AUTO_TEST_SUITE_END() //ut_Path




BOOST_AUTO_TEST_SUITE( ut_PathConfig )

std::string currentPath = boost::filesystem::current_path().native();
std::string username = getenv("USER");

BOOST_AUTO_TEST_CASE( constructors )
{
  mngx::PathConfig empty;
  mngx::PathConfig absolute("/bin");
  mngx::PathConfig absoluteSlash("/bin/");
  mngx::PathConfig absoluteFile("/bin/mkdir");
  mngx::PathConfig relativeSlash("src/");
  mngx::PathConfig relativeDirectoryFile("src/control.cpp");
  mngx::PathConfig relativeFile("CMakeLists.txt");

  BOOST_TEST(!empty.empty());
  BOOST_TEST(absolute.getPath() == "/bin/MngConfig.txt");
  BOOST_TEST(absoluteSlash.getPath() == "/bin/MngConfig.txt");
  BOOST_TEST(absoluteFile.getPath() == "/bin/mkdir");
  BOOST_TEST(relativeSlash.getPath() == ( currentPath + "/src/MngConfig.txt"));
  BOOST_TEST(relativeDirectoryFile.getPath() == (currentPath + "/src/control.cpp"));
  BOOST_TEST(relativeFile.getPath() == (currentPath + "/CMakeLists.txt"));

  BOOST_TEST(empty.getDefaultPath() == ("/home/" + username + "/.mngx/MngConfig.txt"));
  BOOST_TEST(relativeSlash.getDefaultPath() == ("/home/" + username + "/.mngx/MngConfig.txt"));
}


BOOST_AUTO_TEST_CASE( operatorsAndAssingment )
{
  mngx::PathConfig empty;
  mngx::PathConfig origin1("/bin");
  mngx::PathConfig origin2("CMakeLists.txt");
  mngx::PathConfig target = empty;
  mngx::PathConfig target1 = origin1;
  mngx::PathConfig target2;
  target2.setPath(origin2);

  BOOST_TEST(!target.empty());
  BOOST_TEST(target1.getPath() == "/bin/MngConfig.txt");
  BOOST_TEST(target2.getPath() == (currentPath + "/CMakeLists.txt"));

  BOOST_TEST(target1.getDefaultPath() == ("/home/" + username + "/.mngx/MngConfig.txt"));
}


BOOST_AUTO_TEST_CASE( methods )
{
  mngx::PathConfig example1("/bin/");
  mngx::PathConfig example2("src/control.cpp");

  BOOST_TEST(example1.getDirectory() == "/bin/");
  BOOST_TEST(example2.getDirectory() == (currentPath + "/src"));

  BOOST_TEST(example1.getUsername() == username);
  BOOST_TEST(example2.getUsername() == username);

  BOOST_TEST(example1.getFilename() == "MngConfig.txt");
  BOOST_TEST(example2.getFilename() == "control.cpp");
}


BOOST_AUTO_TEST_SUITE_END() //ut_pathConfig



