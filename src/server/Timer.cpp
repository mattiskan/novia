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

    --event->ticksLeft;

    if( shouldTrigger(event) )
      it = doEvent(event, it);
    else
      ++it;
  }
}

bool Timer::shouldTrigger(TimerEvent* eventPtr){
  return eventPtr->ticksLeft == 0;
}

std::list<TimerEvent*>::iterator Timer::doEvent(TimerEvent* eventPtr, std::list<TimerEvent*>::iterator& it){
    bool requeue = eventPtr->fn();
    if(requeue) {
      reset(eventPtr);
      return ++it;
    }
     
    it = queuedEvents.erase(it);
    delete eventPtr;
    return it;
}

void Timer::reset(TimerEvent* eventPtr){
  eventPtr->ticksLeft = eventPtr->interval;
}
