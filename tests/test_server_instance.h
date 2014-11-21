// -*-c++-*-
#include <cxxtest/TestSuite.h>
#include <stdexcept>
#include "../src/server_instance.h"

class TestServerInstance : public CxxTest::TestSuite
{
 public:
  void test_creation() {
    ServerInstance instance;
    TS_ASSERT_THROWS(instance.start(), std::runtime_error);
  }

};
