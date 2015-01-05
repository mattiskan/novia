// -*-c++-*-
#include <cxxtest/TestSuite.h>
#define UNIT_TEST

#include "../src/protocol/message_type.h"

using namespace novia;
using namespace message_type;


class TestMessageType : public CxxTest::TestSuite
{
 public:
  void test_from_enum() {
    TS_ASSERT_EQUALS("authenticate", from_enum(AUTHENTICATE));
  }


  void test_from_string() {
    TS_ASSERT_EQUALS(AUTHENTICATE, from_name("authenticate"));
  }
};
