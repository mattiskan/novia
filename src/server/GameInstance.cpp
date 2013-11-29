#include "GameInstance.h"
#include <iostream>

int main(int argc, char ** argv){
  GameInstance game;

  game.run();

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
  std::cout << "Tick" << std::endl;  
}

void GameInstance::initiate() {
  //clients->run();
  timedEvents.add(&test);
}




