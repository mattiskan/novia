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

  void test_distance() {
    Point p1(1, 1);
    Point p2(1, 2);
    Point p3(2, 2);

    TS_ASSERT_EQUALS(p1.distance_to(p2), 1);
    TS_ASSERT_EQUALS(p1.distance_to(p3), sqrt(2));
    TS_ASSERT_EQUALS(p2.distance_to(p3), 1);
  }

};
