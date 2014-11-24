#ifndef NOVIA_INTERVAL_SLEEPER_H
#define NOVIA_INTERVAL_SLEEPER_H

#include <chrono>
#include <thread>
#include "mocks.h"


class IntervalSleeper {
 private:
  bool first_;
  std::time_t last_tick_;
  const std::time_t delta_;

 public:
  IntervalSleeper(time_t interval_millis);
  void operator()();
};

#endif
