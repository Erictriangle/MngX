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
    std::string error = gai_strerror(status);
    BOOST_LOG(logger) << "-=[ ERROR ]=- getaddrinfo: " << error << ".";
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
    BOOST_LOG(logger) << "-=[ ERROR ]=- Cannot establish connection with "
      << hostname << ".";
    return 0;
  }
  return 1;
}


bool
Network::send(const std::string& filename)
{
  this->filename = filename;
  if(::send(socket, filename.c_str(), filename.size()+1, 0) == -1){
    BOOST_LOG(logger) << "-=[ ERROR ]=- Failed attempt to send the package.";
    return 0;
  }
  return 1;
}


bool
Network::received()
{
  std::array<char, 255> buffer;
  auto file = std::make_unique<std::ofstream>(filename, std::ios::trunc);

  while(recv(socket, buffer.data(), MAXDATASIZE-1, 0) != -1){
    *file << buffer.data();
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
