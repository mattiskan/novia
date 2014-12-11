//-*-c++-*-
#ifndef NOVIA_TIMER_H
#define NOVIA_TIMER_H

#include <queue>
#include <vector>
#include <functional>
#include <iostream>
#include "timer_event.h"

namespace novia {

  class TimerEvent;

  class Timer {
  public:
    void schedule(TimerFn& f, time_t ticks_left);
    void remove(TimerEvent *const);
    void tick();

    size_t size() const;
  
  private:
    time_t time_ = 0;
    std::priority_queue<TimerEvent> event_queue_;
  };

}
#endif


