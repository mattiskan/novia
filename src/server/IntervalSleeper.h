#ifndef INTERVAL_SLEEPER_H
#define INTERVAL_SLEEPER_H
#include <chrono>


class IntervalSleeper {
 private:
  std::chrono::system_clock::time_point nextTick_;
  const std::chrono::milliseconds delta_;

 public:
  //constructors
  IntervalSleeper(int);
  void operator()();
};


#endif
