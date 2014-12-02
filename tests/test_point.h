// -*-c++-*-
#include <cxxtest/TestSuite.h>
#include <string>
#include <iostream>
#include <regex>
#include <jsoncpp/json.h>

#include "../src/point.h"

using namespace Novia;

class TestPoint : public CxxTest::TestSuite
{
 public:
  void test_creation() {
    Point p1(1,3);

    TS_ASSERT_EQUALS(p1.x(), 1);
    TS_ASSERT_EQUALS(p1.y(), 3);
  }

};
