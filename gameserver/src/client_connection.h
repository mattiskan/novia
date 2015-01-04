#ifndef NOVIA_CLIENT_CONNECTION_H
#define NOVIA_CLIENT_CONNECTION_H

#include <string>
#include <functional>
#include "protocol/authentification_message.h"

namespace novia {

  typedef std::function<void (const std::string& msg)> SendFn;
  
  class ClientConnection {
    const int session_id_;
    int user_id_ = -1;
    
  public:    
    ClientConnection(int assigned_id, SendFn& send_fn);

    int user_id() const;
    int session_id() const;
    bool authenticated() const;
    
    bool authenticate(const std::string& username, const std::string& password);
    void interpret_msg(std::string payload);

    SendFn send;
  };

}

#endif
 
