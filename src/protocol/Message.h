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
  Message(int type);
  Message(const IO_BUFFER& buf);
  
  void doAction(MapController& mc);
  void send(); //todo?
};

#endif
