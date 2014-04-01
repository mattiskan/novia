#include "Timer.h"

const TimerEvent* Timer::add(TimerFn f, int ticksLeft){
  TimerEvent* eventPtr = new TimerEvent(f, ticksLeft);
  queuedEvents.push_back(eventPtr);
  return eventPtr;
}

void Timer::remove(const TimerEvent* eventPtr) {
  queuedEvents.remove(const_cast<TimerEvent*>(eventPtr));
  delete eventPtr;
}

void Timer::tick() {
  for(auto it=queuedEvents.begin(); it != queuedEvents.end(); ){
    TimerEvent* event = *it;

    event->ticksLeft--;

    if( event->ticksLeft > 0){
      ++it;
      continue;
    }

    bool requeue = event->fn();
    if(requeue) {
      event->ticksLeft = event->interval;
      it++;
    } else {
      it = queuedEvents.erase(it);
      delete event;
    }

  }
}
