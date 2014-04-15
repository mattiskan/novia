#include "Timer.h"

TimerEvent* const Timer::add(TimerFn f, int ticksLeft){
  TimerEvent* eventPtr = new TimerEvent(f, ticksLeft);
  queuedEvents_.push_back(eventPtr);
  return eventPtr;
}

void Timer::remove(TimerEvent* const eventPtr) {
  queuedEvents_.remove(eventPtr);
  delete eventPtr;
}

void Timer::tick() {
  for(auto it=queuedEvents_.begin(); it != queuedEvents_.end(); ){
    TimerEvent* event = *it;

    event->tick();

    if( event->shouldTrigger() )
      it = doEvent(event, it);
    else
      ++it;
  }
}

std::list<TimerEvent*>::iterator Timer::doEvent(TimerEvent* eventPtr, std::list<TimerEvent*>::iterator& it){
    bool requeue = eventPtr->eventFunction();
    if(requeue) {
      eventPtr->reset();
      return ++it;
    }
     
    it = queuedEvents_.erase(it);
    delete eventPtr;
    return it;
}

