#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H

#include "Map.h"
#include "Timer.h"
#include "ConnectionHandler.h"

using std::chrono::system_clock;
using std::chrono::milliseconds;

int main(int argc, char ** argv);

struct EvenWaiter {
EvenWaiter(int millis): nextFrame(system_clock::now()), delta(millis){ }
  void operator()() {
    nextFrame += delta;
    std::this_thread::sleep_until(nextFrame);
  }
private:
  system_clock::time_point nextFrame;
  const milliseconds delta;
};

class GameInstance {
private:
  Map map;
  Timer timedEvents;
  ConnectionHandler* clientConnections;
  void initiate();
  EvenWaiter sleep;
  void doRecurringEvents();
public:
  GameInstance();
  void run();
  bool test();
};
#endif
