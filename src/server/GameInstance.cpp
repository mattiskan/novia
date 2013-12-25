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
  int count=0;
  int last =-1;
  BOOST_FOREACH(int i, a){
    if(last != i){
      if(last != -1)
	std::cout << "recieved " << count <<" of " << last<< std::endl;
      count=0;
      last=i;
    }
    count++;
  }
  if(count != 0)
    std::cout << "recieved " << count <<" of " << last<< std::endl;
}
