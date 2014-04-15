#include <iostream>
#include <cxxtest/TestSuite.h>
#include "../src/server/Farm.h"
#include "../src/server/Timer.h"

class FarmTest : public CxxTest::TestSuite
{
 public:

  void testGrowth(){
    Timer t;
    Farm subject(WOOD, &t);
      
    for(int i=0; i<121; ++i)
      t.tick();

    TS_ASSERT_EQUALS(subject.getStorage().getAmount(WOOD), 2);

  }

  void tetsStopGrowthOnFull() {
    
  }

};

