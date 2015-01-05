//-*-c++-*-
#include <cxxtest/TestSuite.h>
//#include <jsoncpp/json.h>
#include "../src/protocol/authentification_message.h"

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

};
