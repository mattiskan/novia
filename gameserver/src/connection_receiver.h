//-*-c++-*-
#ifndef NOVIA_CONNECTION_RECEIVER_H
#define NOVIA_CONNECTION_RECEIVER_H

#include <map>
#include <thread>
#include <utility>
#include <functional>
#include <memory>

#include "client_connection.h"
#include "controllers.h"
#include "websocket_config.hpp"
#include "protocol/in_message.h"


using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

typedef websocketpp::server<WebsocketConfig> WebsocketServer;

namespace novia {

  class ConnectionReceiver {
  public:
    typedef std::function< void(const std::shared_ptr<InMessage>&, const std::shared_ptr<ClientConnection>) > MessageHandlerFn;
    ConnectionReceiver();

    void initiate();
    void terminate();

    int connected_client_count() const;
    
    void broadcast(std::string msg);
    void send_to(int session_id, const std::string& msg);
    
    void set_message_handler(const MessageHandlerFn& handler);
    
  private:
    typedef std::map<websocketpp::connection_hdl, std::shared_ptr<ClientConnection>,
      std::owner_less<websocketpp::connection_hdl>> con_list;

    con_list clients;

    std::map<int, websocketpp::connection_hdl> sessions_;
    
    MessageHandlerFn message_handler_;

    std::thread* acceptor_thread_ptr_;
    WebsocketServer socket_server_;
    int next_unassigned_id_;

    //Called when a new client have connected
    void on_connect(websocketpp::connection_hdl);
    //Called when a connection failed to connect to this server
    void on_fail(websocketpp::connection_hdl);
    //Called when the socket is closed
    void on_close(websocketpp::connection_hdl);
    //Called when the server retrieved a message from a client
    void on_message(websocketpp::connection_hdl, WebsocketServer::message_ptr msg);
  };

}
#endif
