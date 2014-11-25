// -*-c++-*-
#include <cxxtest/TestSuite.h>
#include <functional>
#include <vector>
#include "../src/timer.h"

class TestTimer : public CxxTest::TestSuite
{
 private:
  int a_calls_, b_calls_;

  void a(Timer& t) {
    ++a_calls_;
  }

  void b(Timer& t) {
    ++b_calls_;
  }

 public:
  void setUp(){
    a_calls_ = 0;
    b_calls_ = 0;
  }

  void test_simple(){
    Timer t;

    TimerFn callback = std::bind(&TestTimer::a, this, t);
    t.schedule(callback, 1);

    TS_ASSERT_EQUALS(t.size(), 1);

    t.tick();

    TS_ASSERT_EQUALS(a_calls_, 1);
  }

  void test_order() {
    Timer t;

    TimerFn callback_a = std::bind(&TestTimer::a, this, t);
    TimerFn callback_b = std::bind(&TestTimer::b, this, t);

    t.schedule(callback_a, 3);
    t.schedule(callback_a, 3);
    t.schedule(callback_b, 1);
    t.schedule(callback_a, 3);
    t.schedule(callback_a, 3);

    t.tick();

    TS_ASSERT_EQUALS(a_calls_, 0);
    TS_ASSERT_EQUALS(b_calls_, 1);
    TS_ASSERT_EQUALS(t.size(), 4);
  }
  
};
