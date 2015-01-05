#ifndef NOVIA_CONNECTION_RECEIVER_H
#define NOVIA_CONNECTION_RECEIVER_H

#ifdef UNIT_TEST
#define private public
#endif

#include <map>
#include <thread>
#include <utility>
#include "client_connection.h"
#include "protocol/message.h"
#include "websocket_config.hpp"

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

typedef websocketpp::server<WebsocketConfig> WebsocketServer;

namespace novia {

  class ConnectionReceiver {
  public:
    ConnectionReceiver();

    void initiate();
    void terminate();

    int connected_client_count() const;
    void broadcast(std::string msg);

    void send(int session_id, const std::string& msg);

  private:
    typedef std::map<websocketpp::connection_hdl, ClientConnection*,
      std::owner_less<websocketpp::connection_hdl>> con_list;
    
    con_list clients;
    std::map<int, websocketpp::connection_hdl> handles_;

    std::thread* acceptor_thread_ptr_;
    WebsocketServer socket_server_;
    int next_unassigned_id_;

    void on_connect(websocketpp::connection_hdl);
    void on_fail(websocketpp::connection_hdl);
    void on_close(websocketpp::connection_hdl);
    void on_message(websocketpp::connection_hdl, WebsocketServer::message_ptr msg);
  };

}
#endif
