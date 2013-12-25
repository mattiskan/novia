#include <iostream>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

using boost::asio::local::stream_protocol;

int main(int argc, char** argv) {
  std::cout << "=== Client ===" << std::endl;


  boost::asio::io_service io_service;
  stream_protocol::endpoint ep("bin/socket");
  stream_protocol::socket socket(io_service);
  socket.connect(ep);
  
  for (;;) {
    boost::system::error_code error;
    boost::array<int, 1> buf1;
    buf1[0] = argv[1][0]-48;
    std::cout << "Wrote "<< buf1[0] << " to stream" << std::endl;
    boost::asio::write(socket, boost::asio::buffer(buf1), error);
    if(error){
      std::cout << "Ajfan " << error.message() << std::endl;
      std::exit(1);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    continue;

    boost::array<char, 128> buf;

    size_t len = socket.read_some(boost::asio::buffer(buf), error);
    buf[len] = '\0';

    if (error == boost::asio::error::eof)
      break; // Connection closed cleanly by peer.
    else if (error)
      throw boost::system::system_error(error); // Some other error.

    std::cout << buf.data() << std::endl;
  }

  std::cout << "Client terminated" << std::endl;
}
