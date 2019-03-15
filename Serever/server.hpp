#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <fstream>
#include <memory>
#include <array>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>


using namespace boost::asio;
using ip::tcp;


class Connection
    : public boost::enable_shared_from_this<Connection>
{
private:
  static const unsigned int MAX_LENGTH = 256;

public:
  typedef boost::shared_ptr<Connection> pointer;

  Connection(boost::asio::io_service& io_service)
    : socket(io_service){}

  static pointer create(boost::asio::io_service& io_service){
    return pointer(new Connection(io_service));
  }

  tcp::socket& getSocket(){
    return socket;
  }
  
  void start(){
    socket.async_read_some(
      boost::asio::buffer(buffer, MAX_LENGTH-1),
      boost::bind(
        &Connection::readHandler,
        shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred
    ));

    auto file 
      = std::make_unique<std::ifstream>(buffer, std::ios::binary);
    while(file->read(buffer, MAX_LENGTH).gcount() > 0){
      socket.async_write_some(
        boost::asio::buffer(buffer, MAX_LENGTH-1),
        boost::bind(
          &Connection::writeHandler,
          shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred)
      );
    }
  }

private:
  tcp::socket socket;
  char buffer[MAX_LENGTH];

private:
  void readHandler(const boost::system::error_code&, size_t) {}
  void writeHandler(const boost::system::error_code&, size_t) {}
};


class Server
{
private:
  void start(){
    Connection::pointer connection 
      = Connection::create(acceptor.get_io_service());

    acceptor.async_accept(connection->getSocket(),
      boost::bind(&Server::acceptHandler, this, connection,
      boost::asio::placeholders::error));
  }

public:
  Server(boost::asio::io_service& io_service)
      : acceptor(io_service, tcp::endpoint(tcp::v4(), 7747)){
    start();
  }

  void acceptHandler(Connection::pointer connection,
      const boost::system::error_code& err){
    if(!err){
      connection->start();
    }
    start();
  }

private:
  tcp::acceptor acceptor;

};


#endif //SERVER_HPP