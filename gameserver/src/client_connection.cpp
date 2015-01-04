#include "client_connection.h"

#include "protocol/message_router.h"

#include <unordered_map>
#include <string>

std::unordered_map<std::string, int> valid_users = {
  { "mattis", 1337},
  { "axel", 4711},
  { "test", 123}
};

namespace novia {
  
  ClientConnection::ClientConnection(int assigned_id, SendFn& send_fn) 
    : session_id_(assigned_id),
      send(send_fn){
  
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
    
  bool ClientConnection::authenticate(const std::string& username,
				      const std::string& password) {
    if (valid_users.count(username) == 1) {
      user_id_ = valid_users.at(username);
    }

    return authenticated();
  }

  void ClientConnection::interpret_msg(std::string payload){    
    Message* msg = message_router::read_message(payload);
    
    if (!msg->does_modification())
      message_router::invoke_now(msg, *this);
    else
      message_router::invoke_later(msg, *this);
  }


}
