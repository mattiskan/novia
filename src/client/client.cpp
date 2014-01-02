#include <iostream>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include "../Common.h"

void flushBuffer();
void writeRepeatedly(char);
void forwardInput();

IO_BUFFER buf;
boost::asio::io_service myIoService;
boost::asio::local::stream_protocol::endpoint ep("bin/socket");
boost::asio::local::stream_protocol::socket mySocket(myIoService);

int main(int argc, char** argv) {
  mySocket.connect(ep);

  if(argc == 2)
    writeRepeatedly(argv[1][0]-48);
  else
    forwardInput();
}

void writeRepeatedly(char c){
  buf[0] = 1; // length 1 char
  buf[1] = c;
  while(true) {    
    flushBuffer();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

void forwardInput(){
  char* input = new char[256];
  while(true) {
    std::cin >> input;
    buf[0] = std::strlen( input );
    strcpy( &buf[1], input);

    flushBuffer();
  }
}

void flushBuffer(){
  boost::system::error_code error;
  boost::asio::write(mySocket, boost::asio::buffer(buf), error);
  if(error){
    std::cout << "Ajfan " << std::endl <<"\t"<< error.message() << std::endl;
    std::exit(1);
  }
}
