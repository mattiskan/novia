#include <iostream>
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

  for (;;) {
    boost::array<char, 128> buf;
    boost::system::error_code error;

    size_t len = socket.read_some(boost::asio::buffer(buf), error);

    if (error == boost::asio::error::eof)
      break; // Connection closed cleanly by peer.
    else if (error)
      throw boost::system::system_error(error); // Some other error.

    std::cout.write(buf.data(), len);
  }

  std::cout << "Client terminated" << std::endl;
}
