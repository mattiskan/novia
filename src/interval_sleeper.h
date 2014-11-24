#ifndef NOVIA_INTERVAL_SLEEPER_H
#define NOVIA_INTERVAL_SLEEPER_H

#include <chrono>
#include <thread>
#include "mocks.h"


/**
 * Each call sleeps until a prespecified time has passed _since_last_sleep_.
 *
 * Note:
 * IntervalSleeper will automatically "catch up" if more than one interval has
 * passed since last call to sleep operator. REMEMBER to call reset(), if you
 * want to stop this behaviour.
 *
 * Example:
 * You create a sleeper with interval 1000, sleep at time 1234,
 * do stuff for 45 ms and then call sleep.
 * It will sleep for 955 ms; until time 2234.
 */
class IntervalSleeper {
 private:
  std::time_t next_tick_;
  const std::time_t interval_;

 public:
  IntervalSleeper(time_t interval_millis);

  /*
   * Sleep until time_of(last sleep)+interval
   */
  void operator()();

  /*
   * Start counting the interval from now, without sleeping
   */
  void start();

  /*
   * Reset the interval timer, making next call to sleep exactly interval long.
   */
  void reset();
};

#endif
