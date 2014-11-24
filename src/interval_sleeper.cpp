#include "interval_sleeper.h"
#include <unistd.h>

IntervalSleeper::IntervalSleeper(time_t interval_millis)
  : last_tick_(T::time(nullptr)), delta_(interval_millis) {

}

void IntervalSleeper::operator()(){
  time_t sleep_duration = delta_ - (T::time(nullptr) - last_tick_);

  if (sleep_duration > 0)
    T::usleep(sleep_duration*1000);
  last_tick_ = T::time(nullptr);
}

