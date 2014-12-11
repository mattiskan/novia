#ifndef NOVIA_WEBSOCKET_CONFIG
#define NOVIA_WEBSOCKET_CONFIG

#define _WEBSOCKETPP_CPP11_STL_
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>


struct WebsocketConfig : public websocketpp::config::asio {
  static const websocketpp::log::level elog_level =
    websocketpp::log::elevel::all ^ websocketpp::log::elevel::devel;

   static const websocketpp::log::level alog_level =
     websocketpp::log::alevel::none;
};

#endif
