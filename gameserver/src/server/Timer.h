#ifndef TIMER_H
#define TIMER_H

#include <list>
#include <chrono>
#include <iostream>
#include <functional>
#include "TimerEvent.h"

typedef std::function<bool ()>TimerFn;
#define REQUEUE true
#define NO_REQUEUE false



class Timer {
 protected:
  std::list<TimerEvent*> queuedEvents_;

 public:
  Timer() {};
  TimerEvent* const add(TimerFn, int ticksLeft);
  void remove(TimerEvent* const);
  void tick();

 private:
  std::list<TimerEvent*>::iterator doEvent(TimerEvent*, std::list<TimerEvent*>::iterator&);
};

#endif
