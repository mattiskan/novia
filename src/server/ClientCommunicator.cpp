#include "ClientCommunicator.h"
#include <iostream>

ClientCommunicator::ClientCommunicator(boost::asio::io_service& ioService)
  :socket_(ioService) {

}

void ClientCommunicator::start(){
    boost::asio::async_read(socket_, boost::asio::buffer(readBuffer_),			    boost::bind(&ClientCommunicator::read, this, _1, _2));

}

std::vector<int> ClientCommunicator::getClientActions(){
  readLock_.lock();
  std::vector<int> copy(actionQueue_);
  actionQueue_.clear();
  readLock_.unlock();
  return copy;
}

void ClientCommunicator::read(const boost::system::error_code& err, 
			      std::size_t readCount) {
  if(readCount > 0){
    readLock_.lock();
    actionQueue_.push_back(readBuffer_[0]);
    readLock_.unlock();
  }

  if(!err){ // then read next message
    boost::asio::async_read(socket_, boost::asio::buffer(readBuffer_),			    boost::bind(&ClientCommunicator::read, this, _1, _2));
  } else {
    std::cout << "Couldn't read client buffer:" << std::endl << "\t" <<err.message();
  }
}

