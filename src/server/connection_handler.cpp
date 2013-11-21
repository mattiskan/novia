#include <cstdio>
#include <iostream>
#include <chrono>
#include <thread>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
using boost::asio::local::stream_protocol;

#define SOCKET_FILE "bin/socket"


class ConnectionHandler {
private:
  boost::asio::io_service io_service;
  stream_protocol::socket socket;
  stream_protocol::acceptor acceptor;
public:
  ConnectionHandler(stream_protocol::endpoint ep) : socket(io_service),  acceptor(io_service, ep)
    { }
  
  void run() {
    std::cout << "Server started" << std::endl;
    acceptor.accept(socket);
    std::cout << "Client connected" << std::endl;

    boost::system::error_code ignored_error;
    for( ; ; ){
      boost::asio::write(socket, boost::asio::buffer("Welcome!"), ignored_error);
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  }

};


int main() {
  ::unlink(SOCKET_FILE); // Remove previous binding.
  stream_protocol::endpoint ep(SOCKET_FILE);
  
  ConnectionHandler srv(ep);
  srv.run();

  return 0;
}
