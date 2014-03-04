#ifndef MSG_FACTORY_H
#define MSG_FACTORY_H

#include <memory>
#include "../server/Player.h"
#include "Message.h"
#include "../Common.h"



class MessageFactory {

 public:
  MessageFactory(){};
  MessageFactory(Player& communicatee);

  Message* createMessage(IO_BUFFER& messageContent);

 private:

  Player communicatee_;
  

};



#endif
