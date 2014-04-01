#ifndef TIMER_EVENT_H
#define TIMER_EVENT_H

#include <functional>
typedef std::function<bool ()>TimerFn;

struct TimerEvent {
  TimerEvent(TimerFn eventCallback, int ticksToCallback);

  const TimerFn eventFunction;
  int ticksLeft;
  const int interval;

  bool shouldTrigger();
  void tick();
  void reset();
  
};
#endif
