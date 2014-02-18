#include "Message.h"
Message::Message(int type):
  msgType_(type){
    
}

Message::Message(const IO_BUFFER& buf):
  msgLength_(buf[0]),
  msgType_(buf[1]){
    
}

void Message::doAction(MapController& mc){
  std::cout << "Recieved " << msgType_ << std::endl;
}
