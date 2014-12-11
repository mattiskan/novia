#include "timer_event.h"
#include <iostream>

namespace novia {

  TimerEvent::TimerEvent(const TimerFn& f, const int time)
    :callback_(f), when_(time) { 
  }

  TimerEvent::TimerEvent(const TimerEvent& rhs)
    : TimerEvent(rhs.callback_, rhs.when_) {
  
  }

  void TimerEvent::trigger(Timer& timer) {
    callback_(timer);
  }

  int TimerEvent::when() const {
    return when_;
  }

  TimerEvent& TimerEvent::operator=(TimerEvent&& rhs) {
    callback_ = rhs.callback_;
    when_ = rhs.when_;
    return *this;
  }

  bool TimerEvent::operator<(const TimerEvent& rhs) const {
    return when_ > rhs.when_; // smallest first
  }

}
