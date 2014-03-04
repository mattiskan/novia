#include <iostream>
#include <cxxtest/TestSuite.h>
#include "../server/SocketCommunicator.h"
using boost::asio::local::stream_protocol;


#define TEST_SOCKET_FILE "bin/test_socket"


class CommunicatorTester: public SocketCommunicator {
 
 private:
  IO_BUFFER* initalDataPtr_;
  bool eventOccured;

  void onReadEvent(IO_BUFFER& readBuffer){
    eventOccured = true;
  }

 public:

 CommunicatorTester(boost::asio::io_service& ios, IO_BUFFER* transferedDataPtr)
   : SocketCommunicator(ios), eventOccured(false)
  {

  }
};

void run(boost::asio::io_service* ios){
  ios->run();
}

#define PRINT std::cout

class SocketCommunicatorClass : public CxxTest::TestSuite
{
 private:
  boost::asio::io_service ios;
  std::thread* ioServiceThread_;

 public:

  void setUp(){
    ::unlink(TEST_SOCKET_FILE);//remove preexisting
    stream_protocol::endpoint ep(TEST_SOCKET_FILE);
    stream_protocol::acceptor(ios, ep);
    ioServiceThread_ = new std::thread(run, &ios);
  }

  void testRecieve(){
    IO_BUFFER* buf = new IO_BUFFER;
    
  
  }

  void testRecieve1(){
    IO_BUFFER* buf = new IO_BUFFER;
    
  
  }

  void tearDown(){
    ::unlink(TEST_SOCKET_FILE);
    ios.stop();
    ios.reset();
    ioServiceThread_->join();
    delete ioServiceThread_;
  }
};
