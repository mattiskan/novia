#ifndef SOCKET_COMMUNICATOR_H
#define SOCKET_COMMUNICATOR_H
#include <vector>
#include <thread>
#include <array>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "../Common.h"
#include "../protocol/Message.h"


using boost::asio::local::stream_protocol;

class SocketCommunicator {

 public:
  stream_protocol::socket socket_;
  //constructors
  SocketCommunicator(boost::asio::io_service&);
  SocketCommunicator(SocketCommunicator&&) = delete;

  void start();

 private:
  IO_BUFFER readBuffer_;
  std::thread readThread_;

  void handleRead(const boost::system::error_code&, std::size_t);

  virtual void onReadEvent(IO_BUFFER readBuffer) = 0; //abstract definition
};


#endif
