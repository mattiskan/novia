#include "interval_sleeper.h"
#include <unistd.h>
#include <iostream>

IntervalSleeper::IntervalSleeper(time_t interval_millis)
  : next_tick_(0), delta_(interval_millis) {

}

void IntervalSleeper::operator()(){
  if (next_tick_ == 0)
    next_tick_ = T::time(nullptr);

  next_tick_ += delta_;

  int sleep_duration = next_tick_ - T::time(nullptr);

  if (sleep_duration > 0) {
    T::usleep(sleep_duration*1000);
    next_tick_ = T::time(nullptr);
  }
}


void IntervalSleeper::start() {
  next_tick_ = T::time(nullptr);
}

void IntervalSleeper::reset() {
  next_tick_ = 0;
}
