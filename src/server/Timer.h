#ifndef TIMER_H
#define TIMER_H

#include <list>
#include <chrono>
#include <iostream>
#include <functional>

typedef std::function<bool ()>TimerFn;

struct TimerEvent {
  TimerEvent(TimerFn f, int d) : fn(f), dur(d) { }
  TimerFn fn;
private:
  int dur;
};

class Timer {
 private:
  std::list<TimerEvent> queuedEvents;
 public:
  Timer() {};
  const TimerEvent* add( TimerFn );
  void remove( TimerEvent*);
  void tick();
};

#endif
