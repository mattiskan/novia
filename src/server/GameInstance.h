#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H

#include "Map.h"
#include "Timer.h"
#include "ConnectionHandler.cpp"

int main(int argc, char ** argv);

struct EvenWaiter {
  
EvenWaiter(int millis): nextFrame(std::chrono::system_clock::now()), delta(millis){ }
  void operator()() {
    nextFrame += delta;
    std::this_thread::sleep_until(nextFrame);
  }
private:
  std::chrono::system_clock::time_point nextFrame;
  const std::chrono::milliseconds delta;
};

class GameInstance {
private:
  Map map;
  Timer timedEvents;
  ConnectionHandler* clients;
  void initiate();
  EvenWaiter sleep;
  virtual bool test();
public:
  GameInstance();
  void run();
};

#endif
