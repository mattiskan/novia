#include <iostream>
#include <cxxtest/TestSuite.h>
#include "../src/server/IntervalSleeper.h"

class IntervalSleeperTest : public CxxTest::TestSuite
{

 public:

  void setUp(){
    
  }

  void testCreateIntervalSleeperInstance(){
    IntervalSleeper sleep(10);
  }

  void tearDown(){

  }
};
