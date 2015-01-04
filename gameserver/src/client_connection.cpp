#include "client_connection.h"

#include "protocol/message_router.h"

namespace novia {
  ClientConnection::ClientConnection(int assigned_id) 
    : session_id_(assigned_id) {
  
  }


  void ClientConnection::interpret_msg(std::string payload){    
    Message* msg = message_router::read_message(payload);
    
    if (!msg->does_modification())
      message_router::invoke_now(msg, *this);
    else
      message_router::invoke_later(msg, *this);
  }

}
