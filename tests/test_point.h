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

  void test_add() {
    Point p1(1, 3);
    Point p2(2, 4);
    
    Point sum(3, 7);
    
    TS_ASSERT_EQUALS(p1 + p2, sum);
  }

  void test_subtract() {
    Point p1(1, 3);
    Point p2(2, 4);

    TS_ASSERT_EQUALS(p1 - p2, Point(-1, -1));
    TS_ASSERT_EQUALS(p2 - p1, Point( 1,  1));
  }


  void test_equals() {
    Point p1(0,0);
    Point p2(0,0);
    Point p3(1,0);
    Point p4(0,1);
    Point p5(1,1);
    
    TS_ASSERT(p1 == p1);
    TS_ASSERT(p1 == p2 && p2 == p1);
    
    TS_ASSERT(!(p1 == p3));
    TS_ASSERT(!(p1 == p4));
  }

};
