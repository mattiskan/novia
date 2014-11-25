#include "timer.h"
#include <algorithm>
#include <iostream>


TimerEvent::TimerEvent(TimerFn& f, int time)
  :callback(f), when(time) { 
}

Timer::Timer(): time_(0) { }

TimerEvent* Timer::schedule(TimerFn& f, time_t ticks_left) {
  TimerEvent* new_event = new TimerEvent(f, ticks_left);

  event_queue_.push(new_event);
  return new_event;
}

void Timer::tick() {
  ++time_;

  while (!event_queue_.empty() && 
	  event_queue_.top()->when <= time_) {

    TimerEvent *const top = event_queue_.top();
    top->callback(*this);

    event_queue_.pop();
    delete top;
  }
}

size_t Timer::size() const {
  return event_queue_.size();
}

