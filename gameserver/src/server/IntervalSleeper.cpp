#include "IntervalSleeper.h"

IntervalSleeper::IntervalSleeper(int interval)
  : nextTick_(std::chrono::steady_clock::now())
  , delta_(interval) 
{

}


void IntervalSleeper::operator()(){
  sleep();
}

void IntervalSleeper::sleep(){
  nextTick_ += delta_;
  if(std::chrono::steady_clock::now() < nextTick_)
    std::this_thread::sleep_until(nextTick_);
}
