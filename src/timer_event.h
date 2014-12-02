//-*-c++-*-
#ifndef NOVIA_TIMER_EVENT_H
#define NOVIA_TIMER_EVENT_H

#include <functional>

namespace Novia {

  class Timer;
  typedef std::function<void(Timer&)> TimerFn;

  class TimerEvent {
    TimerFn callback_;
    int when_;

  public:
    TimerEvent(const TimerFn& f, const int time);
    TimerEvent(const TimerEvent&);

    void trigger(Timer& timer);

    int when() const;

    TimerEvent& operator=(TimerEvent&& rhs);
    bool operator<(const TimerEvent& rhs) const;
  };

}
#endif
