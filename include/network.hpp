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
  const unsigned int MAXDATASIZE = 100;


public:
  Network() = default;
  ~Network();

  bool connect(const std::string& hostname);
  void close();

  

private:
  std::string hostname;
  int socket;
  addrinfo *servinfo;
  Log *log = Log::instance();

  addrinfo getHints();

}; //class Network
} //namespace mngx


#endif //NETWORK_HPP
