#ifndef TIMER_H
#define TIMER_H

#include <list>
#include <chrono>
#include <iostream>

typedef bool (*TimerFn)(void);

struct TimerEvent {
  TimerEvent(TimerFn f, int d) : fn(f), dur(d) { }
  
  bool tick(){
    fn();
  }

private:
  TimerFn fn;
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
