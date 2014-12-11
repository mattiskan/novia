// -*-c++-*-
#include <cxxtest/TestSuite.h>
#include <stdexcept>
#include "../src/server_instance.h"

using namespace novia;

class TestServerInstance : public CxxTest::TestSuite
{
 public:
  void test_creation() {
    ServerInstance instance;
  }

};
