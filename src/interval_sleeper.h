#ifndef NOVIA_INTERVAL_SLEEPER_H
#define NOVIA_INTERVAL_SLEEPER_H

#include <chrono>
#include <thread>


class IntervalSleeper {
 private:
  std::chrono::system_clock::time_point nextTick_;
  const std::chrono::milliseconds delta_;

 public:
  IntervalSleeper(int millis);
  void operator()();
};

#endif
