#include "interval_sleeper.h"
#include <unistd.h>
#include <iostream>

namespace Novia { 
  IntervalSleeper::IntervalSleeper(time_t interval_millis)
    : next_tick_(0), interval_(interval_millis) {

  }

  void IntervalSleeper::operator()(){
    if (next_tick_ == 0)
      next_tick_ = Mocked::time(nullptr);

    next_tick_ += interval_;

    int sleep_duration = next_tick_ - Mocked::time(nullptr);

    if (sleep_duration > 0) {
      Mocked::usleep(sleep_duration*1000);
      next_tick_ = Mocked::time(nullptr);
    }
  }


  void IntervalSleeper::start() {
    next_tick_ = Mocked::time(nullptr);
  }

  void IntervalSleeper::reset() {
    next_tick_ = 0;
  }
}
