// -*-c++-*-
#include <cxxtest/TestSuite.h>
#define UNIT_TEST

#include "../src/websocket_config.hpp"
#include "../src/protocol/authentification_message.h"
#include "../src/connection_receiver.h"

using namespace novia;

class TestAuthenticationMessage : public CxxTest::TestSuite
{
 public:
  void test_creation() {
    Json::Value auth;
    Json::Reader reader;

    const char* txt =
      "{"
       "\"username\": \"bob\","
       "\"password\": \"banana\""
      "}";

    reader.parse(txt, auth, false);
        
    AuthentificationMessage msg;
    msg.read(auth);

    TS_ASSERT_EQUALS(msg.username(), "bob");
    TS_ASSERT_EQUALS(msg.password(), "banana");
    
  }


  void test_login() {
    ConnectionReceiver cr;

    websocketpp::connection_hdl hdl;
    cr.on_connect(hdl);
    // TODO: mock message...
    //cr.on_message(hdl, msg);
  }
};
