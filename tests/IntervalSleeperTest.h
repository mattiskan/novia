#include <iostream>
#include <cxxtest/TestSuite.h>
#include "../src/server/IntervalSleeper.h"

class IntervalSleeperTest : public CxxTest::TestSuite
{

 public:

  void setUp(){
    
  }

  void testSubLinearOverhead(){
    const int TIME_PER_SLEEP = 10;
    const int SLEEP_COUNT = 100;

    IntervalSleeper sleep(TIME_PER_SLEEP);
    clock_t init, final;
    init=clock();

    for(int i=0; i<SLEEP_COUNT; i++){
      sleep();
    }

    final= (clock()-init) / ((double)CLOCKS_PER_SEC);

    TS_ASSERT(final > TIME_PER_SLEEP*(SLEEP_COUNT-2))
    TS_ASSERT(final < TIME_PER_SLEEP*(SLEEP_COUNT+1))
  }

  void tearDown(){

  }
};
