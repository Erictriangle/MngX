#define BOOST_TEST_MODULE ut_config
#include <boost/test/unit_test.hpp>


#include "config.hpp"
#include <iostream>
#include <boost/filesystem.hpp>


BOOST_AUTO_TEST_SUITE( Config )

BOOST_AUTO_TEST_CASE( singleton )
{
  mngx::log::init();
  mngx::Config* config1 = mngx::Config::instance();
  mngx::Config* config2 = mngx::Config::instance();
  mngx::Config* copy(config1);

  BOOST_TEST( config1 == config2 );
  BOOST_TEST( copy == config1 );
}


BOOST_AUTO_TEST_CASE( methods )
{
  mngx::log::init();
  std::string user = getenv("USER");
  std::string currentPath = boost::filesystem::current_path().native();

  std::vector<std::string> global{
    "Wrong",
    "Date=09.01.2014",
    "Test=True"
  };

  std::vector<std::string> archive{
    "PACK-Test2",
    "/home/" + user,
    "/home",
    "PACK-Test",
    "/home/" + user,
    "/home"
  };

  mngx::Config* config = mngx::Config::instance();
  config->creat("MngConfig.txt");
  config->load("MngConfig.txt");

  BOOST_TEST(config->addRow(mngx::Config::GLOBAL, "Test=True"));
  BOOST_TEST(config->addRow(mngx::Config::GLOBAL, "Date=09.01.2014"));
  BOOST_TEST(config->addRow(mngx::Config::GLOBAL, "Wrong"));
  BOOST_TEST(!config->addRow(mngx::Config::GLOBAL, "Wrong"));

  BOOST_TEST(config->creatPack("Test"));
  BOOST_TEST(!config->creatPack("Test"));
  BOOST_TEST(config->creatPack("Test2"));

  BOOST_TEST(config->addToPack("Test", "/home"));
  BOOST_TEST(config->addToPack("Test", "/home/" + user));
  BOOST_TEST(!config->addToPack("Test", "/home"));
  BOOST_TEST(!config->addToPack("Test", "/home/" + user));

  BOOST_TEST(config->addToPack("Test2", "/home"));
  BOOST_TEST(config->addToPack("Test2", "/home/" + user));
  BOOST_TEST(!config->addToPack("Test2", "/home"));
  BOOST_TEST(!config->addToPack("Test2", "/home/" + user));

  std::vector<std::string> globalFromFile =
    config->getSection(mngx::Config::GLOBAL);
  std::vector<std::string> archiveFromFile =
    config->getSection(mngx::Config::ARCHIVE);

  BOOST_TEST( global == globalFromFile );
  BOOST_TEST( archive == archiveFromFile );
  for(auto a : archiveFromFile)
    std::cout << a << "\n";

  global.pop_back();
  archive.pop_back();

  BOOST_TEST(config->removeRow(mngx::Config::GLOBAL, "Test=True"));
  BOOST_TEST(!config->removeRow(mngx::Config::GLOBAL, "Test=True"));

  BOOST_TEST(config->removeFromPack("Test", "/home"));
  BOOST_TEST(!config->removeFromPack("Test", "/home"));

  globalFromFile = config->getSection(mngx::Config::GLOBAL);
  archiveFromFile = config->getSection(mngx::Config::ARCHIVE);

  BOOST_TEST( global == globalFromFile );
  BOOST_TEST( archive == archiveFromFile );

  config->addToPack("Test", "/home");
  BOOST_TEST(config->removePack("Test"));
  BOOST_TEST(!config->removePack("Test"));
  archive.pop_back();
  archive.pop_back();

  archiveFromFile = config->getSection(mngx::Config::ARCHIVE);
  BOOST_TEST( archive == archiveFromFile );

  boost::filesystem::remove("MngConfig.txt");
}


BOOST_AUTO_TEST_SUITE_END() //Config
