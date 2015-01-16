#include "timer.h"
#include <algorithm>
#include <iostream>

namespace novia {

  void Timer::schedule(TimerFn& f, time_t ticks_left) {
    event_queue_.emplace(f, (ticks_left+time_));
  }

  void Timer::tick() {
    ++time_;

    while (!event_queue_.empty() && 
	   event_queue_.top().when() <= time_) {

      TimerEvent top = event_queue_.top();
      top.trigger(*this);

      event_queue_.pop();
    }
  }

  size_t Timer::size() const {
    return event_queue_.size();
  }

}
