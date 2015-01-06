#include "client_connection.h"

#include "protocol/messages.h"

namespace novia {
  ClientConnection::ClientConnection(int assigned_id) 
    : session_id_(assigned_id) {
  
  }

  int ClientConnection::user_id() const {
    return user_id_;
  }

  int ClientConnection::session_id() const {
    return session_id_;
  }
  
  bool ClientConnection::authenticated() const {
    return user_id_ != -1;
  }

  void ClientConnection::authenticate(int user_id) {
    user_id_ = user_id;
  }
  
  void ClientConnection::interpret_msg(std::string payload){
    InMessage* msg  = messages::in_message(payload);

    Controllers c;
    
    msg->instant_reply(c, *this);
  }

}
