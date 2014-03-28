#include <iostream>
#include <cxxtest/TestSuite.h>
#include <chrono>
#include <time.h>
#include <string>
#include "../src/server/IntervalSleeper.h"

using std::chrono::duration_cast;
using std::chrono::steady_clock;
using std::chrono::milliseconds;

class IntervalSleeperTest : public CxxTest::TestSuite
{
 public:
  static const int MILLIS_PER_SLEEP = 10;
  static const int SLEEP_COUNT = 100;
  static const int MARGIN = (int)(MILLIS_PER_SLEEP*SLEEP_COUNT)/1000.0;//0.1%

  void setUp(){
    testSubject = new IntervalSleeper(MILLIS_PER_SLEEP);
  }

  void tearDown(){
    delete testSubject;
  }

  void testSubLinearOverhead(){
    auto start = steady_clock::now();

    doSleep();

    int elapsed = elapsedMillisSince(start);
    TS_ASSERT_DELTA(elapsed, expectedTestTime(), MARGIN);
  }

  void testCatchUpDelays(){
    auto start = steady_clock::now();
    

    delay( MILLIS_PER_SLEEP * std::min<int>(5, (int)SLEEP_COUNT ) );

    doSleep();
    int elapsed = elapsedMillisSince(start);
    TS_ASSERT_DELTA(elapsed, expectedTestTime(), MARGIN);
  }


  void testTimeAlreadyExpired(){
    delay(expectedTestTime());
    delay(MILLIS_PER_SLEEP); //just in case :)

    auto start = steady_clock::now();
    
    doSleep();

    int elapsed = elapsedMillisSince(start);
    TS_ASSERT_DELTA(elapsed, 0, 10);
  }

  void testTimeAlmostExpired(){
    delay(expectedTestTime()-2);

    auto start = steady_clock::now();
    
    doSleep();

    int elapsed = elapsedMillisSince(start);
    TS_ASSERT_DELTA(elapsed, 0, MARGIN+3);
  }


  void testRealSecconds(){
    time_t start, stop;
    time(&start);

    doSleep();

    time(&stop);
    int actualTestTime = stop-start;

    TS_ASSERT_DELTA(actualTestTime, expectedTestTime()/1000, MARGIN/1000);
  }

  void testEachIndividualSleep(){
    for(int i=0; i<SLEEP_COUNT; i++){
      auto start = steady_clock::now();

      testSubject->sleep();

      int elapsed = elapsedMillisSince(start);
      TS_ASSERT_DELTA(elapsed, MILLIS_PER_SLEEP, MARGIN);
    }
  }

 private:
  IntervalSleeper* testSubject;

  void doSleep() const {
    for(int i=0; i<SLEEP_COUNT; i++){
      testSubject->sleep();
    }
  }

  const int expectedTestTime() const{
    return MILLIS_PER_SLEEP*SLEEP_COUNT;
  }

  int elapsedMillisSince(std::chrono::steady_clock::time_point startTime){
    auto elapsedTime = steady_clock::now() - startTime;
    return duration_cast<milliseconds>(elapsedTime).count();
  }

  void delay(int millis){
    std::this_thread::sleep_for(milliseconds(millis));    
  }

};
