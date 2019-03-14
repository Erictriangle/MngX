#include "network.hpp"


namespace mngx
{

Network::Network(const std::string hostname)
    : socket(io_service)
{
  this->hostname = hostname;
  socket.connect( tcp::endpoint( 
      boost::asio::ip::address::from_string(hostname), PORT));
}



void
Network::download(const std::string& filename)
{
  std::string path = "PACK-" + filename;
  boost::system::error_code error;
  boost::asio::write(socket,
      boost::asio::buffer(path, MAX_FILENAME_LENGTH), error);

  if(error){
    return;
  }

  boost::asio::streambuf buffer;
  path = PathConfig::getDefaultDirectory() + path;
  auto file = std::make_unique<std::ofstream>(path.c_str(),
      std::ios::binary | std::ios::trunc);

  boost::asio::read(socket, buffer,
      boost::asio::transfer_all(), error);

  const char* data = boost::asio::buffer_cast<const char*>(buffer.data());
  *file << data;
}


} //namespace mngx