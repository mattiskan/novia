// -*-c++-*-
#include "../src/interval_sleeper.h"

#include <cxxtest/TestSuite.h>
#include <stdexcept>

struct TimeMock : public T::Base_time
{
  int time_;
  const int increment_;

  TimeMock(int increment) : increment_(increment) {}
  time_t time(time_t *) {
    time_ += increment_;
    return time_; 
  }
};

struct SleepMock : public T::Base_usleep
{ 
  SleepMock(int i) {

  }
  int arg;
  int usleep(useconds_t sleep_time) {
    arg = sleep_time;
    return 0;
  }
};

class TestIntervalSleeper : public CxxTest::TestSuite
{
 public:
  void test_late_first_call() {
    TimeMock m_time(0);
    SleepMock m_sleep(0);

    IntervalSleeper sleep(1000);
    sleep();

    TS_ASSERT_EQUALS(m_sleep.arg, 1000*1000);
  }


};
