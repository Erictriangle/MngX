#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "screen.hpp"
#include "log.hpp"

#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <algorithm>


namespace mngx
{
class Network
{
private:
  const char* PORT = "7747";
  const unsigned int MAXDATASIZE = 256;
  const unsigned int MAXFILENAMESIZE = 255;


public:
  Network() = default;
  ~Network();

  bool connect(const std::string& hostname);
  void close();

  bool send(const std::string& filename);
  bool received();

private:
  std::string hostname;
  int socket;
  addrinfo *servinfo;
  std::string filename;

  log::src::logger_mt& logger = mngLog::get();

private:
  addrinfo getHints();

}; //class Network
} //namespace mngx


#endif //NETWORK_HPP
