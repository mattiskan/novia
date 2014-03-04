#ifndef TEST_MESSAGE_H
#define TEST_MESSAGE_H
#include "Message.h"
#include "iostream"

class TestMessage: public Message {
 public:

  TestMessage(const IO_BUFFER& buffer): Message(buffer) {
    //define how to recive
  }

  void send(){

  }

  void doAction(MapController& mc){
    std::cout << "Recieved test message: " << msgType_ << std::endl;
  }

};

#endif
