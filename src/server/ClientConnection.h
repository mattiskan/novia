#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H
#include <vector>
#include <mutex>
#include "SocketCommunicator.h"
#include "../Common.h"
#include "../protocol/MessageFactory.h"

using boost::asio::local::stream_protocol;

class ClientConnection : public SocketCommunicator {

 public:
  ClientConnection(boost::asio::io_service&);
  ClientConnection(ClientConnection&&) = delete;

  std::vector<Message*> getClientActions();

 private:
  std::mutex readLock_;
  std::vector<Message*> actionQueue_;
  MessageFactory msgFactory_;
  virtual void onReadEvent(IO_BUFFER& readBuffer);
};

#endif
