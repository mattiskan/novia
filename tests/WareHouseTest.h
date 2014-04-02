#include <cxxtest/TestSuite.h>
#include "../src/server/WareHouse.h"

#include <iostream>

class WareHouseTest : public CxxTest::TestSuite
{
 public:
  
  void testWareHouse() {
    WareHouse w;

    ResourceContainer newWares(10, { FOOD, IRON });
    newWares.add(5, FOOD);
    newWares.add(5, IRON);

    ResourceContainer remainder(w.addToStorage(newWares));

    TS_ASSERT_EQUALS(remainder.totalStorage(), 0);
    TS_ASSERT_EQUALS(w.getStorage().totalStorage(), 10);
  }

};
