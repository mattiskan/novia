#include "interval_sleeper.h"

IntervalSleeper::IntervalSleeper(int millis)
  : nextTick_(std::chrono::system_clock::now())
  , delta_(millis) {

}


void IntervalSleeper::operator()(){
  nextTick_ += delta_;
  if(std::chrono::system_clock::now() < nextTick_)
    std::this_thread::sleep_until(nextTick_);
}

