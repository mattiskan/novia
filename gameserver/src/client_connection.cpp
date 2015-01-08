#include "client_connection.h"

#include "protocol/messages.h"
#include <stdexcept>
#include <jsoncpp/json.h>

namespace novia {

  ClientConnection::ClientConnection(int assigned_id, SendFn& send_fn)
    : session_id_(assigned_id),
      send_(send_fn),
      connected_(true)
  {
  
  }

  int ClientConnection::user_id() const {
    // std::lock_guard<std::mutex> lock(conn_mutex_);
    return user_id_;
  }

  int ClientConnection::session_id() const {
    return session_id_;
  }
  
  bool ClientConnection::authenticated() const {
    // std::lock_guard<std::mutex> lock(conn_mutex_);
    return user_id_ != -1;
  }

  void ClientConnection::authenticate(int user_id) {
    // std::lock_guard<std::mutex> lock(conn_mutex_);
    user_id_ = user_id;
  }

  bool ClientConnection::connected() const {
    // std::lock_guard<std::mutex> lock(conn_mutex_);
    return connected_;
  }
  
  void ClientConnection::send(const OutMessage& msg) const {
    Json::FastWriter writer;

    std::string payload = writer.write(msg.get_message());
    send(payload);
  }
  
  void ClientConnection::send(const std::string& msg) const {
    // std::lock_guard<std::mutex> lock(conn_mutex_);
    if (!connected())
      return;
    send_(session_id_, msg);
  }

  void ClientConnection::close_connection() {
    // std::lock_guard<std::mutex> lock(conn_mutex_);
    connected_ = false;
  }
}
