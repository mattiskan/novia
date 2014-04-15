#include <iostream>
#include <cxxtest/TestSuite.h>
#include "../src/server/Map.h"
#include "../src/server/Farm.h"

class MapTest : public CxxTest::TestSuite
{
 public:

  void testAddMapObject(){
    Map map;
    Timer t;

    Farm f(FOOD, &t);
    map.add(f);
  }

};

