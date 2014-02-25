#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H
#include <vector>
#include <thread>
#include <array>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "../Common.h"
#include "../protocol/Message.h"


using boost::asio::local::stream_protocol;

class ClientConnection {

 public:
  ClientConnection(boost::asio::io_service&);
  ClientConnection(ClientConnection&&) = delete;

  std::vector<Message> getClientActions();

 private:
  std::mutex readLock_;
  std::vector<Message> actionQueue_;

  virtual void onReadEvent(IO_BUFFER readBuffer);
};


#endif
