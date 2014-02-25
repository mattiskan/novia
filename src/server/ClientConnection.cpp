#include "ClientConnection.h"
#include <iostream>

ClientConnection::ClientConnection(boost::asio::io_service& ioService)
  :SocketCommunicator(ioService)
{

}

std::vector<Message*> ClientConnection::getClientActions(){
  readLock_.lock();

  std::vector<Message*> copy(actionQueue_);
  actionQueue_.clear();

  readLock_.unlock();
  return copy;
}


void ClientConnection::onReadEvent(IO_BUFFER readBuffer){
  readLock_.lock();

  //actionQueue_.emplace_back(readBuffer);

  readLock_.unlock();
}
