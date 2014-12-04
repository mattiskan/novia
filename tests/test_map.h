// -*-c++-*-
#include <string>
#include <iostream>
#include <cxxtest/TestSuite.h>
#include <jsoncpp/json.h>

#include "../src/map.h"

using namespace Novia;

class TestMap : public CxxTest::TestSuite
{
 public:

  void test_serialize() {
    Map map;

    const char* expected ="{"
        "\"map\":" "{}"
      "}" "\n";
    

    Json::FastWriter writer;

    std::string output = writer.write(map.serialize());
    std::cout << output;
    TS_ASSERT_EQUALS(output, expected);

  }


};
