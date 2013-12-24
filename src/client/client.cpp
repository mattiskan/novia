#include <iostream>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

using boost::asio::local::stream_protocol;

int main() {
  std::cout << "=== Client ===" << std::endl;


  boost::asio::io_service io_service;
  stream_protocol::endpoint ep("bin/socket");
  stream_protocol::socket socket(io_service);
  socket.connect(ep);
  
  for (int i=1;;i++) {
    boost::system::error_code error;
    boost::array<int, 2> buf1;
    buf1[0] = i;
    boost::asio::write(socket, boost::asio::buffer(buf1)); 
    std::cout << "Wrote "<< buf1[0] << " to stream" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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
