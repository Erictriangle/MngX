#define BOOST_TEST_MODULE ut_network
#include <boost/test/unit_test.hpp>

#include "network.hpp"


BOOST_AUTO_TEST_SUITE( network )

BOOST_AUTO_TEST_CASE( default )
{
  mngx::Netowrk network;

  network.connect("192.168.100.81");
  network.download("server");
}

BOOST_AUTO_TEST_SUITE_END()
