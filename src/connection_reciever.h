#ifndef NOVIA_CONNECTION_RECEIVER_H
#define NOVIA_CONNECTION_RECEIVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <map>
#include <thread>
#include <utility>

#include "client_connection.h"


using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;


typedef websocketpp::server<websocketpp::config::asio> WebsocketServer;


class ConnectionReceiver {
 public:
  ConnectionReceiver();

  void initiate();
  void terminate();

  int connected_client_count() const;
  void broadcast(std::string msg);

private:
  typedef std::map<websocketpp::connection_hdl, ClientConnection*,
    std::owner_less<websocketpp::connection_hdl>> con_list;

  con_list clients;

  std::thread* acceptor_thread_ptr_;
  WebsocketServer socket_server_;
  int next_unassigned_id_;

  void on_connect(websocketpp::connection_hdl);
  void on_message(websocketpp::connection_hdl, WebsocketServer::message_ptr msg);
};

#endif
