#ifndef NOVIA_CLIENT_CONNECTION_H
#define NOVIA_CLIENT_CONNECTION_H

#include <string>
#include <functional>

namespace novia {

  class ClientConnection {
    typedef std::function<void (const std::string& msg)> SendFn;
    
  public:
    const int session_id_;
    int user_id_ = -1;    

    ClientConnection(int assigned_id);

    int user_id() const;
    int session_id() const;
    bool authenticated() const;

    void authenticate(int user_id);
    
    void interpret_msg(std::string payload);
  };

}

#endif
 
