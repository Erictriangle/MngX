#define BOOST_TEST_MODULE ut_path
#include <boost/test/unit_test.hpp>

#include "path_config.hpp"
#include "path_backup.hpp"


BOOST_AUTO_TEST_SUITE( ut_PathConfig )

std::string currentPath = boost::filesystem::current_path().native();
std::string username = getenv("USER");

BOOST_AUTO_TEST_CASE( constructors )
{
  mngx::PathConfig empty;
  mngx::PathConfig absolute("/bin");
  mngx::PathConfig absoluteSlash("/bin/");
  mngx::PathConfig absoluteFile("/bin/mkdir");
  mngx::PathConfig relative("src");
  mngx::PathConfig relativeSlash("src/");
  mngx::PathConfig relativeDirectoryFile("src/control.cpp");
  mngx::PathConfig relativeFile("CMakeLists.txt");

  BOOST_TEST(empty.path().empty());
  BOOST_TEST(!absolute.path().compare("/bin/MngConfig.txt"));
  BOOST_TEST(!absoluteSlash.path().compare("/bin/MngConfig.txt"));
  BOOST_TEST(!absoluteFile.path().compare("/bin/mkdir"));
  BOOST_TEST(!relative.path().compare(currentPath + "/src/MngConfig.txt"));
  BOOST_TEST(!relativeSlash.path().compare( currentPath + "/src/MngConfig.txt"));
  BOOST_TEST(!relativeDirectoryFile.path().compare(currentPath + "/src/control.cpp"));
  BOOST_TEST(!relativeFile.path().compare(currentPath + "/CMakeLists.txt"));

  BOOST_TEST(!empty.defaultPath().compare("/home/" + username + "/.mngx/MngConfig.txt"));
  BOOST_TEST(!relativeSlash.defaultPath().compare("/home/" + username + "/.mngx/MngConfig.txt"));
}


BOOST_AUTO_TEST_CASE( operatorsAndAssingment )
{
  mngx::PathConfig empty;
  mngx::PathConfig origin1("/bin");
  mngx::PathConfig origin2("CMakeLists.txt");
  mngx::PathConfig target = empty;
  mngx::PathConfig target1 = origin1;
  mngx::PathConfig target2;
  target2.path(origin2);

  BOOST_TEST(target.path().empty());
  BOOST_TEST(!target1.path().compare("/bin/MngConfig.txt"));
  BOOST_TEST(!target2.path().compare(currentPath + "/CMakeLists.txt"));

  BOOST_TEST(!target1.defaultPath().compare("/home/" + username + "/.mngx/MngConfig.txt"));
}


BOOST_AUTO_TEST_CASE( methods )
{
  mngx::PathConfig example1("/bin/");
  mngx::PathConfig example2("src/control.cpp");

  BOOST_TEST(!example1.directory().compare("/bin/"));
  BOOST_TEST(!example2.directory().compare(currentPath + "/src"));

  BOOST_TEST(!example1.username().compare(username));
  BOOST_TEST(!example2.username().compare(username));

  BOOST_TEST(!example1.filename().compare("MngConfig.txt"));
  BOOST_TEST(!example2.filename().compare("control.cpp"));

  mngx::PathConfig empty;
  BOOST_TEST(empty.empty());
}


BOOST_AUTO_TEST_SUITE_END() //ut_pathConfig


BOOST_AUTO_TEST_SUITE( ut_PathBackup )

std::string currentPath = boost::filesystem::current_path().native();
std::string username = getenv("USER");

BOOST_AUTO_TEST_CASE( constructors )
{
  mngx::PathBackup empty;
  mngx::PathBackup absolute("/bin");
  mngx::PathBackup absoluteSlash("/bin/");
  mngx::PathBackup absoluteFile("/bin/mkdir");
  mngx::PathBackup relative("src");
  mngx::PathBackup relativeSlash("src/");
  mngx::PathBackup relativeDirectoryFile("src/control.cpp");
  mngx::PathBackup relativeFile("CMakeLists.txt");

  BOOST_TEST(empty.path().empty());
  BOOST_TEST(!absolute.path().compare("/bin/"));
  BOOST_TEST(!absoluteSlash.path().compare("/bin/"));
  BOOST_TEST(!absoluteFile.path().compare("/bin/mkdir"));
  BOOST_TEST(!relative.path().compare(currentPath + "/src/"));
  BOOST_TEST(!relativeSlash.path().compare( currentPath + "/src/"));
  BOOST_TEST(!relativeDirectoryFile.path().compare(currentPath + "/src/control.cpp"));
  BOOST_TEST(!relativeFile.path().compare(currentPath + "/CMakeLists.txt"));
}

BOOST_AUTO_TEST_CASE( methods )
{
  mngx::PathBackup example1("/bin/");
  mngx::PathBackup example2("src/control.cpp");

  BOOST_TEST(!example1.directory().compare("/bin/"));
  BOOST_TEST(!example2.directory().compare(currentPath + "/src"));

  BOOST_TEST(!example1.username().compare(username));
  BOOST_TEST(!example2.username().compare(username));

  BOOST_TEST(example1.filename().empty());
  BOOST_TEST(!example2.filename().compare("control.cpp"));

  mngx::PathBackup empty;
  BOOST_TEST(empty.empty());
}

BOOST_AUTO_TEST_SUITE_END() //ut_PathBackup
