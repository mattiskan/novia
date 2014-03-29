#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H
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
