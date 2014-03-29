#include "GameInstance.h"

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
