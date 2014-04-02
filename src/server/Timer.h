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
 private:
  std::list<TimerEvent*> queuedEvents;

 public:
  Timer() {};
  const TimerEvent* add(TimerFn, int ticksLeft);
  void remove(const TimerEvent*);
  void tick();

 private:
  std::list<TimerEvent*>::iterator doEvent(TimerEvent*, std::list<TimerEvent*>::iterator&);
};

#endif
