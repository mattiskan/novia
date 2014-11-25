//-*-c++-*-
#ifndef NOVIA_TIMER_H
#define NOVIA_TIMER_H

#include <queue>
#include <vector>
#include <functional>
#include <iostream>

class Timer;
typedef std::function<void(Timer&)> TimerFn;

class TimerEvent {
  TimerFn callback_;
  int when_;

public:
  TimerEvent(const TimerFn& f, const int time);
  TimerEvent(const TimerEvent&);

  void trigger(Timer& timer);

  int when() const;

  TimerEvent& operator=(TimerEvent&& rhs);
  bool operator<(const TimerEvent& rhs) const;
};


class Timer {
 public:
  Timer();

  void schedule(TimerFn& f, time_t ticks_left);
  void remove(TimerEvent *const);
  void tick();

  size_t size() const;
  
 private:
  time_t time_;
  std::priority_queue<TimerEvent> event_queue_;
};

#endif


