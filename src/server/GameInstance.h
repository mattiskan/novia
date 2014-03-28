#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include "IntervalSleeper.h"

class GameInstance {
 private:
  IntervalSleeper sleep;
  void doRecurringEvents();
 public:
  GameInstance();
  void run();
};

#endif
