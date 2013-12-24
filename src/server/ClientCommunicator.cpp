#include "ClientCommunicator.h"
#include <iostream>

ClientCommunicator::ClientCommunicator(boost::asio::io_service& ioService)
  :socket_(ioService) {

}


void ClientCommunicator::start(){
    boost::asio::async_read(socket_, boost::asio::buffer(readBuffer_),			    boost::bind(&ClientCommunicator::read, this, _1, _2));

}

std::vector<int> ClientCommunicator::getClientActions(){
  readLock.lock();
  std::vector<int> copy(actionQueue_);
  actionQueue_.clear();
  readLock.unlock();
  return copy;
}

void ClientCommunicator::read(const boost::system::error_code& err, 
			      std::size_t readCount) {
  std::cout << "readc" << readCount << std::endl;
  if(readCount > 0){
    readLock.lock();
    std::cout << "Read " <<  readBuffer_[0] << std::endl;
    //TODO
    actionQueue_.push_back(readBuffer_[0]);
    readLock.unlock();
  }

  if(!err){ // then read next message
    std::cout << "reading" << std::endl;
    boost::asio::async_read(socket_, boost::asio::buffer(readBuffer_),			    boost::bind(&ClientCommunicator::read, this, _1, _2));
    std::cout << "read" << std::endl;
  } else {
    std::cout << "An error has occured:" << std::endl << err.message();
  }
}

