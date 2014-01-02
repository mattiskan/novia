#include "Variables.h"

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

  void doAction(){
    
  }

  abstract void send();
}
