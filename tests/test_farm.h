// -*-c++-*-
#include <string>
#include <iostream>
#include <cxxtest/TestSuite.h>
#include <jsoncpp/json.h>

#include "../src/point.h"
#include "../src/farm.h"

using namespace novia;

class TestFarm : public CxxTest::TestSuite
{
 public:

  void test_create() {
    Farm farm(Point (1,2));
  }

  void test_serialize() {
    Farm farm(Point (1,2));

    return; // TODO

    const char* expected = "todo";

    Json::FastWriter writer;

    std::string output = writer.write(farm.serialize());
    TS_ASSERT_EQUALS(output, expected);
  }


};
