#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "path_config.hpp"

#include <iostream>
#include <fstream>
#include <memory>
#include <array>
#include <boost/bind.hpp>
#include <boost/asio.hpp>


using boost::asio::ip::tcp;


namespace mngx
{
static boost::asio::io_service io_service;    

class Network
{
private:
  const unsigned int PORT = 7747;
  const unsigned int MAX_FILENAME_LENGTH = 255;

public:
  Network() = delete;
  Network(const Network&) = delete;
  Network(const std::string hostname);

  void download(const std::string& filename);


private:
  tcp::socket socket;
  tcp::resolver::results_type endpoints;
  std::string hostname;

private:
  void handler(const boost::system::error_code&, std::size_t) {}

};
} //namespace mngx

#endif //NETWORK_HPP