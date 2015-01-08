// -*-c++-*-
#include <string>
#include <iostream>
#include <cxxtest/TestSuite.h>
#include <jsoncpp/json.h>
#include <memory>

#include "../src/map.h"
#include "../src/point.h"
#include "../src/farm.h"

using namespace novia;

class TestMap : public CxxTest::TestSuite
{
 public:

  void test_add() {
    Map map(1, 1);

    Point p(1,2);
    std::shared_ptr<Farm> farm(new Farm(p));
    map.add(farm);

    TS_ASSERT_EQUALS(map.object_count(), 1);
  }

  void test_serialize() {
    Map map(2, 2);

    // const char* expected ="{"
    //     "\"mapObjects\":" "[]"
    //   "}" "\n";
    

    Json::FastWriter writer;

    std::string output = writer.write(map.serialize());
    //TS_ASSERT_EQUALS(output, expected);
        TS_ASSERT(output.length() > 10);
  }


};
