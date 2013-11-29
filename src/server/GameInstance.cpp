#include "GameInstance.h"
#include <iostream>
#include <functional>

int main(int argc, char ** argv){
  GameInstance letsGetThisShowOnTheRoad;

  letsGetThisShowOnTheRoad.run();
}

GameInstance::GameInstance() : sleep(1000){
  ::unlink(SOCKET_FILE); // Remove previous binding.
  stream_protocol::endpoint ep(SOCKET_FILE);
  clients = new ConnectionHandler(ep);
}

void GameInstance::run(){
  initiate();

  while(true) {
    timedEvents.tick();
    sleep();
  }
}

bool GameInstance::test(){
  std::cout << "This is the test function" << std::endl;  
}

void GameInstance::initiate() {
  //clients->run();
  timedEvents.add(std::bind((&GameInstance::test), this));
}

