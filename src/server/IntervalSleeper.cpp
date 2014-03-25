#include "IntervalSleeper.h"

IntervalSleeper::IntervalSleeper(int interval)
  : nextTick_(std::chrono::system_clock::now())
  , delta_(interval) 
{

}


void IntervalSleeper::operator()(){
  nextTick_ += delta_;
  std::this_thread::sleep_until(nextTick_);
}
