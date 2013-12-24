#include "GameInstance.h"
#include <iostream>
#include <boost/foreach.hpp>

int main(int argc, char ** argv){
  GameInstance letsGetThisShowOnTheRoad;

  letsGetThisShowOnTheRoad.run();
}

GameInstance::GameInstance() : sleep(1000){
  ::unlink(SOCKET_FILE); // Remove previous binding.
  stream_protocol::endpoint ep(SOCKET_FILE);
  clientConnections = new ConnectionHandler(ep);
}
void GameInstance::run(){
  initiate();

  while(true) {
    timedEvents.tick();
    doRecurringEvents();
    sleep();
  }
}

bool GameInstance::test(){
  std::cout << "This is the test function" << std::endl;  
}

void GameInstance::initiate() {
  clientConnections->start();
}

void GameInstance::doRecurringEvents(){
  std::vector<int> a = clientConnections->pollClientActions();
  BOOST_FOREACH(int i, a){
    std::cout << "recieved " << i << std::endl;
  }
}
