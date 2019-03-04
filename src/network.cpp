#include "network.hpp"


namespace mngx
{

Network::~Network()
{
  freeaddrinfo(servinfo);
  ::close(socket);
}


bool
Network::connect(const std::string& hostname)
{
  this->hostname = hostname;
  int status;
  addrinfo hints = getHints();
  addrinfo *ptr;
  

  if((status = getaddrinfo(hostname.c_str(), PORT, &hints, &servinfo)) != 0){
    log->report("getaddrinfo error: ", gai_strerror(status), ".");
    return 0;
  }

  for(ptr = servinfo; ptr != nullptr; ptr = ptr->ai_next){
    if((socket = ::socket(ptr->ai_family, ptr->ai_socktype,
        ptr->ai_protocol)) == -1){
      continue;
    }

    if(::connect(socket, ptr->ai_addr, ptr->ai_addrlen) == -1){
      continue;
    }

    break;
  }

  if(ptr == nullptr){
    log->report("Cannot establish connection with " + hostname + ".");
    return 0;
  }
  return 1;
}


void
Network::close()
{
  ::close(socket);
}


addrinfo
Network::getHints()
{
  addrinfo hints;
  hints.ai_flags = 0;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;
  hints.ai_addrlen = 0;
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;
  return hints;
}


} //namespace mngx
