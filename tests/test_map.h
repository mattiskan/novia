// -*-c++-*-
#include <string>
#include <iostream>
#include <cxxtest/TestSuite.h>
#include <jsoncpp/json.h>

#include "../src/map.h"
#include "../src/farm.h"

using namespace Novia;

class TestMap : public CxxTest::TestSuite
{
 public:

  void test_add() {
    Map map;
    Farm f;
    map.add(f);

    TS_ASSERT_EQUALS(map.object_count(), 1);
  }

  void test_serialize() {
    Map map;

    const char* expected ="{"
        "\"map\":" "{}"
      "}" "\n";
    

    Json::FastWriter writer;

    std::string output = writer.write(map.serialize());
    TS_ASSERT_EQUALS(output, expected);
  }


};
