#include "TimerEvent.h"


TimerEvent::TimerEvent(TimerFn fn, int ticks )
    : eventFunction(fn), ticksLeft(ticks), interval(ticks)
    { 
    
    }

void TimerEvent::tick(){
  --ticksLeft;
}

bool TimerEvent::shouldTrigger(){
  return ticksLeft == 0;
}


void TimerEvent::reset(){
  ticksLeft = interval;
}
