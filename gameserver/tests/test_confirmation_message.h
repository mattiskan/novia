//-*-c++-*-
#include <cxxtest/TestSuite.h>
//#include <jsoncpp/json.h>
#include "../src/protocol/confirmation_message.h"

using namespace novia;

class TestConfirmationMessage : public CxxTest::TestSuite
{
 public:
  void test_message() {
    ConfirmationMessage* c_msg =
      new ConfirmationMessage();

    c_msg->set_status(ConfirmationMessage::ACCEPTED);
    
    const OutMessage* msg = (const OutMessage*) c_msg;

    Json::Value result = msg->get_message();

    TS_ASSERT_EQUALS(result["msg_type"], "confirmation");
    TS_ASSERT_EQUALS(result["status"], "accepted");
  }

};
