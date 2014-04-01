#ifndef TIMER_H
#define TIMER_H

#include <list>
#include <chrono>
#include <iostream>
#include <functional>

typedef std::function<bool ()>TimerFn;
#define REQUEUE true
#define NO_REQUEUE false

struct TimerEvent {

TimerEvent(TimerFn f, int t)
  : fn(f), ticksLeft(t), interval(t) { }

  TimerFn fn;
  int ticksLeft;
  const int interval;
};

class Timer {
 private:
  std::list<TimerEvent*> queuedEvents;

 public:
  Timer() {};
  const TimerEvent* add(TimerFn, int ticksLeft);
  void remove(const TimerEvent*);
  void tick();

 private: //helper functions
  bool shouldTrigger(TimerEvent*);
  std::list<TimerEvent*>::iterator doEvent(TimerEvent*, std::list<TimerEvent*>::iterator&);
  void reset(TimerEvent*);
};

#endif
