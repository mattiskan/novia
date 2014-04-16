#include <cxxtest/TestSuite.h>
#include "../src/server/Timer.h"
#include <functional>

class TimerTest : public CxxTest::TestSuite
{
 private:
  int numCallA_, numCallB_;

  bool callA() {
    ++numCallA_;
    return REQUEUE;
  }

  bool callB() {
    ++numCallB_;
    return NO_REQUEUE;
  }
  

 public:
  void setUp(){
    numCallA_ = 0;
    numCallB_ = 0;
  }

  void testRequeue(){
    Timer subject;

    subject.add( std::bind(&TimerTest::callA, this), 1);

    for(int i=0; i<5; ++i)
      subject.tick();

    TS_ASSERT_EQUALS(numCallA_, 5);
  }

  void testNoRequeue() {
    Timer subject;
    subject.add( std::bind(&TimerTest::callB, this), 1);

    for(int i=0; i<5; i++){
      subject.tick();
    }

    TS_ASSERT_EQUALS(numCallB_, 1);
  }

  void testEventInterval(){
    Timer subject;
    subject.add( std::bind(&TimerTest::callA, this), 3);

    for(int i=1; i<40; ++i){
      subject.tick();
      TS_ASSERT_EQUALS(numCallA_, i/3);
    }
  }

  void testThreeEvents() {
    Timer subject;
    subject.add( std::bind(&TimerTest::callA, this), 1);
    subject.add( std::bind(&TimerTest::callA, this), 3);
    subject.add( std::bind(&TimerTest::callA, this), 10);
    subject.add( std::bind(&TimerTest::callB, this), 39);

    for(int i=1; i<40; ++i){
      subject.tick();
      TS_ASSERT_EQUALS(numCallA_, (i + i/3 + i/10) );
    }

    TS_ASSERT_EQUALS(numCallB_, 1);
  }

  void testRemoveTick(){
    Timer subject;
    auto eventPtr = subject.add( std::bind(&TimerTest::callA, this), 1);

    for(int i=0; i<5; ++i)
        subject.tick();

    subject.remove(eventPtr);

    for(int i=0; i<5; ++i){   
        subject.tick();
	TS_ASSERT_EQUALS(numCallA_, 5);
    }
  }

  void testRemoveWithThreeEvents(){
    Timer subject;

    auto one = subject.add( std::bind(&TimerTest::callA, this), 1);
    auto two = subject.add( std::bind(&TimerTest::callA, this), 1);
    auto three = subject.add( std::bind(&TimerTest::callA, this), 1);

    subject.remove(two);

    subject.tick();

    TS_ASSERT_EQUALS(numCallA_, 2);
  }
};
