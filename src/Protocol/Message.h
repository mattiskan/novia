#ifndef MESSAGE_H
#define MESSAGE_H

#include "iostream"
#include "../Common.h"
#include "../server/MapController.h"
#include "../server/Building.h"

class Message {
private:
  int msgLength_;
  int msgType_;
public:
  Message(int type):
    msgType_(type){
    
  }

  Message(const IO_BUFFER& buf):
    msgLength_(buf[0]),
    msgType_(buf[1]){
    
  }
  
  //void doAction(MapController& mc) {
  void doAction(){
    std::cout << "Message " << msgType_ << " called" << std::endl;
    
  }

  void send(); //todo?
};

#endif
