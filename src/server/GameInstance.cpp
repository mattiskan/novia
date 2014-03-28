#include "GameInstance.h"

int main( int argc, char **argv){
  GameInstance letsGetThisShowOnTheRoad;
  letsGetThisShowOnTheRoad.run();

  return 0;
}

GameInstance::GameInstance():
  sleep(1000)
{ 

}

void GameInstance::run(){
  while(true){
    doRecurringEvents();
    sleep();
  }
}

void GameInstance::doRecurringEvents(){
  
}
