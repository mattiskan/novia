#include "timer.h"
#include <algorithm>
#include <iostream>


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


Timer::Timer(): time_(0) { }

void Timer::schedule(TimerFn& f, time_t ticks_left) {
  event_queue_.emplace(f, ticks_left);
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

