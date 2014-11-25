//-*-c++-*-
#ifndef NOVIA_TIMER_H
#define NOVIA_TIMER_H

#include <queue>
#include <vector>
#include <functional>
#include <iostream>

class Timer;
typedef std::function<void(Timer&)> TimerFn;

struct TimerEvent {
  const TimerFn callback;
  const int when;

  TimerEvent(TimerFn& f, int time);
};

struct p_cmp {
  bool operator()(const TimerEvent* a, const TimerEvent* b) {
    return a->when > b-> when;
  }
};

class Timer {
 public:
  Timer();

  TimerEvent* schedule(TimerFn& f, time_t ticks_left);
  void remove(TimerEvent *const);
  void tick();

  size_t size() const;
  
 private:
  time_t time_;
  std::priority_queue<TimerEvent*,std::vector<TimerEvent*>,p_cmp> event_queue_;
};

#endif


