// -*-c++-*-
#include "../src/interval_sleeper.h"

#include <cxxtest/TestSuite.h>
#include <stdexcept>

class TestIntervalSleeper : public CxxTest::TestSuite
{
 public:
  void test_first() {
    IntervalSleeper sleep(1000);
    
  }

};
