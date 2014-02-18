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
#include "../protocol/Message.h" //testlösning
  MapController mc(map);
  std::vector<Message> a = clientConnections->pollClientActions();
  for(int i=0; i<a.size(); ++i){
    a[i].doAction(mc);
  }
}
