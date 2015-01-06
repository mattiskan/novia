#ifndef NOVIA_CLIENT_CONNECTION_H
#define NOVIA_CLIENT_CONNECTION_H

#include <string>
#include <functional>

namespace novia {

  class ClientConnection {
  public:
    typedef std::function<void (int session_id, const std::string& msg)> SendFn;
    
    ClientConnection(int assigned_id, SendFn& send_fn);

    int user_id() const;
    int session_id() const;
    bool authenticated() const;

    void authenticate(int user_id);
    void interpret_msg(std::string payload);
    void send(std::string msg);

  private:
    const int session_id_;
    int user_id_ = -1;
    SendFn send_;
  };

}

#endif
 
