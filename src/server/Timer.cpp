#include "Timer.h"

const TimerEvent* Timer::add(TimerFn f){
  TimerEvent* event = new TimerEvent(f, 1000);
  queuedEvents.push_back(*event);
  return event;
}

void Timer::tick() {
  for(auto it=queuedEvents.begin(); it != queuedEvents.end(); ++it)
    it->tick();
}
