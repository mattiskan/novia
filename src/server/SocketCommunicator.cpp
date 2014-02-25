#include "SocketCommunicator.h"
#include <iostream>

SocketCommunicator::SocketCommunicator(boost::asio::io_service& ioService)
    :socket_(ioService)
{

}

void SocketCommunicator::start(){
  //queue next read event to call this->read()
    boost::asio::async_read(socket_, boost::asio::buffer(readBuffer_),
			    boost::bind(&SocketCommunicator::handleRead, this, _1, _2));
}


void SocketCommunicator::handleRead(const boost::system::error_code& err, std::size_t readCount) {

  if(readCount > 0)
    onReadEvent(readBuffer_);

  if(!err){ // then read next message
    boost::asio::async_read(socket_, boost::asio::buffer(readBuffer_),
			    boost::bind(&SocketCommunicator::handleRead, this, _1, _2));
  } else {
    std::cout << "Client buffer failed:" << std::endl << "\t" <<err.message();
  }
}

