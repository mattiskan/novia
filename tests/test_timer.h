// -*-c++-*-
#include <cxxtest/TestSuite.h>
#include <functional>
#include <vector>
#include "../src/timer.h"

class TestTimer : public CxxTest::TestSuite
{
 private:
  Timer* timer;
  int calls_a, calls_b;

  TimerFn callback_a;
  TimerFn callback_b;

  void a(Timer& t) {
    ++calls_a;
  }

  void b(Timer& t) {
    ++calls_b;
  }

 public:
  void setUp(){
    timer = new Timer;
    calls_a = 0;
    calls_b = 0;
    callback_a = std::bind(&TestTimer::a, this, *timer);;
    callback_b = std::bind(&TestTimer::b, this, *timer);;
  }
  void tearDown() {
    delete timer;
  }

  void test_simple(){
    timer->schedule(callback_a, 1);

    TS_ASSERT_EQUALS(timer->size(), 1);

    timer->tick();

    TS_ASSERT_EQUALS(calls_a, 1);
  }

  void test_order() {
    timer->schedule(callback_a, 3);
    timer->schedule(callback_a, 2);
    timer->schedule(callback_b, 1);
    timer->schedule(callback_a, 2);
    timer->schedule(callback_a, 3);

    timer->tick();

    TS_ASSERT_EQUALS(calls_a, 0);
    TS_ASSERT_EQUALS(calls_b, 1);
    TS_ASSERT_EQUALS(timer->size(), 4);
  }

  void test_removed_after_trigger() {
    for(int i=0; i<10; ++i)
      timer->schedule(callback_a, i+1);
    
    TS_ASSERT_EQUALS(timer->size(), 10);

    for(int i=0; i<10; ++i){
      timer->tick();
      TS_ASSERT_EQUALS(timer->size(), 10-(i+1));
    }

    TS_ASSERT_EQUALS(calls_a, 10);
  }

  void test_multiple() {
    timer->schedule(callback_a, 4);
    timer->schedule(callback_b, 3);
    timer->schedule(callback_a, 2);
    timer->schedule(callback_b, 1);

    timer->tick();
    TS_ASSERT_EQUALS(calls_a, 0);
    TS_ASSERT_EQUALS(calls_b, 1);

    timer->tick();
    TS_ASSERT_EQUALS(calls_a, 1);
    TS_ASSERT_EQUALS(calls_b, 1);

    timer->tick();
    TS_ASSERT_EQUALS(calls_a, 1);
    TS_ASSERT_EQUALS(calls_b, 2);

    timer->tick();
    TS_ASSERT_EQUALS(calls_a, 2);
    TS_ASSERT_EQUALS(calls_b, 2);
  }

  void test_one_callback() {
    timer->schedule(callback_a, 5);
    
    for(int i=0; i<10; ++i)
      timer->tick();

    TS_ASSERT_EQUALS(calls_a, 1);
  }

};
