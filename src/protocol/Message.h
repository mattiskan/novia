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
  /*  Message(int type); //send constructor
      Message(const IO_BUFFER& buf);//recieve constructor*/

  Message(int type): msgType_(type){
    
  }

  Message(const IO_BUFFER& buf): msgLength_(buf[0]),
    msgType_(buf[1]){
    
  }

  virtual void send()=0;
  virtual void recieve()=0; 
  virtual void doAction(MapController& mc) =0;

};

#endif
