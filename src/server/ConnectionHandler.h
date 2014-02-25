#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H
#include <cstdio>
#include <iostream>
#include <chrono>
#include <thread>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "ClientConnection.h"
#include "../protocol/Message.h"

using boost::asio::local::stream_protocol;

#define SOCKET_FILE "bin/socket"

class ConnectionHandler {
public:
  ConnectionHandler(stream_protocol::endpoint ep);

  void start();
  std::vector<Message*> pollClientActions();

private:
  std::mutex safeAdd_;
  std::thread* ioServiceThread_;
  boost::asio::io_service ioService_;
  stream_protocol::acceptor acceptor_;
  std::vector<ClientConnection*> clients_;
  
  void run();
  void prepareForNewClient();
  void acceptClient(ClientConnection*, const boost::system::error_code&);

};

#endif
