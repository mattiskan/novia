// -*-c++-*-
#include "../src/interval_sleeper.h"

#include <cxxtest/TestSuite.h>
#include <stdexcept>

using namespace Novia;

struct TimeMock : public Mocked::Base_time
{
  int time_;

  TimeMock(int initial): time_(initial) {}
  void operator+= (const int arg) { time_ += arg; }

  time_t time(time_t *) { // this is the mocked function
    return time_; 
  }

};

struct SleepMock : public Mocked::Base_usleep
{ 
  TimeMock& time_;
  int arg_;

  SleepMock(int i, TimeMock& time): time_(time), arg_(-1) { }

  int usleep(useconds_t sleep_time) { // this is the mocked function
    sleep_time /= 1000; // micro -> milli
    arg_ = sleep_time;
    time_ += sleep_time; // each call increments time
    return 0;
  }
};

class TestIntervalSleeper : public CxxTest::TestSuite
{
  TimeMock* m_time;
  SleepMock* m_sleep;

public:
  void test_wait_before_first_sleep() {
    IntervalSleeper sleep(1000);
    *m_time += 1100;

    sleep();

    TS_ASSERT_EQUALS(m_sleep->arg_, 1000);

    *m_time += 100;
    sleep();

    TS_ASSERT_EQUALS(m_sleep->arg_, 900);
  }

  void test_catch_up() {
    IntervalSleeper sleep(1000);
    sleep.start();

    *m_time += 1500;

    sleep();
    TS_ASSERT_EQUALS(m_sleep->arg_, -1);

    sleep();
    TS_ASSERT_EQUALS(m_sleep->arg_, 500);

    sleep();
    TS_ASSERT_EQUALS(m_sleep->arg_, 1000);
  }



  void setUp() {
    m_time = new TimeMock(12345);
    m_sleep = new SleepMock(0, *m_time);
  }

  void TearDown() {
    delete m_time; delete m_sleep;
  }
};
