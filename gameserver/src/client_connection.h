//-*-c++-*-
#ifndef NOVIA_CLIENT_CONNECTION_H
#define NOVIA_CLIENT_CONNECTION_H

#include <string>
#include <functional>
#include <mutex>
#include "protocol/out_message.h"


namespace novia {

  class ClientConnection {
  public:
    typedef std::function<void (int session_id, const std::string& msg)> SendFn;
    
    ClientConnection(int assigned_id, SendFn& send_fn);
    ClientConnection(const ClientConnection& other) = delete;
    ClientConnection(ClientConnection&& other) = delete;

    ClientConnection& operator= (const ClientConnection& other) = delete;
    ClientConnection& operator= (const ClientConnection&& other) = delete;

    int user_id() const;
    int session_id() const;
    bool authenticated() const;
    bool connected() const;

    void authenticate(int user_id);
    void send(const OutMessage& msg) const;
    void send(const std::string& msg) const;
    void close_connection();

  private:
    const int session_id_;
    int user_id_ = -1;
    SendFn send_;
    volatile bool connected_;
    mutable std::mutex conn_mutex_;
  };

}

#endif
 
